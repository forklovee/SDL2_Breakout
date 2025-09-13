#ifndef SOFTWARE_IMAGE_H
#define SOFTWARE_IMAGE_H

#include "SDL2/SDL_rect.h"
#include "vector.h"

class SDL_Surface;

class SoftwareImage{
public:
    SoftwareImage(const char* image_path, SDL_Surface* target_surface);
    ~SoftwareImage();

    void draw(SDL_Surface* target_surface);

    void set_positon(const Vector2i& position);
    void set_size(const Vector2i& size);

private:
    bool load_image(const char* image_path, SDL_Surface* target_source);
    void clear();

private:
    SDL_Surface* image_surface;
    SDL_Rect position_and_size;
};

#endif