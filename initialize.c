/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:12:50 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/20 12:02:53 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game)
{
	game->mlx = NULL;
	// game->player = mlx_image_create(game->mlx, "player.xpm");
	// game->background = mlx_image_create(game->mlx, "background.xpm");
	// game->wall = mlx_image_create(game->mlx, "wall.xpm");
	// game->keydata = NULL;
	game->x = 0;
	game->y = 0;
	game->counter = 0;
	game->map = NULL;
	game->map_copy = NULL;
	game->line_count = 0;
	game->line_width = 0;
	game->player_x = 0;
	game->player_y = 0;
	game->init_collc_count = 0;
	game->read_collc_count = 0;
}
