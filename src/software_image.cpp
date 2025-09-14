#include "software_image.h"

#include "SDL_image.h"
#include "SDL_surface.h"
#include "vector.h"
#include <iostream>

SoftwareImage::SoftwareImage(const char* image_path, SDL_Surface* target_surface)
    :image_surface(nullptr)
{
    if (load_image(image_path, target_surface))
    {
        draw(target_surface);
    }
}

SoftwareImage::~SoftwareImage()
{
    clear();
    std::cout << "SoftwareImage destroy" << std::endl;
}

void SoftwareImage::draw(SDL_Surface* target_surface)
{
    SDL_BlitScaled(image_surface, NULL, target_surface, &position_and_size);
}

void SoftwareImage::set_positon(const Vector2i& position)
{
    position_and_size.x = position.x;
    position_and_size.y = position.y;
}

void SoftwareImage::set_size(const Vector2i& size)
{
    position_and_size.w = size.x;
    position_and_size.h = size.y;
}

bool SoftwareImage::load_image(const char* image_path, SDL_Surface* target_source)
{
    if (image_surface){
        SDL_FreeSurface(image_surface);
        image_surface = nullptr;
    }

    SDL_Surface* new_image_surface = IMG_Load(image_path);
    if (!new_image_surface){
        std::cerr << "Error! Couldn't load the "<< image_path << " image!" << IMG_GetError() << std::endl;
        return false;
    }

    image_surface = SDL_ConvertSurface(new_image_surface, target_source->format, 0);
    set_size(Vector2i{image_surface->w, image_surface->h});
    
    SDL_FreeSurface(new_image_surface);
    return true;
}

void SoftwareImage::clear()
{
    SDL_FreeSurface(image_surface);
    image_surface = NULL;
}