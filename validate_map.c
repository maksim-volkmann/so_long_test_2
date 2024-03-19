#include "so_long.h"

void check_map_line_lengths(t_game *game)
{
	int i;
	size_t line_length;

	if (game->map == NULL || game->map[0] == NULL) {
		prn_error("Map is not loaded or is empty");
		return;
	}

	i = 0;
	line_length = ft_strlen(game->map[0]);
	while (game->map[i] != NULL) {
		if (ft_strlen(game->map[i]) != line_length) {
			prn_error("Map lines are not of the same length!");
			return;
		}
		i++;
	}

	// Additional checks can be added here if needed
	ft_printf("All map lines are consistent.\n");
}

void check_map_for_valid_characters(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] != '1' && game->map[i][j] != 'P' &&
				game->map[i][j] != 'E' && game->map[i][j] != 'C' &&
				game->map[i][j] != '0')
			{
				prn_error("Map contains invalid characters!");
				return;
			}
			j++;
		}
		i++;
	}
	ft_printf("Map characters are valid.\n");
}

void check_map_walls(t_game *game)
{
    int i, j;

    // Check first and last row
    i = 0;
    j = 0;
    while (game->map[0][j]) // Check first line
    {
        if (game->map[0][j] != '1')
        {
            prn_error("First row does not consist of only walls ('1')");
            return;
        }
        j++;
    }

    j = 0;
    while (game->map[game->line_count - 1][j]) // Check last line
    {
        if (game->map[game->line_count - 1][j] != '1')
        {
            prn_error("Last row does not consist of only walls ('1')");
            return;
        }
        j++;
    }

    // Check first and last character of each line
    while (game->map[i] != NULL)
    {
        if (game->map[i][0] != '1' || game->map[i][ft_strlen(game->map[i]) - 1] != '1')
        {
            prn_error("First or last character of a row is not a wall ('1')");
            return;
        }
        i++;
    }

    ft_printf("Map walls are valid.\n");
}
void check_map_characters_count(t_game *game)
{
	int i;
	int	j;
	int exit_count = 0;
	int collectible_count = 0;
	int start_position_count = 0;

	// for (int i = 0; &game->map[i] != NULL; i++) {
	// 	printf("\033[32m%s\033[0m\n", game->map[i]);
	// }
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'E') exit_count++;
			else if (game->map[i][j] == 'C') collectible_count++;
			else if (game->map[i][j] == 'P')
			{
				 printf("Found P at i=%d, j=%d\n", i, j);
				game->player_x = i;
				game->player_y = j;
				start_position_count++;
			}
			j++;
		}
		i++;
	}

	// Check for the map requirements
	if (exit_count != 1)
	{
		prn_error("Map must contain exactly one exit ('E')!");
		return;
	}
	if (collectible_count < 1)
	{
		prn_error("Map must contain at least one collectible ('C')!");
		return;
	}
	if (start_position_count != 1)
	{
		prn_error("Map must contain exactly one starting position ('P')!");
		return;
	}

	// If all checks are passed
	ft_printf("Map requirements are valid.\n");
}
