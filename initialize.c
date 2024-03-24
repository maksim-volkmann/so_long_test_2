/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 08:12:50 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/21 09:48:47 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->player = NULL;
	game->background = NULL;
	game->wall = NULL;
	game->door = NULL;
	game->collc = NULL;
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
	game->exit_count = 0;
	game->player_count = 0;
}
