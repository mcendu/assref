/*
 * SPDX-License-Identifier: GPL-2.0-or-later
 * Copyright (C) 2022 McEndu et al.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef _AREF__MATCH_H
#define _AREF__MATCH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <playerlist.h>

/**
 * @brief Represents the current state of a match.
 */
typedef struct aref_match {
	/**
	 * Name of red team.
	 */
	char red[56];
	/**
	 * Name of blue team.
	 */
	char blue[56];
	/**
	 * Number of wins for team red.
	 */
	int red_score;
	/**
	 * Number of wins for team blue.
	 */
	int blue_score;
	/**
	 * Number of wins required to win the match.
	 */
	int first_to;
} aref_match;

/**
 * @brief Get if a player can participate in the current match and
 * which team the player is on.
 *
 * @param match A match.
 * @param player The player data to query.
 * @return 1 if the player is on team red, -1 if on team blue, 0
 * otherwise.
 */
extern int aref_player_in_match(aref_match *match, aref_player *player);

/**
 * @brief Determine the winner from the scores each player recieved.
 *
 * @param red_scores A list of individual scores for team red.
 * @param red_team_size Number of team red players in the game.
 * @param blue_scores A list of individual scores for team red.
 * @param blue_team_size Number of team blue players in the game.
 * @return Positive number if red wins, Negative if blue wins, or 0 in
 * a tie.
 */
extern int aref_aggregate_score(int *red_scores, int red_team_size,
								int *blue_scores, int blue_team_size);

#ifdef __cplusplus
}
#endif

#endif /* !_AREF__MATCH_H */
