#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <string>
#include "player.h"

void save_single_player_score(const Player& player);
void save_multiplayer_score(const Player& p1, const Player& p2, std::string round_winner);
void show_previous_scores(bool multiplayer);

#endif

