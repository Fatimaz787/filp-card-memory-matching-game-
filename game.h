#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "player.h"
#include "board.h"

class Game {
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    sf::Texture background_texture;
    sf::Sprite background;

    Player player1;
    Player player2;
    bool multiplayer;
	void save_game();
	void load_game();

    Board board;
    int level;

    bool game_over;
    bool wait;
    sf::Clock flip_clock;

    void draw_ui();
    void next_turn();
    void load_assets();

public:
    Game();
    void run();
};

#endif

