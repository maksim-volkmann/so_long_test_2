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

void prn_error(char *message) {
	ft_printf("%s\n", message);
}

// -----------------------------------------------------------------------------

int32_t main(int ac, char *av[])
{
	t_game game;

	game.map = NULL;
	game.line_count = 0;

	// line_counter(av[1], &game.line_count);
	array_of_pointer(&game, av[1]);

	ft_printf("line_count: %d\n", game.line_count);

	if(ac != 2)
	{
		ft_printf("Error: Invalid number of arguments\n");
		return (EXIT_FAILURE);
	}

	// int fd = open(av[1], O_RDONLY);
	// if (fd == -1) {
	// 	perror("Error opening file");
	// 	return EXIT_FAILURE;
	// }

	// char *line;
	// while ((line = get_next_line(fd)) != NULL) {
	// 	// ft_printf("%s\n", line);
	// 	free(line);
	// }

	// if (close(fd) == -1) {
	// 	perror("Error closing file");
	// 	return EXIT_FAILURE;
	// }

	if (!game.map) // Check if map was successfully populated
	{
		ft_printf("Failed to populate map\n");
		return (EXIT_FAILURE);
	}
	check_map_population(&game);

	if (game.map == NULL || game.map[0] == NULL) {
		ft_printf("Map is not properly allocated or first line is NULL.\n");
	} else {
		// ft_printf("First character of the first line: %c\n", game.map[0][0]);
	}
	ft_printf("Map:\n");
	// ft_printf("First map line: %s\n", game.map[0][1]);
	// ft_printf("11 map line: %s\n", game.map[10]);
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
