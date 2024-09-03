/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:24:23 by amakela           #+#    #+#             */
/*   Updated: 2024/09/03 20:06:49 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_coor
{
	int	x;
	int	y;
} t_coor;

typedef struct s_map
{
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
	mlx_t			*mlx;
	mlx_image_t		*arrow_png;
	mlx_image_t		*background_png;
	mlx_texture_t	*arrow_tex;
	mlx_texture_t	*background_tex;
}t_minimap;

#endif
