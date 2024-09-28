/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:24:23 by amakela           #+#    #+#             */
/*   Updated: 2024/09/27 20:57:24 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h> /*delete*/
# include <math.h>
# include <float.h>

# define PLAYER_X 137
# define PLAYER_Y 137
# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 1000
# define INDEX_WIDTH 25
# define INDEX_HEIGHT 25

typedef struct s_coor
{
	int		x;
	int		y;
	float	pix_x;
	float	pix_y;
} t_coor;

typedef struct s_map
{
	int		height;
	int		width;
	int		offsetx;
	int		offsety;
	double	p_angle;
	char	**grid;
	t_coor	player;
} t_map;

typedef struct s_ray
{
	double	current_angle;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
    double	delta_dist_y;
	float	unit_x;
	float	unit_y;
	int		ray_index_x;
	int		ray_index_y;
    int		step_x;
	int		step_y;
    double	side_dist_x;
	double	side_dist_y;
	double	ray_distance;
	double	wall_hit_x;
	double	wall_hit_y;
	int		hit;
	int		side;
} t_ray;

typedef struct s_cub3d
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	mlx_image_t		*background;
	uint32_t		*wall_to_draw;
	// uint8_t			*wall_to_draw;
	int				start;
	int				end;
	int				wall_height;
	int				floor;
	int				ceiling;
	int				elements_found;
	int				gnl_err;
	int				fd;
	t_map			map;
	t_ray			ray_c;
	mlx_t			*mlx;
} t_cub3d;

// PARSING
int		check_extension(char *arg);
int		parse_file(t_cub3d *data, char *file);
int		parse_map(t_cub3d *data, char *line, char *file);
int		create_grid(t_cub3d *data, char *file);
int		rgba_to_hex(int r, int g, int b, int a);
int		reverse_bytes(int p);
int		copy_color(t_cub3d *data, char *str, char identifier);
int		validate_index(t_cub3d *data, char **grid, int y, int x);
int		validate_line(char *str);

// GAME
int		init_game(t_cub3d *data);

// MOVEMENT
void	rotate_right(t_cub3d *data);
void	rotate_left(t_cub3d *data);
void	reset_minimap(t_cub3d * data);
void	my_keyhook(mlx_key_data_t keydata, void *game_data);

// DRAWING
void	draw_minimap(t_cub3d *data, int y, int x);
void	draw_player(t_cub3d *data);
void	draw_background(t_cub3d *data);
void	draw_pixel(t_cub3d *data, int x, int incr);
void	fov_cast(t_cub3d *data, t_ray *ray_c, float player_angle);

// CLEANING UTILS
int		err(char *str, void *ptr);
int		free_str_array(char **array);
int		free_data(t_cub3d *data);

#endif
