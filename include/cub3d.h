/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:24:23 by amakela           #+#    #+#             */
/*   Updated: 2024/08/30 15:00:18 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include <fcntl.h>

typedef struct s_cub
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	**map;
	int		floor[3];
	int		ceiling[3];
	int		elements_found;
} t_cub;

#endif
