#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include "pong.h"

#define WIDTH  1100
#define HEIGHT  900

//#define DEBUG


Pong::Application::Application() : m_pong(sf::VideoMode(WIDTH, HEIGHT), "Pong"), m_court_divider(sf::Vector2f(10.f, 10.f)), m_freezeDuration(sf::seconds(6.0f)), m_start_time(0.0f) {
    //Load game font
    if (!m_font.loadFromFile("./assets/font.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        exit (-1);
    } 

    //Load/Initialize Shader 
    if (!m_shader.loadFromFile("distortion.frag", sf::Shader::Fragment)) {
        std::cerr << "Failed to load fragment shader!" << std::endl;
        std::cout << m_shader.getNativeHandle() << std::endl;
    }
    m_shader.setUniform("iResolution", sf::Vector3f(WIDTH, HEIGHT, 1.0f));
    
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
    if (!m_buffer.loadFromFile("./assets/hit.wav")) {
        std::cerr << "Failed to load sound effect!" << std::endl;
        exit (-1);
    } 
    m_collision_effect.setBuffer(m_buffer);
    m_collision_effect.setVolume(15);

    //Load/Initialize intro music
    if(!m_start_up.openFromFile("./assets/start_up.wav")) {
        std::cerr << "Failed to load start_up music!" << std::endl;
        exit (-1);
    }
    m_start_up.setVolume(50);
    
    //Load/Initialize background music
    if(!m_background.openFromFile("./assets/background.wav")) {
        std::cerr << "Failed to load background music!" << std::endl;
        exit (-1);
    }
    m_background.setVolume(3);

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
        if (m_left.get_y() == 20) {
            m_collision_effect.play();
        }
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
           #ifdef DEBUG
           std::cout << m_left.get_y() << std::endl;
           #endif
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
           #ifdef DEBUG
           std::cout << m_right.get_opponent_y() << std::endl;
           #endif
        }
    }
}

void Pong::Application::draw_players() {
    m_pong.draw(m_left.get_player());
    m_pong.draw(m_right.get_opponent());
}

void Pong::Application::draw_players_score() {
    if ((m_tennis_ball.get_x() <= -150)) {
        m_SCORE_RIGHT++;
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << m_SCORE_RIGHT;
        std::string stringValue = ss.str();
        m_opponent_score.setString(stringValue);
    }
    if ( (m_tennis_ball.get_x() >  WIDTH + 150)) {
        m_SCORE_LEFT++;
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << m_SCORE_LEFT;
        std::string stringValue = ss.str();
        m_player_score.setString(stringValue);
    }
    m_pong.draw(m_player_score);
    m_pong.draw(m_opponent_score);
}

void Pong::Application::update_ball() {
    

    [[unlikely]]
    if (m_tennis_ball.get_ball_bounding_box().intersects(m_left.get_player_box())) {
        std::cout << m_tennis_ball.get_y() << std::endl;
        std::cout << m_left.get_y() << std::endl;
        if (m_collision_effect.getStatus() != sf::Music::Playing)
            m_collision_effect.play();
        m_tennis_ball.set_status(false);
        if (m_tennis_ball.get_y()  < m_left.get_y()) {
            m_tennis_ball.set_y(false);
            std::cout << "Here left 1st!" << std::endl;
        }
        else {
            m_tennis_ball.set_y(true);
            std::cout << "Here left 2nd!" << std::endl;
        }
    }

    else if (m_tennis_ball.get_ball_bounding_box().intersects(m_right.get_opponent_box())) {
        std::cout << m_tennis_ball.get_y() << std::endl;
        std::cout << m_right.get_y() << std::endl;
        if (m_collision_effect.getStatus() != sf::Music::Playing)
            m_collision_effect.play();
        m_tennis_ball.set_status(true);
        if (m_tennis_ball.get_y() < m_right.get_y()) {
            m_tennis_ball.set_y(false);
            std::cout << "Here right 1st" << std::endl;
        }
        else {
            m_tennis_ball.set_y(true);
            std::cout << "Here right 2nt" << std::endl;
        }
    }

     m_tennis_ball.set_x(5.0f, 0);
}

void Pong::Application::shader_logic() {
    float currentTime = static_cast<float>(sf::Clock().getElapsedTime().asSeconds());
    float deltaTime   = currentTime - m_start_time;
    m_shader.setUniform("iTime", currentTime);
    m_shader.setUniform("iTimeDelta", deltaTime);
    
    float channelTimes[4] = {
        m_clock.getElapsedTime().asSeconds(),
        m_clock.getElapsedTime().asSeconds() * 0.5,
        m_clock.getElapsedTime().asSeconds() * 2.0f,
        m_clock.getElapsedTime().asSeconds() * 0.75f,
    };
    m_shader.setUniformArray("iChannelTime", channelTimes, 4);
    m_shader.setUniform("iFrame", m_clock.getElapsedTime().asMilliseconds());
    sf::Vector3f channelResolutions[4] {
        sf::Vector3f(WIDTH, HEIGHT, 1.0f),
        sf::Vector3f(WIDTH, HEIGHT, 1.0f),
        sf::Vector3f(WIDTH, HEIGHT, 1.0f),
        sf::Vector3f(WIDTH, HEIGHT, 1.0f)
    };
    m_shader.setUniformArray("iChannelResolution", channelResolutions, 4);
    sf::Vector2i mousePos = sf::Mouse::getPosition(m_pong);
    sf::Vector2i mouseClicksPos = sf::Mouse::isButtonPressed(sf::Mouse::Left) ? sf::Mouse::getPosition(m_pong) : sf::Vector2i(-1, -1);

    std::vector<float> iMouseValues = {static_cast<float>(mousePos.x), static_cast<float>(mousePos.y), static_cast<float>(mouseClicksPos.x), static_cast<float>(mouseClicksPos.y)};
    m_shader.setUniformArray("iMouse", iMouseValues.data(), iMouseValues.size());

    sf::Time current_Time = m_clock.getElapsedTime();
    std::vector<float> iDateValues = {current_Time.asSeconds(), current_Time.asMilliseconds(), current_Time.asSeconds() / 60.f, current_Time.asSeconds() / 3600.0f};
    m_shader.setUniformArray("iDateValues", iDateValues.data(), iDateValues.size());
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

        if (m_background.getStatus() != sf::Music::Playing) m_background.play();
        update_players();
        update_ball();
        m_pong.clear(sf::Color::Black);
        draw_court();        
        draw_players();
        draw_players_score();
        m_pong.draw(m_tennis_ball.get_ball_object());
        m_pong.display();
    }
}
