/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_and_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:30:22 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/26 12:45:26 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	tile_draw(t_game *game, mlx_image_t *image, int x, int y)
{
	if (mlx_image_to_window(game->mlx, image, x * TILE, y * TILE) == -1)
		error_and_cleanup(game, mlx_strerror(mlx_errno));
}

void	draw_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			tile_draw(game, game->floor, x, y);
			if (game->map[y][x] == '1')
				tile_draw(game, game->wall, x, y);
			else if (game->map[y][x] == 'C')
				tile_draw(game, game->collc, x, y);
			else if (game->map[y][x] == 'E')
				tile_draw(game, game->door, x, y);
			x++;
		}
		y++;
	}
}

void	redraw_tile(t_game *game, int x, int y)
{
	char		curr_type;
	mlx_image_t	*texture;

	curr_type = game->map[y][x];
	if (curr_type == '0')
		texture = game->floor;
	else if (curr_type == '1')
		texture = game->wall;
	else if (curr_type == 'C')
		texture = game->collc;
	else if (curr_type == 'E')
		texture = game->door;
	else
		texture = game->floor;
	tile_draw(game, game->floor, x, y);
	tile_draw(game, texture, x, y);
}

void	draw_player(t_game *game)
{
	redraw_tile(game, game->p_x, game->p_y);
	tile_draw(game, game->player, game->p_x, game->p_y);
}

void	attempt_move(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->p_x + dx;
	new_y = game->p_y + dy;
	if (new_x < 0 || new_x >= game->line_width || new_y < 0
		|| new_y >= game->line_count || game->map[new_y][new_x] == '1')
		return ;
	if (game->map[new_y][new_x] == 'C')
	{
		game->coll_c++;
		game->map[new_y][new_x] = '0';
	}
	redraw_tile(game, game->p_x, game->p_y);
	game->p_x = new_x;
	game->p_y = new_y;
	draw_player(game);
	game->counter++;
	ft_printf("Move count: %d\n", game->counter);
	if (game->map[new_y][new_x] == 'E' && game->coll_s == game->coll_c)
	{
		mlx_terminate(game->mlx);
		ft_printf("Total moves: %d\n", game->counter);
		exit(0);
	}
}
