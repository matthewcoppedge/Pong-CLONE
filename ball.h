#pragma once

#include <SFML/Graphics.hpp>
#include "player.h"

class Ball {
    public:
        Ball();
        float get_x() const;
        float get_y() const;
        sf::Vector2f get_ball_origin() const;
        void  set_x(float pos, int32_t direction);
        void  set_y(bool direction);
        void  set_status(bool stat);
        bool  get_status() const;
        sf::RectangleShape& get_ball_object();
        sf::FloatRect       get_ball_bounding_box();

    private:
        sf::RectangleShape  m_ball;
        sf::FloatRect       m_ball_bounding_box;
        sf::SoundBuffer     m_buffer;
        sf::Sound           m_boundry;
        float               m_x;
        float               m_y;
        float               m_speed;
        bool                m_direction;
        bool                m_vertical_direction;
};
