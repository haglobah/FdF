/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:57 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/06/19 12:38:43 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# include <fcntl.h>
# include <math.h>

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

# define WIDTH 1000
# define HEIGHT 660
# define SCALE 10
# define WHITE 0xFFFFFFFF

typedef struct s_iplist
{
	int	*ip;
	int	width;
	struct s_iplist	*next;
}	t_lip;

t_lip	*ft_lipelem(int *iarr, int width);
void	ft_lipclear(t_lip **lip);
//t_lip	*ft_lipcpy(t_lip *lip);
void	ft_lipapp(t_lip **lip, t_lip *lipel);
int	ft_liplen(t_lip *lip);
int	ft_printlip(t_lip *lip);

typedef struct s_2dpoint
{
	int	x;
	int	y;
}	t_2d;

typedef struct s_3dpoint
{
	int	x;
	int	y;
	int	z;
}	t_3d;

typedef struct s_3dmapofallpoints
{
	t_3d	**arr;
	int	y;
	int	z;
}	t_map;

typedef struct s_bresenham
{
	t_2d	d;
	t_2d	s;
}	t_bres;

/* typedef struct s_grid */
/* { */
/* 	t_lip	*coors; */
/* }	t_grid; */

#endif
