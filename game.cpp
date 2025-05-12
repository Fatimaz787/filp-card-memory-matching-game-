#include "../include/game.h"
#include <iostream>
#include <sstream>
#include <fstream>

Game::Game() {
    multiplayer = false;
    level = 1;
    game_over = false;
    wait = false;
}

void Game::load_assets() {
    // Load background image
    if (!background_texture.loadFromFile("assets/cards/background.png")) {
        std::cerr << "Error: Failed to load background image.\n";
        // Load a fallback texture in case of failure
        if (!background_texture.loadFromFile("fallback_background.png")) {
            std::cerr << "Error: Failed to load fallback background image.\n";
        }
    } else {
        background.setTexture(background_texture);
    }

    // Load font
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Error: Failed to load font.\n";
    } else {
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(20, 20);
    }
}

void Game::run() {
    // Initialize window
    if (!window.isOpen()) {
        std::cerr << "Error: Failed to create the SFML window.\n";
        return;
    }

    std::string theme;
    std::string player_name1, player_name2;
    char input;

    // --- TEXT INPUT BEFORE WINDOW CREATION ---
    std::cout << "Select Theme (emoji/elemental): ";
    std::cin >> theme;
    if (theme != "emoji" && theme != "elemental") {
        std::cout << "Invalid theme selected, defaulting to 'emoji'.\n";
        theme = "emoji";
    }

    std::cout << "Load previous game? (y/n): ";
    std::cin >> input;

    if (input == 'y' || input == 'Y') {
        load_game();
    } else {
        std::cout << "Multiplayer? (y/n): ";
        std::cin >> input;
        multiplayer = (input == 'y' || input == 'Y');

        std::cout << "Enter Player 1 name: ";
        std::cin >> player_name1;
        player1 = Player(player_name1);

        if (multiplayer) {
            std::cout << "Enter Player 2 name: ";
            std::cin >> player_name2;
            player2 = Player(player_name2);
            player1.set_turn(true);
            player2.set_turn(false);
        } else {
            player1.set_turn(true);
        }

        level = 1;
        board.initialize(level, theme);
    }

    // --- NOW CREATE WINDOW & LOAD GRAPHICS ---
    window.create(sf::VideoMode(700,500), "Flip Card Memory Game");
    if (!window.isOpen()) {
        std::cerr << "Error: SFML window failed to open.\n";
        return;
    }

    load_assets();

    // --- MAIN GAME LOOP ---
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (!game_over && event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left && !wait) {
                    sf::Vector2f pos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    board.handle_click(pos);
                    wait = true;
                    flip_clock.restart();
                }
            }
        }

        // Handle waiting period between flips
        if (wait && flip_clock.getElapsedTime().asSeconds() >= 1) {
            board.update();
            if (multiplayer && !game_over)
                next_turn();
            wait = false;
        }

        // Check if the board is fully matched
        if (board.all_matched() && !game_over) {
            level += 4;
            if (level > 24) {
                game_over = true;
                save_game();
                std::cout << "Game Over! Score saved.\n";
            } else {
                board.initialize(level, theme);
            }
        }

        // Clear, draw, and display each frame
        window.clear();
        window.draw(background);
        board.draw(window);
        draw_ui();
        window.display();
    }
}

void Game::draw_ui() {
    std::ostringstream ss;

    // Display scores and moves
    if (multiplayer) {
        ss << player1.get_name() << " Score: " << player1.get_score()
           << " | Moves: " << player1.get_moves() << "\n"
           << player2.get_name() << " Score: " << player2.get_score()
           << " | Moves: " << player2.get_moves() << "\n";
    } else {
        ss << player1.get_name() << " Score: " << player1.get_score()
           << " | Moves: " << player1.get_moves() << "\n";
    }

    ss << "Level: " << level;
    text.setString(ss.str());
    window.draw(text);
}

void Game::save_game() {
    std::ofstream file("scores.txt");
    if (!file) {
        std::cerr << "Error: Failed to open file for saving game state.\n";
        return;
    }

    // Save multiplayer setting and game state
    file << multiplayer << "\n";
    file << level << "\n";
    player1.save_to_file(file);
    if (multiplayer)
        player2.save_to_file(file);
    file.close();
}

void Game::load_game() {
    std::ifstream file("scores.txt");
    if (!file) {
        std::cerr << "Error: Failed to open file for loading game state.\n";
        return;
    }

    // Load game state
    file >> multiplayer;
    file >> level;
    file.ignore();  // Ignore newline after level
    player1.load_from_file(file);
    if (multiplayer)
        player2.load_from_file(file);
    file.close();
}

void Game::next_turn() {
    if (!multiplayer) return;

    if (player1.get_turn()) {
        player1.set_turn(false);
        player2.set_turn(true);
    } else {
        player1.set_turn(true);
        player2.set_turn(false);
    }
}
