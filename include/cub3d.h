/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:24:23 by amakela           #+#    #+#             */
/*   Updated: 2024/10/29 18:59:15 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <math.h>

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000

typedef struct s_draw
{
	uint32_t	*wall_to_draw;
	double		increment;
	double		txtr_y;
	int			txtr_x;
	int			start;
	int			end;
	int			wall_height;
}	t_draw;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	distance;
	double	wall_x;
	int		screen_x;
	int		side;
	int		hit;
	int		step_x;
	int		step_y;
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
}	t_ray;

typedef struct s_map
{
	double	angle;
	char	**grid;
	int		height;
	int		y;
	int		x;
}	t_map;

typedef struct s_cub3d
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_image_t		*background;
	int				floor;
	int				ceiling;
	t_gnl			gnl;
	t_map			map;
	t_ray			ray;
	t_draw			draw;
	mlx_t			*mlx;
}	t_cub3d;

/*******PARSING********/
int		check_extension(char *arg);
int		parse_file(t_cub3d *data, t_gnl *gnl, char *file);
int		parse_map(t_cub3d *data, t_gnl *gnl, char *line, char *file);
int		copy_color(t_cub3d *data, char *str, char identifier);
int		validate_line(char *str);
int		get_arr_len(char **array);
void	set_orientation(t_cub3d *data, char orientation);

/*******GAME***********/
int		game(t_cub3d *data);

/*******MOVEMENT*******/
void	rotate_right(t_cub3d *data, t_ray *ray);
void	rotate_left(t_cub3d *data, t_ray *ray);
void	my_keyhook(void *game_data);

/*******RENDERING******/
void	init_player(t_cub3d *data);
void	init_casting(t_map *map, t_ray *ray);
void	fov_cast(t_cub3d *data, t_ray *ray);
void	draw_background(t_cub3d *data);
void	draw_ray(t_cub3d *data, t_draw *draw, int screen_x);

/*******CLEANING*******/
int		err(char *str, char *ptr);
int		free_str_array(char **array);
int		free_data(t_cub3d *data);

#endif
