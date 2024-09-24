/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:24:23 by amakela           #+#    #+#             */
/*   Updated: 2024/09/24 16:53:44 by amakela          ###   ########.fr       */
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
	mlx_texture_t	*no_txtr;
	mlx_texture_t	*so_txtr;
	mlx_texture_t	*we_txtr;
	mlx_texture_t	*ea_txtr;
	mlx_texture_t	*minimap_txtr;
	mlx_image_t		*no;
	mlx_image_t		*so;
	mlx_image_t		*we;
	mlx_image_t		*ea;
	mlx_image_t		*minimap;
	int				floor[3];
	int				ceiling[3];
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
int		get_map_height(t_cub3d *data, char *line);
void	get_map_width(t_cub3d *data);
int		count_commas(char *str);

// GAME
int		init_game(t_cub3d *data);

// MOVEMENT
void	move_left(t_cub3d *data);
void	move_right(t_cub3d *data);
void	move_down(t_cub3d *data);
void	move_up(t_cub3d *data);
void	my_keyhook(mlx_key_data_t keydata, void *game_data);

void	rotate_left(t_cub3d *data);
void	rotate_right(t_cub3d *data);

// DRAWING
void	draw_player(t_cub3d *data, float angle);
int		draw_minimap(t_cub3d *data, int y, int x);
// void	fov_cast(t_cub3d *data, float player_angle);
void	fov_cast(t_cub3d *data, t_ray *ray_c, float player_angle);

// CLEANING UTILS
int		err(char *str, void *ptr);
int		free_str_array(char **array);
int		free_data(t_cub3d *data);

#endif
