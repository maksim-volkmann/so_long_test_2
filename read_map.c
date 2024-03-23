#include "so_long.h"

int	line_counter(char *file, int *line_count)
{
	int		fd;
	char	*current_line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	*line_count = 0;
	while ((current_line = get_next_line(fd)) != NULL)
	{
		(*line_count)++;
		free(current_line);
	}
	close(fd);
	ft_printf("line_count from line_count function: %d\n", *line_count);
	return (0);
}

// Allocate memory for the map using the line_count from the game struct
void	array_of_pointer(t_game *game, char *file)
{
	line_counter(file, &game->line_count);
	if (game->line_count <= 0) {
		prn_error("Error counting lines or file is empty");
		// return NULL; // Here, return NULL directly after logging the error
	}
	game->map = malloc(sizeof(char *) * (game->line_count + 1));
	if (!game->map) {
		prn_error("Memory allocation error for map");
		// return NULL; // Similarly, return NULL directly after logging the error
	}
	game->map[game->line_count] = NULL; // Set the last element to NULL
	// return game->map; // Return the allocated map
}

int populate_map(t_game *game, char *file)
{
	int fd;
	char *line;
	int i;
	size_t len;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1); // Handle error

	i = 0;
	while (((line = get_next_line(fd)) != NULL) && (i < game->line_count))
	{
		// Determine the length of the line excluding the newline character
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0'; // Replace newline character with null terminator

		game->map[i] = line; // Assign the line directly since get_next_line allocates memory
		i++;
	}
	close(fd);
	return (0); // Success
}
