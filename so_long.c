/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:12:57 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/25 16:21:17 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	init_game(t_game *game)
{
	int	game_width;
	int	game_height;

	game_width = TILE * game->line_width;
	game_height = TILE * game->line_count;
	game->mlx = mlx_init(game_width, game_height, "Redbull Bull", false);
	if (!(game->mlx))
		error_and_cleanup(game, mlx_strerror(mlx_errno));
	init_textures(game);
}

int32_t	main(int ac, char *av[])
{
	t_game	game;

	init_variables(&game);
	if (ac != 2)
		error_and_cleanup(&game, NUM_ARGS);
	if (!validate_map_name(av[1]))
		error_and_cleanup(&game, INV_NAME);
	line_counter(&game, av[1]);
	array_of_pointer(&game);
	populate_map(&game, av[1]);
	check_map_line_lengths(&game);
	copy_map(&game);
	flood_fill(&game, game.p_x, game.p_y);
	check_reachability(&game);
	init_game(&game);
	draw_map(&game);
	draw_player(&game);
	mlx_key_hook(game.mlx, &ft_key_hook, &game);
	mlx_loop(game.mlx);
	error_and_cleanup(&game, NULL);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}

// int main(int argc, char *argv[])
// {
// 	int32_t result = the_real_main(argc, argv);
// 	system("leaks so_long");
// 	return result;
// }
