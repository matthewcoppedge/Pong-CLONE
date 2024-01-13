#include "player.h"

#define WIDTH  1100
#define HEIGHT  900

Player::Player() : m_player(sf::Vector2f(145.0f, 20.0f)), m_opponent(sf::Vector2f(145.0f, 20.0f)) {
    m_x = 30.0f;
    m_y = 375.0f;
    m_player.setPosition(m_x, m_y);
    m_player.rotate(90.0f);

    m_X = WIDTH - 15.0f;
    m_Y = 375.0f;
    m_opponent.setPosition(m_X, m_Y);
    m_opponent.rotate(90.0f);
}

[[nodiscard]]
float Player::get_x() const {
    return m_x;
}

[[nodiscard]]
float Player::get_y() const {
    return m_y;
}

[[nodiscard]]
float Player::get_opponent_y() const {
    return m_Y;
}

[[nodiscard]]
float Player::get_opponent_x() const {
    return m_X;
}

void Player::set_y(float pos) {
    m_y += pos;
    m_player.setPosition(m_x, m_y + pos);
}

void Player::set_x(float pos) {
    m_x += pos;
}

void Player::set_opponent_y(float pos) {
    m_Y += pos;
    m_opponent.setPosition(m_X, m_Y + pos);
}

void Player::set_opponent_x(float pos) {
    m_X += pos;
}

sf::RectangleShape& Player::get_player() {
    return m_player;
}

sf::RectangleShape& Player::get_opponent() {
    return m_opponent;
}
