#include "so_long.h"

t_game	*create_game(void)
{
	t_game	*game;

	game = malloc(sizeof(game));
	if (!game)
		return (NULL);
	game.map = NULL;
	game.mlx = NULL;
	game.window = NULL;
	game.error = NULL;
	return (game);
}