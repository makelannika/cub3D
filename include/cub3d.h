/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:24:23 by amakela           #+#    #+#             */
/*   Updated: 2024/09/04 17:17:48 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h> /*delete*/

typedef struct s_coor
{
	int	x;
	int	y;
} t_coor;

typedef struct s_map
{
	int		width;
	int 	height;
	char	**layout;
	char	orientation;
	t_coor	player;
} t_map;

typedef struct s_cub
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor[3];
	int		ceiling[3];
	int		elements_found;
	t_map	map;
	
} t_cub;

typedef struct s_minimap
{
	int				map_width;
	int				map_height;
	float			index_width;
	float			index_height;
	float			player_x;
	float			player_y;
	char			**map;
	mlx_t			*mlx;
	mlx_image_t		*arrow_png;
	mlx_image_t		*background_png;
	mlx_texture_t	*arrow_tex;
	mlx_texture_t	*background_tex;
}t_minimap;

#endif
