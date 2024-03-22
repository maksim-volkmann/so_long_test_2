#include "so_long.h"

void copy_map(t_game *game) {
	int i;
	printf("Line count: %d\n", game->line_count); // After setting line_count

	game->map_copy = malloc(sizeof(char *) * (game->line_count + 1));
	if (!game->map_copy) {
		prn_error("Memory allocation error for map copy");
		return;
	}

	i = 0;
	while (i < game->line_count) {
		game->map_copy[i] = ft_strdup(game->map[i]);
		if (!game->map_copy[i]) {
			prn_error("Memory allocation error for map copy line");
			return;
		}
		i++;
	}
	game->map_copy[game->line_count] = NULL; // Null-terminate the map copy
}

void flood_fill(t_game *game, int x, int y, char target, char replacement) {

	if (x < 0 || x >= game->line_count || y < 0 || y >= (int)ft_strlen(game->map[0]) || game->map_copy[x][y] != target)
		return;
	game->map_copy[x][y] = replacement;
	flood_fill(game, x + 1, y, target, replacement);
	flood_fill(game, x - 1, y, target, replacement);
	flood_fill(game, x, y + 1, target, replacement);
	flood_fill(game, x, y - 1, target, replacement);
}


int check_collectables_and_exit_reachability(t_game *game)
{
	int x;
	char current_char;
	int y;

	x = 0;
	y = 0;
	while (x < game->line_count)
	{
		y = 0;
		while ((current_char = game->map_copy[x][y]) != '\0')
		{
			// Check if the current character is a collectable or an exit
			if (current_char == 'C' || current_char == 'E')
			{
				// Check adjacent cells for 'F'
				if (!((x > 0 && game->map_copy[x-1][y] == 'F') ||
						(x < game->line_count - 1 && game->map_copy[x+1][y] == 'F') ||
						(y > 0 && game->map_copy[x][y-1] == 'F') ||
						(game->map_copy[x][y+1] == 'F')))
				{ // Right
					prn_error("A collectable or the exit is not reachable.");
					return 0; // Not all collectables/exits are reachable
				}
			}
			y++;
		}
		x++;
	}
	return 1; // All collectables and the exit are reachable
}

