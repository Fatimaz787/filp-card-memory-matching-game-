#include "../include/board.h"
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include<fstream>
#include <iostream> // <-- Required for std::cerr
#include <SFML/Graphics.hpp> // <-- Required for sf::Texture
#include <vector>
Board::Board() {
    first_card = 0;
    second_card = 0;
    can_flip = true;
    std::srand(static_cast<unsigned>(std::time(0)));

    // Define the theme (this could come from elsewhere, e.g., a configuration file or user input)
    std::string theme = "elemental";  // Example theme

    // Now call the load_textures function with the theme
    load_textures(theme);  // Pass the theme directly
}

#include <iostream> // <-- Required for std::cerr
#include <SFML/Graphics.hpp> // <-- Required for sf::Texture
#include <vector>

void Board::load_textures(const std::string& theme) {
    // Load back texture
    if (!card_back_texture.loadFromFile("assets/cards/" + theme + "/back.png")) {
        std::cerr << "Failed to load back texture!" << std::endl;
    }

    // Set up card face names based on the theme
    std::string names[6];

    if (theme == "emoji") {
        names[0] = "1"; names[1] = "2"; names[2] = "3";
        names[3] = "4"; names[4] = "5"; names[5] = "6";
    } else if (theme == "elemental") {
        names[0] = "fire"; names[1] = "water"; names[2] = "earth";
        names[3] = "waterdrop"; names[4] = "lightning"; names[5] = "air";
    }

    face_textures.clear();

    for (int i = 0; i < 6; ++i) {
        sf::Texture texture;
        std::string path = "assets/cards/" + theme + "/" + names[i] + ".png";
        if (!texture.loadFromFile(path)) {
            std::cerr << "Failed to load texture: " << path << std::endl;
        }
        face_textures.push_back(texture);
    }   
	// Load textures based on the names array
    for (int i = 0; i < 6; i++) {
        sf::Texture texture;
        std::string path = "assets/cards/" + theme + "/" + names[i] + ".png";
        texture.loadFromFile(path);
        card_textures[i] = texture;
    }
}
  
  


void Board::initialize(int level, const std::string& theme) {
    cards.clear();
    card_values.clear();
    first_card = 0;
    second_card = 0;
    can_flip = true;

    total_pairs = level / 2;
    int i;

    // Create pairs
    for (i = 0; i < total_pairs; i++) {
        card_values.push_back(i);
        card_values.push_back(i);
    }

    shuffle_cards();
    load_textures(theme);  // Pass theme here
    setup_cards(level);
}


void Board::shuffle_cards() {
    std::random_shuffle(card_values.begin(), card_values.end());
}

void Board::setup_cards(int level) {
    int cols = 6;
    int rows = (level + cols - 1) / cols;
    float x_start = 100, y_start = 100;
    float spacing = 10;

    for (int i = 0; i < level; i++) {
        int val = card_values[i];
        Card card(val, card_textures[val], card_back_texture);

        float x = x_start + (i % cols) * (80 + spacing);
        float y = y_start + (i / cols) * (80 + spacing);
        card.set_position(x, y);

        cards.push_back(card);
    }
}

void Board::draw(sf::RenderWindow &window) {
    for (unsigned int i = 0; i < cards.size(); i++) {
        cards[i].draw(window);
    }
}

void Board::handle_click(sf::Vector2f mouse_pos) {
    if (!can_flip) return;

    for (unsigned int i = 0; i < cards.size(); i++) {
        if (!cards[i].get_flipped() && !cards[i].get_matched() &&
            cards[i].contains(mouse_pos)) {
            cards[i].flip();

            if (!first_card)
                first_card = &cards[i];
            else if (!second_card && &cards[i] != first_card) {
                second_card = &cards[i];
                can_flip = false;
            }

            break;
        }
    }
}

void Board::update() {
    if (first_card && second_card) {
        if (first_card->get_value() == second_card->get_value()) {
            first_card->mark_matched();
            second_card->mark_matched();

            // Update the score based on the current player's turn
            if (player1.get_turn()) {
                player1.increase_score();
            } else if (player2.get_turn()) {
                player2.increase_score();
            }
        } else {
            first_card->hide();
            second_card->hide();
        }

        first_card = 0;
        second_card = 0;
        can_flip = true;
    }
}


bool Board::all_matched() const {
    for (unsigned int i = 0; i < cards.size(); i++) {
        if (!cards[i].get_matched())
            return false;
    }
    return true;
}

