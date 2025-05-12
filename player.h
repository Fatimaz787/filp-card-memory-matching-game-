#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string name;
    int score;
    int moves;
    bool is_turn;

public:
    Player();
    Player(const std::string &player_name);

    void increase_score();
    void increase_moves();
    void set_turn(bool turn);
    void save_to_file(std::ofstream &out) const;
	void load_from_file(std::ifstream &in);

    int get_score() const;
    int get_moves() const;
    std::string get_name() const;
    bool get_turn() const;

    void reset();
};

#endif

