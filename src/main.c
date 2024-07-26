#include "../include/cub3d.h"

int	check_extension(char *arg)
{
	int     len;

	len = ft_strlen(arg);
	return (ft_strncmp(&arg[len - 4], ".cub", 5));
}

int	copy_path(char *line, char *id)
{
	id = ft_substr(line, 0, ft_strlen(line) - 1);
	if (!id)
		return (err("malloc failed in substr"));
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
		return (err("malloc failed in split"));
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
	return (0);
}

int increase_array_capacity(t_cub *data, int *capacity)
{
	char 	**new_array;
	int		new_capacity;
	int		i;

	i = 0;
	new_capacity = *capacity * 2;
	new_array = malloc(sizeof(char *) * new_capacity);
	if (!new_array)
		return (1);
	while (data->map[i])
	{
		new_array[i] = data->map[i];
		i++;
	}
	free (data->map);
	data->map = new_array;
	*capacity = new_capacity;
	return (0);
}

int	init_map(int fd, t_cub *data, char *line)
{
	int		capacity;
	int		i;

	i = 0;
	capacity = 2;
	data->map = malloc(sizeof(char *) * capacity);
	while (line)
	{
		data->map[i] = strdup_no_newline(line);
		if (!data->map[i])
			return (1); //needs free funciton that checks array index and free in cleanup;
		i++;
		data->map[i] = NULL;
		if (i == capacity - 1)
		{
			if (increase_array_capacity(data, &capacity))
				return (1); //needs free funciton that checks array index and free in cleanup;
		}
		free (line);
		line = get_next_line(fd); // check line
	}
	return (0);
}

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

int	check_map(t_cub *data)
{
	int	i;
	int j;
	int flag;

	i = 0;
	flag = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ' || data->map[i][j] == '1' || data->map[i][j] == '0')
				;
			else if (!flag && (data->map[i][j] == 'N'|| data->map[i][j] == 'W'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'S'))
				flag = 1;
			else 
				return (1);
			j++;
		}
		i++;
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
		return (1); //checks what exist and free
	for (int i = 0; data.map[i]; i++)
		ft_printf(2, "%s\n", data.map[i]);
	if (check_map(&data))
		return (err("\nError map is shit")); // clean
	return (0);
}

