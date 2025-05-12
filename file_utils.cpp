#include "../include/file_utils.h"
#include <fstream>
#include <ctime>
#include <iostream>

std::string current_time() {
    time_t now = time(0);
    char* dt = ctime(&now);
    return std::string(dt);
}

void save_single_player_score(const Player& player) {
    std::ofstream file("scores_single.txt", std::ios::app);
    if (file.is_open()) {
        file << player.get_name() << "," << player.get_score() << "," << player.get_moves() << "," << current_time();
        file.close();
    }
}

void save_multiplayer_score(const Player& p1, const Player& p2, std::string round_winner) {
    std::ofstream file("scores_multi.txt", std::ios::app);
    if (file.is_open()) {
        file << p1.get_name() << "," << p1.get_score() << "," << p1.get_moves() << " | ";
        file << p2.get_name() << "," << p2.get_score() << "," << p2.get_moves();
        file << " | Winner: " << round_winner << " | " << current_time();
        file.close();
    }
}

void show_previous_scores(bool multiplayer) {
    std::ifstream file(multiplayer ? "scores_multi.txt" : "scores_single.txt");
    std::string line;
    if (file.is_open()) {
        std::cout << "\n--- Previous " << (multiplayer ? "Multiplayer" : "Single Player") << " Scores ---\n";
        while (getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cout << "No previous score data found.\n";
    }
}

