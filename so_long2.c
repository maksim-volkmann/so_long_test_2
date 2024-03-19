/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:12:57 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/19 13:25:47 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static mlx_image_t* image;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

// void ft_hook(void* param)
// {
// 	mlx_t* mlx = param;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_UP))
// 		image->instances[0].y -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
// 		image->instances[0].y += 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		image->instances[0].x -= 5;
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		image->instances[0].x += 5;
// }

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game *game = param;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_UP)
		image->instances[0].y -= 5;
	if (keydata.key == MLX_KEY_DOWN)
		image->instances[0].y += 5;
	if (keydata.key == MLX_KEY_LEFT)
		image->instances[0].x -= 5;
	if (keydata.key == MLX_KEY_RIGHT)
		image->instances[0].x += 5;

}

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

// -----------------------------------------------------------------------------




static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}





int32_t main(int ac, char *av[])
{
	t_game game;


	// line_counter(av[1], &game.line_count);


	if(ac != 2)
	{
		ft_printf("Error: Invalid number of arguments\n");
		return (EXIT_FAILURE);
	}
	init_game(&game);

	array_of_pointer(&game, av[1]);
	printf("Line count 1: %d\n", game.line_count); // After setting line_count
	populate_map(&game, av[1]);

	ft_printf("map %d\n", ft_strlen(game.map[0]));
	ft_printf("line_count: %d\n", game.line_count);
	ft_printf("map[0][0]: %c\n", game.map[0][ft_strlen(game.map[0]) - 1]);

	check_map_line_lengths(&game);
	printf("SITAS | WIDTH: %d, HEIGHT: %d\n", game.line_width, game.line_count);
	printf("player cordinates 001: x: %d, y: %d\n", game.player_x, game.player_y);
	check_map_for_valid_characters(&game);
	printf("SITAS2 | WIDTH: %d, HEIGHT: %d\n", game.line_width, game.line_count);
	check_map_walls(&game);
	printf("SITAS3 | WIDTH: %d, HEIGHT: %d\n", game.line_width, game.line_count);
	check_map_characters_count(&game);
	printf("SITAS4 | WIDTH: %d, HEIGHT: %d\n", game.line_width, game.line_count);
	printf("player cordinates 002: x: %d, y: %d\n", game.player_x, game.player_y);

	printf("map[0][0]: %s\n", game.map[0]);

	copy_map(&game);
	if (game.map_copy == NULL || game.map_copy[0] == NULL) {
		printf("Map copy is NULL.\n");
		// return; // Or handle the error as appropriate
	}

	ft_printf("player.x: %d, player.y: %d\n", game.player_x, game.player_y);
	// ft_printf("map_copy[0][0]: \033[32m%c\033[0m\n\n", game.map_copy[0][0]);

	ft_printf("Player character: %c\n", game.map_copy[game.player_x][game.player_y]);
	game.map_copy[game.player_x][game.player_y] = '0';
	ft_printf("Player character: %c\n", game.map_copy[game.player_x][game.player_y]);

	flood_fill(&game, game.player_x, game.player_y, '0', 'F');
	printf("SITAS | WIDTH: %d, HEIGHT: %d\n", game.line_width, game.line_count);
	ft_printf("\n");
	if (game.map_copy == NULL) {
		ft_printf("Map copy is NULL.\n");
	}

	// for (int i = 0; game.map[i] != NULL; i++) {
	// 	printf("\033[32m%s\033[0m\n", game.map[i]);
	// }
	// printf("\n");
	// for (int i = 0; game.map_copy[i] != NULL; i++) {
	// 	printf("\033[32m%s\033[0m\n", game.map_copy[i]);
	// }

	printf("copy_map[0][0]: %c\n", game.map_copy[0][0]);

	// if (!game.map || !game.map[0]) // Check if map and map[0] were successfully populated
	// {
	// 	ft_printf("Failed to populate map or map[0]\n");
	// 	return (EXIT_FAILURE);
	// }

	// check_reachability(&game);
	// ft_printf("Map is reachable\n");

	if (game.map_copy == NULL) {
		ft_printf("Map copy is NULL.\n");
	}

	// for (int i = 0; game.map_copy[i] != NULL; i++) {
	// 	ft_printf("%s\n", game.map_copy[i]);
	// }
	if (check_collectables_and_exit_reachability(&game))
	{
		ft_printf("All collectables and the exit are reachable.\n");
	}
	else
	{
		ft_printf("Some collectables or the exit are not reachable.\n");
	}
	// printf("\033[34mChecking reachability...\033[0m\n");
	// printf("WIDTH: %d, HEIGHT: %d\n", game.line_width, game.line_count);

	game.line_width = ft_strlen(game.map[0]);
		printf("SITAS | WIDTH: %d, HEIGHT: %d\n", game.line_width, game.line_count);
	// Gotta error check this stuff
		// if (!(game.mlx = mlx_init(WIDTH * game.line_width, HEIGHT * game.line_count, "MLX42", true)))
	if (!(game.mlx = mlx_init(WIDTH * game.line_width, HEIGHT * game.line_count, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(game.mlx, 50, 50)))
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game.mlx, image, 0, 0) == -1)
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}


	// DISPLAY IMAGE!!!! [START]

	// Try to load the file
	mlx_texture_t* texture = mlx_load_png("player.png");
	if (!texture)
		error();

	// Convert texture to a displayable image
	mlx_image_t* img = mlx_texture_to_image(game.mlx, texture);
	if (!img)
		error();

	// Display the image
	if (mlx_image_to_window(game.mlx, img, 0, 0) < 0)
		error();

	// DISPLAY IMAGE!!!! [END]


	mlx_loop_hook(game.mlx, ft_randomize, game.mlx);
	// mlx_loop_hook(game.mlx, ft_hook, game.mlx);
	// mlx_key_hook(game.mlx, &ft_key_hook, &game);
	mlx_key_hook(game.mlx, &ft_key_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
