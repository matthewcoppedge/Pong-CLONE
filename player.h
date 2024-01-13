#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Player {
    public:
       Player();
       float get_x()          const;
       float get_y()          const;
       float get_opponent_y() const;
       float get_opponent_x() const;
       void  set_x(float pos);
       void  set_y(float pos);
       void  set_opponent_x(float pos);
       void  set_opponent_y(float pos);
       sf::RectangleShape& get_player();
       sf::RectangleShape& get_opponent();

    private:
        float               m_x;
        float               m_y;
        float               m_X;
        float               m_Y;
        sf::RectangleShape  m_player;
        sf::RectangleShape  m_opponent;
};
