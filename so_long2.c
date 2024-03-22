/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:12:57 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/21 12:44:46 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// -----------------------------------------------------------------------------

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

bool load_texture(mlx_t *mlx, const char *path, mlx_image_t **texture) {
    mlx_texture_t* temp_texture;

	temp_texture = mlx_load_png(path);
    if (!temp_texture) {
        return false; // Indicate failure to load texture
    }
    *texture = mlx_texture_to_image(mlx, temp_texture);
    if (!*texture) {
        return false; // Indicate failure to convert texture to image
	mlx_delete_texture(temp_texture);
    }
    return true; // Texture loaded and converted successfully
}

void init_textures(t_game *game) {
    if (!load_texture(game->mlx, WALL, &game->wall) ||
        !load_texture(game->mlx, BACKGROUND, &game->background) ||
        !load_texture(game->mlx, DOOR, &game->door) ||
        !load_texture(game->mlx, COLLECTABLE, &game->collc) ||
        !load_texture(game->mlx, PLAYER, &game->player)) {
        error(); // Call your error handling function
    }
}

void draw_map(t_game *game) {
    int y = 0;
    while (game->map[y] != NULL) {
        int x = 0;
        while (game->map[y][x] != '\0') {
            // Always draw floor/background first for every tile
            mlx_image_to_window(game->mlx, game->background, x * TILE_SIZE, y * TILE_SIZE);

            if (game->map[y][x] == '1') { // Wall
                mlx_image_to_window(game->mlx, game->wall, x * TILE_SIZE, y * TILE_SIZE);
            }
            else if (game->map[y][x] == 'C') { // Collectible
                // Draw floor then collectible to ensure collectibles have a background
                mlx_image_to_window(game->mlx, game->collc, x * TILE_SIZE, y * TILE_SIZE);
            }
            else if (game->map[y][x] == 'E') { // Exit
                // Draw floor then exit to ensure exits have a background
                mlx_image_to_window(game->mlx, game->door, x * TILE_SIZE, y * TILE_SIZE);
            }
            // The player is not drawn here
            x++;
        }
        y++;
    }
}

void draw_player(t_game *game) {
    // Ensure the background/floor is drawn under the player
    mlx_image_to_window(game->mlx, game->background, game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
    // Draw the player on top of the floor/background
    mlx_image_to_window(game->mlx, game->player, game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
}

void redraw_tile(t_game *game, int x, int y, char tileType) {
    // Depending on your game design, this might involve selecting the correct image based on tileType
    // and calling mlx_put_image_to_window or similar function.
    mlx_image_t *texture;
    if (tileType == '0') {
        texture = game->background; // For empty space
    } else if (tileType == 'P') {
        texture = game->player; // For player
    } else {
        texture = game->background; // Default to background
    }
    // Note: This is a simplified example. Your game might have more tile types and corresponding textures.
    mlx_image_to_window(game->mlx, texture, x * TILE_SIZE, y * TILE_SIZE);
}


void attempt_move(t_game *game, int dx, int dy) {
    int new_x = game->player_x + dx;
    int new_y = game->player_y + dy;

    if (new_x < 0 || new_y < 0 || new_x >= game->line_width || new_y >= game->line_count || game->map[new_y][new_x] == '1') {
        return; // Move is invalid or hits a wall, so we don't proceed.
    }

    // Handle collectible pickup
    if (game->map[new_y][new_x] == 'C') {
        game->map[new_y][new_x] = '0'; // Collectible is picked up
        game->read_collc_count++;
        redraw_tile(game, new_x, new_y, '0'); // Redraw the tile to reflect the pickup
    }

    // Check for exit condition before moving
    if (game->map[new_y][new_x] == 'E' && game->init_collc_count != game->read_collc_count) {
        return; // Attempt to move to exit without collecting all, do not proceed.
    }

    // Redraw player's current position as empty before moving
    redraw_tile(game, game->player_x, game->player_y, '0');

    game->player_x = new_x;
    game->player_y = new_y;

    // Now move and redraw player in the new position
    redraw_tile(game, new_x, new_y, 'P');

    if (game->map[new_y][new_x] == 'E') {
        // Conditions to exit the game successfully, collectibles are all picked up
        mlx_terminate(game->mlx);
        printf("Total moves: %d\n", game->counter); // Display total moves before exiting
        exit(0);
    }

    game->counter++; // Count the successful move
    printf("Move %d\n", game->counter);
}









void ft_key_hook(mlx_key_data_t keydata, void *param) {
    t_game *game = param; // Cast param back to t_game*

		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
    if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
        if (keydata.key == MLX_KEY_W) // Move up
		{
	    	attempt_move(game, 0, -1);
			printf("collc_count: %d\n", game->init_collc_count);
		}
        else if (keydata.key == MLX_KEY_S) // Move down
            attempt_move(game, 0, 1);
        else if (keydata.key == MLX_KEY_A) // Move left
            attempt_move(game, -1, 0);
        else if (keydata.key == MLX_KEY_D) // Move right
            attempt_move(game, 1, 0);
    }

	// ft_printf("read_collc_count: %d\n", game->read_collc_count);
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

	// DISPLAY IMAGE!!!! [START]


	// -----------------------------------------------------------------------------

	// wall
	// mlx_texture_t* wall_text = mlx_load_png(WALL);
	// if (!wall_text)
	// 	error();
	// game.wall = mlx_texture_to_image(game.mlx, wall_text);
	// if (!game.wall)
	// 	error();

	// // grass
	// mlx_texture_t* background_txt = mlx_load_png(BACKGROUND);
	// if (!background_txt)
	// 	error();
	// game.background = mlx_texture_to_image(game.mlx, background_txt);
	// if (!game.background)
	// 	error();

	// // door
	// mlx_texture_t* door_txt = mlx_load_png(DOOR);
	// if (!door_txt)
	// 	error();
	// game.door = mlx_texture_to_image(game.mlx, door_txt);
	// if (!game.door)
	// 	error();

	// // collectable
	// mlx_texture_t* collc_txt = mlx_load_png(COLLECTABLE);
	// if (!collc_txt)
	// 	error();
	// game.collc = mlx_texture_to_image(game.mlx, collc_txt);
	// if (!game.collc)
	// 	error();

	// // player
	// mlx_texture_t* player_txt = mlx_load_png(PLAYER);
	// if (!player_txt)
	// 	error();
	// game.player = mlx_texture_to_image(game.mlx, player_txt);
	// if (!game.player)
	// 	error();

	init_textures(&game);

	printf("player.x: %d, player.y: %d\n", game.player_x, game.player_y);
	// Display the image

	// mlx_image_to_window(game.mlx, game.player, WIDTH * game.player_x, HEIGHT * game.player_y);
// Example usage within the game loop or main logic
	draw_map(&game);
	draw_player(&game);


	// DISPLAY IMAGE!!!! [END]


	// mlx_loop_hook(game.mlx, ft_hook, game.mlx);
	// mlx_key_hook(game.mlx, &ft_key_hook, &game);
	mlx_key_hook(game.mlx, &ft_key_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
	system("leaks so_long");
}
