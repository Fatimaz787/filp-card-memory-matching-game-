#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>
#include "card.h"
#include "player.h"

class Board {
private:
    Player player1;
    Player player2;
    std::vector<Card> cards;
    std::vector<int> card_values;

    sf::Texture card_back_texture;  // ? only one declaration
    std::vector<sf::Texture> face_textures;
    std::map<int, sf::Texture> card_textures;

    int total_pairs;
    Card* first_card;
    Card* second_card;

    bool can_flip;

    void load_textures(const std::string& theme);
    void shuffle_cards();
    void setup_cards(int level);

public:
    Board();
    void initialize(int level, const std::string& theme); // level defines number of cards
    void draw(sf::RenderWindow &window);

    void handle_click(sf::Vector2f mouse_pos);
    void update();
    bool all_matched() const;
};

#endif

