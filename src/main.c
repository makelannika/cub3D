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

int	free_str_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i])
			free(array[i++]);
	}
	free(array);
	return (1);
}

int	count_commas(char *str)
{
	int	commas;

	commas = 0;
	while (*str != '\0') {
		if (*str == ',')
			commas++;
		str++;
	}
	return (commas);
}

int	validate_color(char *str)
{
	int	i;
	int	color;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != '\n')
			return (err("Error: invalid element"));
		i++;
	}
	color = ft_atoi(str);
	if (color < 0 || color > 255)
		return (err("Error: invalid element"));
	return (color);
}

int	copy_color(char *str, int *id)
{
	char **rgb;
	
	if (count_commas(str) != 2)
		return (err("Error: invalid element"));
	rgb = ft_split(str, ',');
	if (!rgb)
		return (err("Error: malloc failed in split"));
	id[0] = validate_color(rgb[0]);
	id[1] = validate_color(rgb[1]);
	id[2] = validate_color(rgb[2]);
	if (id[0] == -1 || id[1] == -1 || id[2] == -1)
		return (free_str_array(rgb));
	free_str_array(rgb);
	return (0);
}

int	check_identifier(char **element, t_cub *data)
{
	char	*copy;
	
	if (!ft_strncmp("F", element[0], 2))
		return (copy_color(element[1], data->floor));
	else if (!ft_strncmp("C", element[0], 2))
		return (copy_color(element[1], data->ceiling));
	copy = ft_strdup(element[1]);
	if (!copy)
		return (err("Error: malloc failed"));
	if (!ft_strncmp("NO", element[0], 3))
		data->no = copy;
	else if (!ft_strncmp("WE", element[0], 3))
		data->we = copy;
	else if (!ft_strncmp("EA", element[0], 3))
		data->ea = copy;
	else if (!ft_strncmp("SO", element[0], 3))
		data->so = copy;
	else
	{
		free(copy);
		return (1);
	}
	return (0);
}

int	parse_element(t_cub *data, char *line)
{
	char	**element;
	int		len;

	element = ft_split(line, ' ');
	if (!element)
		return (err("Error: malloc failed"));
	if (element[2])
	{
		free_str_array(element);
		return (err("Error: invalid element"));
	}
	len = ft_strlen(element[1]);
	element[1][len - 1] = '\0';
	if (check_identifier(element, data))
		return (free_str_array(element));
	free_str_array(element);
	data->elements_found++;
	return (0);
}

int	parse_map(t_cub *data, char *line)
{
	if (data->elements_found != 6)
	{
		free(line);
		return (err("Error: invalid .cub file content"));
	}
	free(line);
	return (0);
}

int	parse_file(t_cub *data, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err("Error: open failed :("));
	line = get_next_line(fd); // add malloc check for gnl
	while (line)
	{
		if (ft_strchr("NSWEFC", *line)) {
			if (parse_element(data, line))
			{
				free(line);
				return (1);
			}
		}
		else if (ft_strchr(" 1", *line)) {
			return (parse_map(data, line));
		}
		else if (*line != '\n')
		{
			free(line);
			return (err("Error: forbidden content in .cub file"));
		}
		free(line);
		line = get_next_line(fd); // malloc check
	}
	return (0);
}

int	free_data(t_cub *data)
{
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	return (1);
}

int	main(int argc, char **argv)
{
	t_cub data;

	data = (t_cub){0};
	if (argc != 2 || check_extension(argv[1]))
		return (err("Error: invalid argument"));
	if (parse_file(&data, argv[1]))
		return (free_data(&data));
	ft_printf(1, "NO: %s\n", data.no);
	ft_printf(1, "SO: %s\n", data.so);
	ft_printf(1, "WE: %s\n", data.we);
	ft_printf(1, "EA: %s\n", data.ea);
	ft_printf(1, "floor: %d,%d,%d\n", data.floor[0], data.floor[1], data.floor[2]);
	ft_printf(1, "ceiling: %d,%d,%d\n", data.ceiling[0], data.ceiling[1], data.ceiling[2]);
	ft_printf(1, "OK\n");
	free_data(&data);
	return (0);
}
