// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

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

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
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

int32_t main(int ac, char *av[])
{
	t_game game;

	game.map = NULL;
	game.line_count = 0;

	// line_counter(av[1], &game.line_count);


	if(ac != 2)
	{
		ft_printf("Error: Invalid number of arguments\n");
		return (EXIT_FAILURE);
	}


	array_of_pointer(&game, av[1]);
	printf("Line count 1: %d\n", game.line_count); // After setting line_count
	populate_map(&game, av[1]);

	ft_printf("map %d\n", ft_strlen(game.map[0]));
	ft_printf("line_count: %d\n", game.line_count);
	ft_printf("map[0][0]: %c\n", game.map[0][ft_strlen(game.map[0]) - 1]);

	check_map_line_lengths(&game);

	check_map_for_valid_characters(&game);
	check_map_walls(&game);
	check_map_characters_count(&game);
	printf("player cordinates: x: %d, y: %d\n", game.player_x, game.player_y);

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

	ft_printf("\n");
	if (game.map_copy == NULL) {
		ft_printf("Map copy is NULL.\n");
	}

	for (int i = 0; game.map[i] != NULL; i++) {
		printf("\033[32m%s\033[0m\n", game.map[i]);
	}
	printf("\n");
	for (int i = 0; game.map_copy[i] != NULL; i++) {
		printf("\033[32m%s\033[0m\n", game.map_copy[i]);
	}

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

	for (int i = 0; game.map_copy[i] != NULL; i++) {
		ft_printf("%s\n", game.map_copy[i]);
	}

	// printf("\033[34mChecking reachability...\033[0m\n");

	// Gotta error check this stuff
	if (!(game.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(game.mlx, 128, 128)))
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

	mlx_loop_hook(game.mlx, ft_randomize, game.mlx);
	mlx_loop_hook(game.mlx, ft_hook, game.mlx);

	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
