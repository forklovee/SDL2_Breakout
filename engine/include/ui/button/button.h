#pragma once

#include "core/game.h"
#include "graphics/image/text_image.h"
#include "graphics/object2d.h"

#include "math/vector.h"
#include <SDL_ttf.h>
#include <cstdint>
#include <string>

namespace Engine{

class Button: public Object2D
{
public:
    Button() = default;
    Button(std::string text, bool is_togglable = false,
        Vector2<int> position = {}, Vector2<int> size = {64},
        TTF_Font* font = Engine::default_font);
    
    virtual ~Button() override;

    void render(SDL_Renderer* m_renderer) override;
    void handle_event(const SDL_Event& event) override;

    void set_position(const Vector2<int>& position) override;

    const bool& get_is_pressed() const;
    void set_is_pressed(const bool& pressed);

private:
    std::string m_text;

    bool m_is_pressed{false};
    bool m_is_toggleable{false};

    Vector3<uint8_t> m_default_color{255};
    uint8_t m_default_alpha{255};
    Vector3<uint8_t> m_hover_color{255};
    uint8_t m_hover_alpha{255};
    Vector3<uint8_t> m_pressed_color{255};
    uint8_t m_pressed_alpha{255};

    TextImage m_button_text_image;
    Image m_background_image;
};

}