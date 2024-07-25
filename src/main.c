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

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (err("error: invalid arguments"));
	if (check_extension(argv[1]))
		return (err("error: invalid file type"));
	ft_printf(1, "OK\n");
	return (0);
}
