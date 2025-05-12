#include "../include/player.h"
#include <fstream>

Player::Player() {
    name = "Unknown";
    score = 0;
    moves = 0;
    is_turn = false;
}


void Player::save_to_file(std::ofstream &out) const {
    out << name << "\n" << score << "\n" << moves << "\n";
}

void Player::load_from_file(std::ifstream &in) {
    std::getline(in, name);
    in >> score >> moves;
    in.ignore(); // To consume the newline
}


Player::Player(const std::string &player_name) {
    name = player_name;
    score = 0;
    moves = 0;
    is_turn = false;
}

void Player::increase_score() {
    score++;
}

void Player::increase_moves() {
    moves++;
}

void Player::set_turn(bool turn) {
    is_turn = turn;
}

int Player::get_score() const {
    return score;
}

int Player::get_moves() const {
    return moves;
}

std::string Player::get_name() const {
    return name;
}

bool Player::get_turn() const {
    return is_turn;
}

void Player::reset() {
    score = 0;
    moves = 0;
    is_turn = false;
}

