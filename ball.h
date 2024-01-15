#pragma once

#include <SFML/Graphics.hpp>

class Ball {
    public:
        Ball();
        float get_x() const;
        float get_y() const;
        void  set_x(float pos, int32_t direction);
        void  set_y(float pos, int32_t direction);
        bool  get_status() const;
        sf::RectangleShape& get_ball_object();
        sf::FloatRect       get_ball_bounding_box();

    private:
        sf::RectangleShape  m_ball;
        sf::FloatRect       m_ball_bounding_box;
        float               m_x;
        float               m_y;
        float               m_speed;
        bool                m_direction;
};
