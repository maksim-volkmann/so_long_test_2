#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include "libft/include/libft.h"
# include "MLX42/MLX42.h"

# define WIDTH 50
# define HEIGHT 50
# define TILE_SIZE 50


# define PLAYER "images/player.png"
# define WALL "images/wall.png"
# define DOOR "images/door.png"
# define BACKGROUND "images/background.png"
# define COLLECTABLE "images/collectable.png"

# define NUM_ARGS "Invalid number of arguments!"
# define INV_NAME "Incorrect file name!"
# define EMP_FILE "Empty file or error counting lines!"
# define MAP_MEM_ERR "Memory allocation failed for map!"
# define NOT_RECT "Map is not rectangular!"
# define INV_CHAR "Map contains invalid characters!"
# define FRS_ROW "First row is not a wall!"
# define LST_ROW "Last row is not a wall!"
# define VRT_WALL "Vertical walls are missing!"
# define EXT_ERR "Map must contain exactly one exit ('E')!"
# define PLR_ERR "Map must contain exactly one player ('P')!"
# define COL_ERR "Map must contain at least one collectible ('C')!"
# define ORG_MAP_ERR "Memory allocation failed for the map!"
# define CPY_MAP_ERR "Memory allocation failed for the map copy!"
# define FIL_ERR "Map path is blocked!"

# define TRG_CHR "0PEC"
# define FILL_CHR 'F'

typedef struct s_game
{
	mlx_t	*mlx;
	mlx_image_t *player;
	mlx_image_t *background;
	mlx_image_t *wall;
	mlx_image_t *door;
	mlx_image_t *collc;
	int	x;
	int	y;
	int	counter;
	char	**map;
	char	**map_copy;
	int	line_count;
	int	line_width;
	int	player_x;
	int	player_y;
	int	init_collc_count;
	int	read_collc_count;
	int exit_count;
	int player_count;
}	t_game;

// read_map.c
// int	line_counter(char *file, int *line_count);
// int	line_counter(char *file, t_game *game);
int	line_counter(t_game *game, char *file);
void array_of_pointer(t_game *game);
// void array_of_pointer(t_game *game, char *file);
void prn_error(char *message);
int populate_map(t_game *game, char *file);
// void populate_map(t_game *game, char *file);

//validate_map.c
void	check_map_line_lengths(t_game *game);
void	check_map_for_valid_characters(t_game *game);
void	check_map_walls(t_game *game);
void	count_map_characters(t_game *game);
void	check_map_character_count(t_game *game);

//check_map_path.c
// void	copy_map(t_game *game);
// void	fill(t_game *game);
// void	flood_fill(t_game *game, int x, int y, char target, char replacement);
// void	flood_fill(t_game *game, int x, int y, char target, char replacement);
// bool	check_adjacent_for_f(t_game *game, int x, int y);
// void	check_reachability(t_game *game);
// int		check_collectables_and_exit_reachability(t_game *game);
void 	copy_map(t_game *game);
int		is_fill_target(char tile);
void	flood_fill(t_game *game, int x, int y);
void	check_reachability(t_game *game);

//iniinitialize.c
void	init_game(t_game *game);

//clean_up.c
void	free_images(t_game *game);
void	free_map(char ***map);
void	error_and_cleanup(t_game *game, const char *msg);

#endif
