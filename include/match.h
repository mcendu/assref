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

typedef struct aref_match {
	char red[56];
	char blue[56];
	int red_score;
	int blue_score;
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

#ifdef __cplusplus
}
#endif

#endif /* !_AREF__MATCH_H */
