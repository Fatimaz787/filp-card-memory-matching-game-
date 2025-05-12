#include "../include/card.h"

Card::Card(int val, const sf::Texture &front, const sf::Texture &back) {
    value = val;
    is_flipped = false;
    is_matched = false;

    front_sprite.setTexture(front);
    back_sprite.setTexture(back);
}

void Card::set_position(float x, float y) {
    position = sf::Vector2f(x, y);
    front_sprite.setPosition(position);
    back_sprite.setPosition(position);
}

void Card::draw(sf::RenderWindow &window) {
    if (is_matched || is_flipped)
        window.draw(front_sprite);
    else
        window.draw(back_sprite);
}

void Card::flip() {
    is_flipped = !is_flipped;
}

void Card::hide() {
    is_flipped = false;
}

void Card::mark_matched() {
    is_matched = true;
}

bool Card::get_flipped() const {
    return is_flipped;
}

bool Card::get_matched() const {
    return is_matched;
}

int Card::get_value() const {
    return value;
}

bool Card::contains(sf::Vector2f point) const {
    return back_sprite.getGlobalBounds().contains(point);
}

