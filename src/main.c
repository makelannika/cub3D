#include "../include/cub3d.h"

int	check_extension(char *arg)
{
	int     len;

	len = ft_strlen(arg);
	return (ft_strncmp(&arg[len - 4], ".cub", 5));
}

int	err(char *str)
{
	ft_printf(2, "%s\n", str);
	return (1);
}
int	copy_path(char *line, char *id)
{
	id = ft_substr(line, 0, ft_strlen(line) - 1);
	if (!id)
		return (err("Error: malloc failed in substr"));
	return (0);
}

int	copy_color(char *line, int *id)
{
	char **rgb;
	
	while (*line == ' ')
		line++;
	//check the rgb is a good string
	rgb = ft_split(line, ',');
	if (!rgb)
		return (err("Error: malloc failed in split"));
	id[0] = ft_atoi(rgb[0]);
	id[1] = ft_atoi(rgb[1]);
	id[2] = ft_atoi(rgb[2]);
	return (0);
}

int	check_identifier(char *line, t_cub *data)
{
	if (!ft_strncmp("NO ", line, 3))
		return (copy_path(line, data->no));
	if (!ft_strncmp("WE ", line, 3))
		return (copy_path(line, data->we));
	if (!ft_strncmp("EA ", line, 3))
		return (copy_path(line, data->ea));
	if (!ft_strncmp("SO ", line, 3))
		return (copy_path(line, data->so));
	if (!ft_strncmp("F ", line, 2))
		return (copy_color(&line[1], data->floor));
	if (!ft_strncmp("C ", line, 2))
		return (copy_color(&line[1], data->ceiling));
	return (1);
}

int	parse_file(t_cub *data, char *file)
{
	int		fd;
	char	*line;

	ft_printf(1, "%d\n", data->floor[0]);
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
			return (err("Error:"));
		
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub data;

	data = (t_cub){0};
	if (argc != 2 || check_extension(argv[1]))
		return (err("Error: invalid argument"));
	if (parse_file(&data, argv[1]))
		return (1);
	ft_printf(1, "OK\n");
	return (0);
}
