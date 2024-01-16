#include "ball.h"
#include <iostream>

#define WIDTH   1100
#define HEIGHT  900

Ball::Ball() : m_ball(sf::Vector2f(15.0f, 15.0f)), m_speed(10.0f), m_direction{true}, m_vertical_direction{true}{
    m_x = WIDTH / 2.0f;
    m_y = 100.0f;
    m_ball.setPosition(m_x, m_y);
    //m_ball.setOrigin( (15.0f / 2.0f), (15.0f / 2.0f));
    if (!m_buffer.loadFromFile("./assets/boundry.wav")) {
        std::cerr << "Failed to load boundry sound effect!" << std::endl;
    }
    m_boundry.setBuffer(m_buffer);
    m_boundry.setVolume(15);
}
[[nodiscard]]
float Ball::get_x() const {
    return m_x;
}

[[nodiscard]]
float Ball::get_y() const {
    return m_y;
}

[[nodiscard]]
bool Ball::get_status() const {
    return m_direction;
}

sf::Vector2f Ball::get_ball_origin() const {
    return m_ball.getOrigin();
}

void Ball::set_x(float pos, int32_t direction) {
    
    if (m_x < -150) {
        m_x = WIDTH / 2.0f + 150.0f; 
        m_y = 45.0f;
        m_ball.setPosition( (WIDTH / 2.0f) + 150.0f, 45.0f);
        if (m_boundry.getStatus() != sf::Music::Playing) m_boundry.play();
    }
    if (m_x > WIDTH + 150) {
        m_x = WIDTH / 2.0f;
        m_y = HEIGHT - 150.0f;
        m_ball.setPosition( (WIDTH / 2.0f) - 150.0f, (HEIGHT - 100));
        if (m_boundry.getStatus() != sf::Music::Playing) m_boundry.play();
    }


    if (m_y < 20) {
        m_vertical_direction = true;
        if (m_boundry.getStatus() != sf::Music::Playing) m_boundry.play();
    }
    else if (m_y > (HEIGHT - 20)) {
        m_vertical_direction = false;
        if (m_boundry.getStatus() != sf::Music::Playing) m_boundry.play();
    }

    if (!m_vertical_direction)  m_y -= 1.5f;
    if (m_vertical_direction)   m_y += 1.5f;

    //0 = Left Player | Other = Right Player
    [[unlikely]]
    if (!m_direction) {
        m_x += pos;
    }
    else {
        m_x -= pos;
    }

    m_ball.setPosition(m_x, m_y);
}

void Ball::set_y(bool direction) {
    m_vertical_direction = direction;
}

void Ball::set_status(bool stat) {
    m_direction = stat; 
}

[[nodiscard]]
sf::RectangleShape& Ball::get_ball_object() {
    return m_ball;
}

[[nodiscard]]
sf::FloatRect Ball::get_ball_bounding_box() {
    return m_ball.getGlobalBounds();
}
