#ifndef SOFTWARE_IMAGE_H
#define SOFTWARE_IMAGE_H

class SDL_Surface;

class SoftwareImage{
public:
    SoftwareImage(const char* image_path, SDL_Surface* target_surface);
    ~SoftwareImage();


private:
    bool load_image(const char* image_path);
    void clear();

private:
    SDL_Surface* image_surface;
};

#endif