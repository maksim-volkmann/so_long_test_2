/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 13:58:21 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/23 14:14:24 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	line_counter(char *file, t_game *game)
{
	int		fd;
	char	*current_line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	game->line_count = 0;
	current_line = get_next_line(fd);
	while (current_line != NULL)
	{
		game->line_count++;
		free(current_line);
	}
	close(fd);
	return (0);
}

void	array_of_pointer(t_game *game, char *file)
{
	line_counter(file, game);
	if (game->line_count <= 0)
		prn_error("Memory allocation error for map");
	game->map = malloc(sizeof(char *) * (game->line_count + 1));
	if (!game->map)
		prn_error("Memory allocation error for map");
	game->map[game->line_count] = NULL;
}

int	populate_map(t_game *game, char *file)
{
	int		fd;
	char	*line;
	int		i;
	size_t	len;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	i = 0;
	while (((line = get_next_line(fd)) != NULL) && (i < game->line_count))
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		game->map[i] = line;
		i++;
	}
	close(fd);
	return (0);
}
