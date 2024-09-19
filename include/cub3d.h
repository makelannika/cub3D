/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:24:23 by amakela           #+#    #+#             */
/*   Updated: 2024/09/19 13:28:39 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h> /*delete*/
# include <errno.h> /*ok?*/
# include <math.h>
#include <float.h>

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

typedef struct s_minimap
{
	int				map_height;
	int				map_width;
	int				offsetx;
	int				offsety;
	double			p_angle;
	char			**map;
	char			orientation;
	mlx_t			*mlx;
	mlx_image_t		*arrow_png;
	mlx_image_t		*background_png;
	mlx_texture_t	*arrow_tex;
	mlx_texture_t	*background_tex;
	t_coor			player;
} t_minimap;

// typedef struct s_cub3d
// {
// 	char		*no_txtr;
// 	char		*so_txtr;
// 	char		*we_txtr;
// 	char		*ea_txtr;
// 	int			floor[3];
// 	int			ceiling[3];
// 	int			elements_found;
// 	t_minimap	map;
// 	mlx_image_t	*no;
// 	mlx_image_t	*so;
// 	mlx_image_t	*we;
// 	mlx_image_t	*ea;
// } t_cub3d;

typedef struct s_cub3d
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			floor[3];
	int			ceiling[3];
	int			elements_found;
	t_minimap	map;
	
} t_cub3d;

// PARSING
int		check_extension(char *arg);
int		parse_file(t_cub3d *data, char *file);
int		parse_map(t_cub3d *data, char *line, int fd, char *file);
int		get_map_height(t_cub3d *data, char *line, int fd);
void	get_map_width(t_cub3d *data);
int		count_commas(char *str);

// GAME
int init_game(t_cub3d *data);

// MOVEMENT
void	move_left(t_minimap *data);
void	move_right(t_minimap *data);
void	move_down(t_minimap *data);
void	move_up(t_minimap *data);
void	my_keyhook(mlx_key_data_t keydata, void *game_data);

void	rotate_left(t_minimap *data);
void	rotate_right(t_minimap *data);

// DRAWING
void	draw_player(t_minimap *data, float angle);
int		draw_minimap(t_minimap *data, int y, int x);

void	fov_cast(t_minimap *data, float player_angle);

// CLEANING UTILS
int		err(char *str, void *ptr);
int		free_str_array(char **array);
int		free_data(t_cub3d *data);

#endif
