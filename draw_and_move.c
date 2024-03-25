/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_and_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:30:22 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/25 11:32:24 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			mlx_image_to_window(game->mlx, game->floor, x * TILE, y * TILE);
			if (game->map[y][x] == '1')
				mlx_image_to_window(game->mlx, game->wall, x * TILE, y * TILE);
			else if (game->map[y][x] == 'C')
				mlx_image_to_window(game->mlx, game->collc, x * TILE, y * TILE);
			else if (game->map[y][x] == 'E')
				mlx_image_to_window(game->mlx, game->door, x * TILE, y * TILE);
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
	mlx_image_to_window(game->mlx, game->floor, x * TILE, y * TILE);
	mlx_image_to_window(game->mlx, texture, x * TILE, y * TILE);
}

void	draw_player(t_game *game)
{
	int	player_x;
	int	player_y;

	player_x = game->p_x * TILE;
	player_y = game->p_y * TILE;
	redraw_tile(game, game->p_x, game->p_y);
	mlx_image_to_window(game->mlx, game->player, player_x, player_y);
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
		printf("Total moves: %d\n", game->counter);
		exit(0);
	}
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP)
			attempt_move(game, 0, -1);
		else if (keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN)
			attempt_move(game, 0, 1);
		else if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT)
			attempt_move(game, -1, 0);
		else if (keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT)
			attempt_move(game, 1, 0);
	}
}
