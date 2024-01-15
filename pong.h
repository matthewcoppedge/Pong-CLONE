#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "player.h"
#include "ball.h"

namespace Pong {
class Application {
    public:
        Application();
        void run();

    private:
        void draw_court();
        void draw_players();
        void update_players();
        void draw_players_score();
        void shader_logic();
        void update_ball();

        int32_t             m_SCORE_LEFT;
        int32_t             m_SCORE_RIGHT;
        float               m_start_time;

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
        sf::Music           m_background;
        sf::Clock           m_clock;
        sf::Time            m_freezeDuration;
        sf::Time            m_freezeTimer;

        sf::Shader          m_shader;

        Player              m_left;
        Player              m_right;

        Ball                m_tennis_ball;
};
}
