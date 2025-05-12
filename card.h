#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>

class Card {
private:
    int value;
    bool is_flipped;
    bool is_matched;
    sf::Sprite front_sprite;
    sf::Sprite back_sprite;
    sf::Vector2f position;

public:
    Card(int val, const sf::Texture &front, const sf::Texture &back);
    
    void set_position(float x, float y);
    void draw(sf::RenderWindow &window);
    
    void flip();
    void hide();
    void mark_matched();
    
    bool get_flipped() const;
    bool get_matched() const;
    int get_value() const;

    bool contains(sf::Vector2f point) const;
};

#endif

