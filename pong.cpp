#include <iostream>
#include "pong.h"

#define WIDTH  1100
#define HEIGHT  900

//#define DEBUG

Pong::Application::Application() : m_pong(sf::VideoMode(WIDTH, HEIGHT), "Pong"), m_court_divider(sf::Vector2f(10.f, 10.f)), m_freezeDuration(sf::seconds(6.0f)) {
    //Load game font
    if (!m_font.loadFromFile("font.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        exit (-1);
    } 
    
    //Initalize Title Settings
    m_title.setFont(m_font);
    m_title.setString("PONG");
    m_title.setFillColor(sf::Color::White);
    m_title.setCharacterSize(50);
    m_title.setPosition(((WIDTH / 2.0f) - 100 ), (HEIGHT / 2.0f) - 75);

    //Initalize Player's Score
    m_SCORE_LEFT = 0;
    m_player_score.setFont(m_font);
    m_player_score.setString("00");
    m_player_score.setCharacterSize(50);
    m_player_score.setPosition(((WIDTH / 2.0f) - 195 ),  (HEIGHT / 4.75f) - 75);

    //Initalize Opponent's Score
    m_SCORE_RIGHT = 0;
    m_opponent_score.setFont(m_font);
    m_opponent_score.setString("00");
    m_opponent_score.setCharacterSize(50);
    m_opponent_score.setPosition(((WIDTH / 2.0f) + 95 ), (HEIGHT / 4.75f) - 75);

    //Load/Initialize Collision sound effect
    if (!m_buffer.loadFromFile("hit.wav")) {
        std::cerr << "Failed to load sound effect!" << std::endl;
        exit (-1);
    } 
    m_collision_effect.setBuffer(m_buffer);
    m_collision_effect.setVolume(15);

    //Load/Initialize intro music
    if(!m_start_up.openFromFile("start_up.wav")) {
        std::cerr << "Failed to load start_up music!" << std::endl;
        exit (-1);
    }
    m_start_up.setVolume(50);

    //Used to set delay for main theme / title screen
    m_freezeTimer = m_freezeDuration;

    //Lower framerate for smoother movement (?)
    m_pong.setFramerateLimit(120);

}

void Pong::Application::draw_court() {
    const float gap = 15.0f;
    for (int32_t i = 0; i < 41; ++i) {
        if (i % 2 == 0) {
            m_court_divider.setPosition(sf::Vector2f( (WIDTH / 2.0f) - 10, i * (5.0f + gap) + 50.0f));
            m_pong.draw(m_court_divider);
        }
    } 
}

void Pong::Application::update_players() {
    #ifdef DEBUG 
        std::cout << "Left's current Y: " << m_left.get_y() << std::endl;
    #endif
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if (m_left.get_y() == 20) m_collision_effect.play();
        if (m_left.get_y() > 20.0f) 
        {
           m_left.set_y(-5.0f);
           #ifdef DEBUG
           std::cout << m_left.get_y() << std::endl;
           #endif
        }
    }    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if (m_left.get_y() == (HEIGHT - 175.0f)) m_collision_effect.play();
        if (m_left.get_y() < (HEIGHT - 175.0f))
        {
           m_left.set_y(5.0f);
           std::cout << m_left.get_y() << std::endl;
        }
    }
    #ifdef DEBUG 
        std::cout << "Right's current Y: " << m_right.get_opponent_y() << std::endl;
    #endif
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
        if (m_right.get_opponent_y() == 20) m_collision_effect.play();
        if (m_right.get_opponent_y() > 20.0f) 
        {
           m_right.set_opponent_y(-5.0f);
           #ifdef DEBUG
           std::cout << m_right.get_opponent_y() << std::endl;
           #endif
        }
    }    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
        if (m_right.get_opponent_y() == (HEIGHT - 175.0f)) m_collision_effect.play();
        if (m_right.get_opponent_y() < (HEIGHT - 175.0f))
        {
           m_right.set_opponent_y(5.0f);
           std::cout << m_right.get_opponent_y() << std::endl;
        }
    }
}

void Pong::Application::draw_players() {
    m_pong.draw(m_left.get_player());
    m_pong.draw(m_right.get_opponent());
}

void Pong::Application::draw_player_score() {
    m_pong.draw(m_player_score);
}

void Pong::Application::draw_opponent_score() {
    m_pong.draw(m_opponent_score);
}

void Pong::Application::run() {
    while (m_pong.isOpen()) {
        while (m_pong.pollEvent(m_event)) {
            if (m_event.type == sf::Event::Closed)
                m_pong.close();
        }

        [[unlikely]]
        if (m_freezeTimer > sf::Time::Zero) {
            m_freezeTimer -= m_clock.restart();

            m_pong.draw(m_title);
            m_pong.display();

            if (m_start_up.getStatus() != sf::Music::Playing)    m_start_up.play();
            continue;
        }
        else m_start_up.stop();

        update_players();
        m_pong.clear(sf::Color::Black);
        draw_court();        
        draw_players();
        draw_player_score();
        draw_opponent_score();
        m_pong.display();
    }
}
