/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:57 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/20 12:35:17 by bhagenlo         ###   ########.fr       */
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
# define SCALE 100
# define WHITE 0xFFFFFFFF

typedef struct s_rgb
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}	t_rgb;

typedef struct s_3dmapofallpoints
{
	int	**arr;
	int	width;
	int	len;
	int	range[2];
}	t_map;

typedef struct s_2dpoint
{
	int			x;
	int			y;
}	t_2d;

typedef struct s_3dpoint
{
	int			x;
	int			y;
	int			z;
	uint32_t	clr;
}	t_3d;

typedef struct s_bresenham
{
	t_2d	d;
	t_2d	s;
	int		err;
	int		e2;
}	t_bres;

typedef struct s_parse_file
{
	char	*fname;
	int		fd;
	char	*line;
	char	**zs;
}	t_parse;

typedef struct s_iplist
{
	int				*ip;
	int				width;
	struct s_iplist	*next;
}	t_lip;

//parse
void		free_parse(t_parse *p);

t_lip		*ft_lipelem(int *iarr, int width);
void		ft_lipclear(t_lip **lip);
//t_lip		*ft_lipcpy(t_lip *lip);
void		ft_lipapp(t_lip **lip, t_lip *new);
void		ft_lipprep(t_lip **lip, t_lip *new);
int			ft_liplen(t_lip *lip);
int			ft_printlip(t_lip *lip);

// color gradient
int			color(t_3d s, t_3d e, double percent);
int			get_color(t_3d current, t_3d start, t_3d end, t_bres b);

// points
uint32_t	rgb(double ratio);
int			assign_color(int z, int *range);
t_3d		iso(t_3d p3d);
t_3d		mk_3d(t_map *map, int x, int y);
int			ft_print3d(t_3d p);
int			isfst(t_3d p);
int			istop(t_3d p);

//map
t_map		*mkmap(t_lip *grid);
void		delmap(t_map *map);
int			map_get(t_map *map, int x, int y);
void		map_set(t_map *map, int x, int y, int z);
int			ft_printmap(t_map *map);

int			ft_strslen(char *strs[]);

void		ft_draw_line(mlx_image_t *img, t_3d p0, t_3d p1);
void		draw_wireframe(mlx_image_t *img, t_lip *grid);
t_lip		*parse_file(int argc, char *argv[]);
t_map		*grid_to_map(t_lip *grid);

#endif
