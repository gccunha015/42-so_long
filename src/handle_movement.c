/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoelho- <gcoelho-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:32:19 by gcoelho-          #+#    #+#             */
/*   Updated: 2022/02/19 19:01:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	get_new_location(t_game *game, int key_code, int *new_location);
static int	has_collided(t_game *game, int *new_location);
static void	change_player_location(t_game *game, int key_code,
				int *new_location);

int	handle_movement(t_game *game, int key_code)
{
	int	new_location[2];

	if (!game->player.row)
		return (0);
	get_new_location(game, key_code, new_location);
	if (has_collided(game, new_location))
		return (1);
	change_player_location(game, key_code, new_location);
	return (0);
}

static void	get_new_location(t_game *game, int key_code, int *new_location)
{
	t_player	*p;

	p = &game->player;
	new_location[0] = p->row;
	new_location[1] = p->column;
	if (key_code == XK_W)
		new_location[0]--;
	else if (key_code == XK_S)
		new_location[0]++;
	else if (key_code == XK_A)
		new_location[1]--;
	else if (key_code == XK_D)
		new_location[1]++;
}

static int	has_collided(t_game *game, int *new_location)
{
	t_matrix	*m;
	char		tile_type;

	m = game->map;
	tile_type = ((char *) m->values[new_location[0]])[new_location[1]];
	if (tile_type == WALL
		|| (tile_type == EXIT
			&& game->collectibles))
		return (1);
	else if (tile_type == COLLECTIBLE)
		game->collectibles--;
	return (0);
}

static void	change_player_location(t_game *game, int key_code,
				int *new_location)
{
	t_matrix	*m;
	t_player	*p;
	char		tile_type;

	m = game->map;
	p = &game->player;
	tile_type = ((char *) m->values[new_location[0]])[new_location[1]];
	p->moves++;
	((char *) m->values[p->row])[p->column] = EMPTY;
	if (tile_type == EXIT && !game->collectibles)
	{
		p->row = 0;
		return ;
	}
	((char *) m->values[new_location[0]])[new_location[1]] = PLAYER;
	if (key_code == XK_W)
		p->row--;
	else if (key_code == XK_S)
		p->row++;
	else if (key_code == XK_A)
		p->column--;
	else if (key_code == XK_D)
		p->column++;
}
