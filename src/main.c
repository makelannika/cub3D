#include "../include/cub3d.h"

int	parse_file(t_cub *data, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err("Error: open failed :("));
	line = get_next_line(fd); //check line
	while (line && ft_strncmp(line, " ", 1) && ft_strncmp(line, "1", 1))
	{
		if (ft_strncmp(line, "\n", 1))
		{
			line = get_next_line(fd);
			continue ;
		}
		if(check_identifier(line, data))
			return (err("Error"));
		free(line);
		line = get_next_line(fd);
	}
	if (init_map(fd, data, line))
		return (err("Error"));
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub data;

	data = (t_cub){0};
	if (argc != 2 || check_extension(argv[1]))
		return (err("Error: invalid argument"));
	if (parse_file(&data, argv[1]))
		return (1); //checks what exist and free
	for (int i = 0; data.map[i]; i++)
		ft_printf(2, "%s\n", data.map[i]);
	if (check_map_char(&data))
		return (err("\nError map is shit")); // clean
	return (0);
}

