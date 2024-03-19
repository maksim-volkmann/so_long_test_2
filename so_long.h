#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libft/include/libft.h"
#include "MLX42/MLX42.h" // Correct include statement for MLX42 library

// #include <string.h> // delete later

# define WIDTH 50
# define HEIGHT 50

# define PLAYER "images/player.png"
# define WALL "images/wall.png"
# define GRASS "images/grass.png"

typedef struct s_game
{
	mlx_t	*mlx;
	mlx_image_t *player;
	mlx_image_t *background;
	mlx_image_t *wall;
	// mlx_key_data_t	*keydata;
	int	x;
	int	y;
	int	counter;
	char	**map;
	char	**map_copy;
	int	line_count;
	int	line_width;
	int	player_x;
	int	player_y;
}	t_game;

int	line_counter(char *file, int *line_count);
char **array_of_pointer(t_game *game, char *file);
void prn_error(char *message);
int populate_map(t_game *game, char *file);

//validate_map.c
void	check_map_line_lengths(t_game *game);
void	check_map_for_valid_characters(t_game *game);
void	check_map_walls(t_game *game);
void	check_map_characters_count(t_game *game);

//check_map_path.c
void	copy_map(t_game *game);
void	flood_fill(t_game *game, int x, int y, char target, char replacement);
// bool	check_adjacent_for_f(t_game *game, int x, int y);
// void	check_reachability(t_game *game);
int		check_collectables_and_exit_reachability(t_game *game);

//iniinitialize.c
void	init_game(t_game *game);

#endif
