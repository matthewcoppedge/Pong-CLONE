#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "player.h"

namespace Pong {
class Application {
    public:
        Application();
        void run();

    private:
        void draw_court();
        void draw_players();
        void update_players();
        void draw_player_score();
        void draw_opponent_score();

        int32_t             m_SCORE_LEFT;
        int32_t             m_SCORE_RIGHT;

        sf::RenderWindow    m_pong;
        sf::Event           m_event;
        sf::Font            m_font;
        sf::Text            m_title;
        sf::Text            m_player_score;
        sf::Text            m_opponent_score;
        sf::SoundBuffer     m_buffer;
        sf::Sound           m_collision_effect;
        sf::RectangleShape  m_court_divider;
        sf::Music           m_start_up;
        sf::Clock           m_clock;
        sf::Time            m_freezeDuration;
        sf::Time            m_freezeTimer;

        Player              m_left;
        Player              m_right;
};
}
