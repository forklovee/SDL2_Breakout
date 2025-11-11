#include "graphics/image/image.h"
#include "core/window.h"
#include "graphics/object2d.h"

#include "SDL_error.h"
#include "SDL_image.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_surface.h"
#include <cstdint>
#include <iostream>

namespace Engine {

Image::Image(Vector2<float> position, Vector2<int> size)
    : Object2D(position, size), m_image_texture(nullptr, nullptr),
      m_loaded(false) {}

Image::Image(const char *texture_path, Vector2<float> position,
             Vector2<int> size, bool use_color_key, Vector3<uint8_t> color_key)
    : Object2D(position, size), m_image_texture(nullptr, nullptr),
      m_use_color_key(use_color_key), m_color_key(color_key), m_loaded(false) {
  set_texture_path(texture_path);
}

Image::~Image() { clear(); }

void Image::render(Window &target_window) {
  if (!is_texture_loaded()) {
    load_texture(target_window.get_renderer());
  }

  if (m_image_clips.empty()) {
    draw(target_window.get_renderer());
    return;
  }
  draw_all_image_clips(target_window.get_renderer());
}

void Image::set_color(const Vector3<uint8_t> &color, const uint8_t &alpha) {
  m_color = color;
  m_alpha = alpha;

  SDL_SetTextureColorMod(m_image_texture.get(), m_color.x, m_color.y,
                         m_color.z);
  SDL_SetTextureAlphaMod(m_image_texture.get(), m_alpha);
}

void Image::set_blend_mode(SDL_BlendMode blend_mode) {
  SDL_SetTextureBlendMode(m_image_texture.get(), blend_mode);
}

SDL_Texture *Image::get_texture() const { return m_image_texture.get(); }

void Image::set_texture_path(const char *texture_path) {
  if (is_texture_loaded()) { // Free current texture
    m_image_texture.reset();
  }
  m_loaded = false;
  m_texture_path = texture_path;
}

void Image::add_image_clip(SDL_Rect clip_rect, Vector2<float> local_position) {
  m_image_clips.push_back(ImageClip(clip_rect, m_position + local_position));
}

void Image::remove_image_clip(const size_t clip_id) {
  m_image_clips.erase(m_image_clips.begin() + clip_id);
}

ImageClip &Image::get_imape_clip(const size_t clip_id) {
  return m_image_clips[clip_id];
}

void Image::draw(SDL_Renderer *renderer, SDL_Rect *clip_rect) {
  SDL_Rect transform = get_transform();
  if (clip_rect != NULL) {
    transform.w = clip_rect->w;
    transform.h = clip_rect->h;
  }

  if (m_image_texture == nullptr) {
    SDL_SetRenderDrawColor(renderer, m_color.x, m_color.y, m_color.z, m_alpha);
    SDL_RenderFillRect(renderer, &transform);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    return;
  }

  SDL_SetTextureColorMod(m_image_texture.get(), m_color.x, m_color.y,
                         m_color.z);
  SDL_SetTextureAlphaMod(m_image_texture.get(), m_alpha);

  SDL_RenderCopyEx(renderer, m_image_texture.get(), clip_rect, &transform,
                   get_rotation(), &get_pivot_point(), get_flipmode());
}

void Image::draw_all_image_clips(SDL_Renderer *renderer) {
  for (ImageClip &image_clip : m_image_clips) {
    draw_image_clip(renderer, image_clip);
  }
}

void Image::draw_image_clip(SDL_Renderer *renderer, ImageClip &image_clip) {
  SDL_RenderCopyEx(renderer, m_image_texture.get(), &image_clip.clip_rect,
                   &image_clip.destination_rect, get_rotation(),
                   &get_pivot_point(), get_flipmode());
}

void Image::draw_image_clip(SDL_Renderer *renderer, uint8_t image_clip_id) {
  draw_image_clip(renderer, m_image_clips[image_clip_id]);
}

const bool Image::is_texture_loaded() const { return m_image_texture != NULL; }

bool Image::load_texture(SDL_Renderer *target_renderer) {
  // If renderer is not provided, do not load the texture
  if (target_renderer == NULL) {
    return false;
  }
  if (m_loaded) {
    return true;
  }

  m_loaded = true;

  if (m_texture_path.empty()) {
    return false;
  }

  std::cout << "Image: Load texture from path: " << m_texture_path << "."
            << std::endl;

  // Load Texture

  if (!m_use_color_key) {
    SDL_Texture *raw_texture_ptr =
        IMG_LoadTexture(target_renderer, m_texture_path.c_str());
    m_image_texture = SDLTexturePtr(raw_texture_ptr, SDL_DestroyTexture);
  } else {
    SDL_Surface *image_surface = IMG_Load(m_texture_path.c_str());
    if (!image_surface) {
      std::cerr << "Error! Couldn't create an image surface from "
                << m_texture_path << " image!" << IMG_GetError() << std::endl;
      return false;
    }

    SDL_SetColorKey(image_surface, SDL_TRUE,
                    SDL_MapRGB(image_surface->format, m_color_key.x,
                               m_color_key.y, m_color_key.z));

    SDL_Texture *raw_texture_ptr =
        SDL_CreateTextureFromSurface(target_renderer, image_surface);
    SDL_FreeSurface(image_surface);

    m_image_texture = SDLTexturePtr(raw_texture_ptr, SDL_DestroyTexture);
  }

  if (!m_image_texture) {
    std::cerr << "Error! Couldn't create a texture from " << m_texture_path
              << " image! " << SDL_GetError() << std::endl;
    return false;
  }

  return m_image_texture != NULL;
}

void Image::clear() { }

} // namespace Engine
