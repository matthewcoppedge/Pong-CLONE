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
       sf::Vector2f get_origin_player() const; 
       sf::Vector2f get_origin_opponent() const; 
       void  set_x(float pos);
       void  set_y(float pos);
       void  set_opponent_x(float pos);
       void  set_opponent_y(float pos);
       sf::FloatRect get_player_box();
       sf::FloatRect get_opponent_box();
       sf::RectangleShape& get_player();
       sf::RectangleShape& get_opponent();

    private:
        float               m_x;
        float               m_y;
        float               m_X;
        float               m_Y;
        sf::RectangleShape  m_player;
        sf::RectangleShape  m_opponent;
        sf::FloatRect       m_player_bounding_box;
        sf::FloatRect       m_opponent_bounding_box;
};
