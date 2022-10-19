/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:09:56 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/19 15:03:43 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	red(int clr)
{
	return ((clr >> 24) & 0xFF);
}
int	green(int clr)
{
	return ((clr >> 16) & 0xFF);
}
int	blue(int clr)
{
	return ((clr >> 8) & 0xFF);
}

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	color(t_3d s, t_3d e, double percent)
{
	int r = get_light(red(s.clr), red(e.clr), percent);
	int g = get_light(green(s.clr), green(e.clr), percent);
	int b = get_light(blue(s.clr), blue(e.clr), percent);
	return (r << 24) | (g << 16) | (b << 8) | (255);
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
	if (current.clr == end.clr)
		return (current.clr);
	return (color(start, end, percentage));
}

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
//		ft_print3d(p0);
		mlx_put_pixel(img, p0.x + (WIDTH / 2), p0.y + (HEIGHT / 3), get_color(p0, start, p1, b, map));
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
