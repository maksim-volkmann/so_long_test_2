/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:12:57 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/25 12:03:11 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// -----------------------------------------------------------------------------

// static void error(void)
// {
// 	puts(mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }






void check_map_population(t_game *game) {
	if (game->map == NULL) {
		ft_printf("Map is not allocated.\n");
		return;
	}

	int i = 0;
	while (game->map[i] != NULL) {
		if (game->map[i][0] == '\0') {
			// Empty line, you might want to check if this is expected
			ft_printf("Warning: Line %d is empty.\n", i + 1);
		} else {
			// This line is populated
			ft_printf("Line %d is populated with: %s\n", i + 1, game->map[i]);
		}
		i++;
	}

	if (i == 0) {
		ft_printf("Map has no lines.\n");
	} else {
		ft_printf("Total lines populated: %d\n", i);
	}
}

void prn_error(char *message)
{
	ft_printf("\033[31m%s\033[0m\n", message);
}

int	validate_map_name(const char *map_name)
{
	const char	*actual_file_name;
	size_t		len;

	actual_file_name = ft_strrchr(map_name, '/');
	if (actual_file_name == NULL)
		actual_file_name = map_name;
	else
		actual_file_name++;
	len = ft_strlen(actual_file_name);
	if (len < 5)
		return (0);
	if (actual_file_name[len - 4] == '.'
		&& actual_file_name[len - 3] == 'b'
		&& actual_file_name[len - 2] == 'e'
		&& actual_file_name[len - 1] == 'r')
		return (1);
	return (0);
}


int32_t main(int ac, char *av[])
{
	// printf("aaaaaaa *av[1]: %c\n", *av[1]);
	t_game game;

	init_game(&game);
	if(ac != 2)
		error_and_cleanup(&game, NUM_ARGS);
	if (!validate_map_name(av[1]))
		error_and_cleanup(&game, INV_NAME);

	line_counter(&game, av[1]);
	array_of_pointer(&game);
	populate_map(&game, av[1]);
	// need to move this to new function or add to existing one.
	game.line_width = ft_strlen(game.map[0]);
	printf("line_width: %d\n", game.line_width);


	check_map_line_lengths(&game);
	check_map_for_valid_characters(&game);
	check_map_walls(&game);
	count_map_characters(&game);
	check_map_character_count(&game);



	copy_map(&game);
	if (game.map_copy == NULL || game.map_copy[0] == NULL) {
		printf("Map copy is NULL.\n");
	}


	// set player to 0, because we will flood fill from player position
	// game.map_copy[game.player_x][game.player_y] = '0';


	// flood_fill(&game, game.player_x, game.player_y, '0', 'F');
	flood_fill(&game, game.p_x, game.p_y);
	// if (game->map_copy[x][y] != target) {
	// 	printf("returnina cia\n");
	// 	return;
	// }

	// fill(&game);
		// int x = 0;
		// int y;
		// while (game.map_copy[x] != NULL) {
		// 	y = 0;
		// 	while (game.map_copy[x][y] != '\0') {
		// 		printf("%c", game.map_copy[x][y]);
		// 		y++;
		// 	}
		// 	printf("\n"); // Print a newline at the end of each row
		// 	x++;
		// }



	// if (game.map_copy == NULL) {
	// 	ft_printf("Map copy is NULL.\n");
	// }

;

	// if (game.map_copy == NULL) {
	// 	ft_printf("Map copy is NULL.\n");
	// }


	check_reachability(&game);

	// game.line_width = ft_strlen(game.map[0]);


	if (!(game.mlx = mlx_init(TILE * game.line_width, TILE * game.line_count, "Redbull Bull", false)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	init_textures(&game);

	draw_map(&game);
	draw_player(&game);
	// system("leaks so_long");
	mlx_key_hook(game.mlx, &ft_key_hook, &game);
	mlx_loop(game.mlx);
	// mlx_put_string(game.mlx, "GAME OVER, YOU WIN", 0, 0);
		// system("leaks so_long");
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
