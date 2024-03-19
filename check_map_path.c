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
		printf("Copied line %d: %s\n", i, game->map_copy[i]);
		if (!game->map_copy[i]) {
			prn_error("Memory allocation error for map copy line");
			return;
		}
		i++;
	}
	game->map_copy[game->line_count] = NULL; // Null-terminate the map copy
}

void flood_fill(t_game *game, int x, int y, char target, char replacement) {

	// 1111111111
	// 1000000001
	// 1P0C0000E1
	// 1000000001
	// 1111111111

	// 1111111111
	// 1FFFFFFFF1
	// 1FFCFFFFE1
	// 1FFFFFFFF1
	// 1111111111
	// printf("flood_fill cekas\n");
	// printf("game->line_count: %d\n", game->line_count);
	// printf("(int)ft_strlen(game->map[0]): %d\n", (int)ft_strlen(game->map[0]));
	// printf("target: %c\n", target);
	// printf("replacement: %c\n", replacement);
	// printf("x: %d\n", x);
	// printf("y: %d\n", y);
	if (x < 0 || x >= game->line_count || y < 0 || y >= (int)ft_strlen(game->map[0]) || game->map_copy[x][y] != target) {
		return;
	}
	// printf("flood_fill cekas2\n");
	game->map_copy[x][y] = replacement;
	// printf("Flood fill: x: %d, y: %d\n", x, y);

	flood_fill(game, x + 1, y, target, replacement); // Down
	flood_fill(game, x - 1, y, target, replacement); // Up
	flood_fill(game, x, y + 1, target, replacement); // Right
	flood_fill(game, x, y - 1, target, replacement); // Left
}

// bool check_adjacent_for_f(t_game *game, int x, int y) {
// 	// Check boundaries and then check for 'F' in adjacent cells
// 	if (x > 0 && game->map_copy[x-1][y] == 'F') return true;
// 	if (x < game->line_count - 1 && game->map_copy[x+1][y] == 'F') return true;
// 	if (y > 0 && game->map_copy[x][y-1] == 'F') return true;
// 	if (game->map_copy[x][y+1] == 'F') return true; // Assuming each row is null-terminated

// 	return false;
// }

// void check_reachability(t_game *game) {
// 	bool valid = true;
// 	int i = 0;
// 	int j;

// 	printf("\033[34mChecking reachability...\033[0m\n");
// 	while (i < game->line_count && valid) {
// 		j = 0;
// 		while (game->map_copy[i][j] != '\0' && valid) {
// 			if (game->map_copy[i][j] == 'C' || game->map_copy[i][j] == 'E' || game->map_copy[i][j] == 'P') {
// 				if (!check_adjacent_for_f(game, i, j)) {
// 					valid = false; // An essential element is not reachable
// 					prn_error("Not all essential elements are reachable.");
// 					return;
// 				}
// 			}
// 			j++;
// 		}
// 		i++;
// 	}

// 	if (valid) {
// 		ft_printf("All essential elements are reachable.\n");
// 	}
// }

int check_collectables_and_exit_reachability(t_game *game)
{
	int x;
	char current_char;
	int y;

	x = 0;
	y = 0;
	while (x < game->line_count) {
		y = 0;
		while ((current_char = game->map_copy[x][y]) != '\0') {
			// Check if the current character is a collectable or an exit
			if (current_char == 'C' || current_char == 'E') {
				// Check adjacent cells for 'F'
				if (!((x > 0 && game->map_copy[x-1][y] == 'F') || // Up
						(x < game->line_count - 1 && game->map_copy[x+1][y] == 'F') || // Down
						(y > 0 && game->map_copy[x][y-1] == 'F') || // Left
						(game->map_copy[x][y+1] == 'F'))) { // Right
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

