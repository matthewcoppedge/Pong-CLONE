#include "ball.h"

#define WIDTH   1100
#define HEIGHT  900

Ball::Ball() : m_ball(sf::Vector2f(15.0f, 15.0f)), m_speed(10.0f), m_direction{true}{
    m_x = WIDTH / 2.0f;
    m_y = (HEIGHT / 2.0f) - 150.0f;
    m_ball.setPosition(WIDTH/ 2.0f, HEIGHT/ 2.0 - 150);
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

void Ball::set_x(float pos, int32_t direction) {
    //1 = Left Player | Other = Right Player
    [[unlikely]]
    if (direction && m_direction) {
        m_x += pos;
        m_direction = false;
    }
    else if (!direction && m_direction){
        m_x -= pos;
        m_direction = true;
    }

    m_ball.setPosition(m_x, m_y);
}

void Ball::set_y(float pos, int32_t direction) {
    m_y += pos;
    m_ball.setPosition(m_x, m_y);
}

[[nodiscard]]
sf::RectangleShape& Ball::get_ball_object() {
    return m_ball;
}

[[nodiscard]]
sf::FloatRect Ball::get_ball_bounding_box() {
    return m_ball.getGlobalBounds();
}
