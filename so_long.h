#ifndef SO_LONG_H
# define SO_LONG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MLX42/MLX42.h>
#include "libft/include/libft.h"

#include <string.h> // delete later

#define WIDTH 512
#define HEIGHT 512

typedef struct s_game
{
	mlx_t	*mlx;
	mlx_image_t *player;
	mlx_image_t *background;
	mlx_image_t *wall;
	int	x;
	int	y;
	int	counter;
	char	**map;
}	t_game;

#endif
