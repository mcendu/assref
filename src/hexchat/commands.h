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

#ifndef _AREFXCHAT__COMMANDS_H
#define _AREFXCHAT__COMMANDS_H

struct arefxchat_command {
	/**
	 * @brief The name of the command.
	 */
	const char *name;
	/**
	 * @brief The help text of the command.
	 */
	const char *helptext;
	/**
	 * @brief A callback run when calling this command.
	 *
	 * Unlike in the HexChat plugin API, indices are zero based instead
	 * of one based. word[0] refers not to the command name but to the
	 * first parameter.
	 */
	void (*callback)(struct plugindata *, char **word, char **word_eol);
};

/* Help */
extern void arefxchat_help(struct plugindata *, char **, char **);

/* Database */
extern void arefxchat_load(struct plugindata *, char **, char **);

/* Misc functions */
extern int init_database(struct plugindata *);
extern int load_database(struct plugindata *, char *path);

#endif /* !_AREFXCHAT__COMMANDS_H */
