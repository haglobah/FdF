/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:09:56 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/18 16:55:10 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	color(t_map *map, t_3d p, double percentage)
{
	double	absrange;

//	p.z -= range[0];
//	ft_printf("clr: %x\n", rgb((double)p.z / 10.0));
//	absrange = (double)map->range[1] - (double)map->range[0];
	absrange = (double)10 - (double)(-10);
	if (absrange == 0.0)
		absrange = 1.0;
	return (rgb(((double)p.z - (double)(-10)) / 20.0));
}

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

/*
** Get color. Result depends on point position.
** This function is needed to create linear gradient.
*/

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int	get_color(t_3d current, t_3d start, t_3d end, t_bres b, t_map *map)
{
	double	percentage;

	if (b.d.x > b.d.y)
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);
	if (start.z == end.z)
		return (color(map, current, 1.0));
	if (start.z < end.z)
		percentage = 1.0 - percentage;
	return (color(map, current, percentage));
}

int	interpolate_color();

void	ft_draw_line(mlx_image_t *img, t_3d p0, t_3d p1, t_map *map)
{
	int	err;
	int	e2;
	t_bres	b;
	t_3d	start;

	b = (t_bres){
		(t_2d){abs(p1.x - p0.x),
			abs(p1.y - p0.y)},
		(t_2d){(p0.x < p1.x) * 2 - 1,
			((p0.y < p1.y) * 2 - 1)}};
	err = ((b.d.x > b.d.y) * b.d.x + !(b.d.x < b.d.y) * (-b.d.y))/2;
	start = p0;
	while (1)
	{
		ft_print3d(p0);
		mlx_put_pixel(img, p0.x + (WIDTH / 2), p0.y + (HEIGHT / 3), p0.clr);
		if (p0.x == p1.x && p0.y == p1.y)
			break;
		e2 = err;
		if (e2 > -b.d.x)
		{
			err -= b.d.y;
			p0.x += b.s.x;
			p0.z += (p0.z < p1.z) * 1 + (p0.z > p1.z) * -1;
		}
		if (e2 < b.d.y) {
			err += b.d.x;
			p0.y += b.s.y;
			p0.z += (p0.z < p1.z) * 1 + (p0.z > p1.z) * -1;
		}
	}
}

void	draw_point(mlx_image_t *img, t_3d p3d, t_map *map)
{
	t_3d	p;

	p = iso(p3d);
	mlx_put_pixel(img,
				  p.x + (WIDTH / 2),
				  p.y + (HEIGHT / 3),
				  p.clr);//!! Segfaults when values to big
}

void	draw_conns(mlx_image_t *img, t_3d p, t_map *map)
{
	t_3d	to_left;
	t_3d	to_top;

	if (isfst(p) && istop(p))
		;
	else if (istop(p))
	{
		to_left = mk_3d(map, p.x - 1, p.y);
		ft_draw_line(img, iso(p), iso(to_left), map);
	}
	else if (isfst(p))
	{
		to_top = mk_3d(map, p.x, p.y - 1);
		ft_draw_line(img, iso(p), iso(to_top), map);
	}
	else
	{
		to_left = mk_3d(map, p.x - 1, p.y);
		to_top = mk_3d(map, p.x, p.y - 1);
		ft_draw_line(img, iso(p), iso(to_left), map);
		ft_draw_line(img, iso(p), iso(to_top), map);
	}
	return ;
}

void	draw_a_conn(mlx_image_t *img, t_3d p, t_map *map)
{
	t_3d	to_left = mk_3d(map, 0, 1);

	ft_draw_line(img, iso(p), iso(to_left), map);
}

void	draw(mlx_image_t *img, int x, int y, t_map *map)
{
	t_3d	p;

	p = mk_3d(map, x, y);
	draw_point(img, p, map);
	draw_conns(img, p, map);
}

void	draw_fdf(mlx_image_t *img, t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->len)
	{
		x = -1;
		while (++x < map->width)
			draw(img, x, y, map);
	}
}

void	draw_wireframe(mlx_image_t *img, t_lip *grid)
{
	t_map *map;

	map = mkmap(grid);
	draw_fdf(img, map);
	delmap(map);
}
