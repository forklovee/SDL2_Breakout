#include "software_image.h"

#include "commons.h"

SoftwareImage::SoftwareImage(const char* image_path, SDL_Surface* target_surface)
    :image_surface(nullptr)
{
    if (load_image(image_path))
    {
        SDL_BlitSurface(image_surface, NULL, target_surface, NULL);
    }
}

SoftwareImage::~SoftwareImage()
{
    clear();
    std::cout << "SoftwareImage destroy" << std::endl;
}

bool SoftwareImage::load_image(const char* image_path)
{
    image_surface = SDL_LoadBMP(image_path);
    if (!image_surface){
        std::cerr << "Error! Couldn't load the image!" << std::endl;
        return false;
    }
    return true;
}

void SoftwareImage::clear()
{
    SDL_FreeSurface(image_surface);
    image_surface = NULL;
}