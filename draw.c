/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:09:56 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/06/22 15:47:22 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t rgb(double ratio)
{
    //we want to normalize ratio so that it fits in to 6 regions
    //where each region is 256 units long
    int normalized = (int)(ratio * 256 * 6);

    //find the region for this position
    int region = normalized / 256;

    //find the distance to the start of the closest region
    int x = normalized % 256;

    uint8_t r = 0, g = 0, b = 0;
    switch (region)
    {
    case 0: r = 255; g = 0;   b = 0;   g += x; break;
    case 1: r = 255; g = 255; b = 0;   r -= x; break;
    case 2: r = 0;   g = 255; b = 0;   b += x; break;
    case 3: r = 0;   g = 255; b = 255; g -= x; break;
    case 4: r = 0;   g = 0;   b = 255; r += x; break;
    case 5: r = 255; g = 0;   b = 255; b -= x; break;
    }
    return (r << 24) | (g << 16) | (b << 8) | (255);
}

void	hrange(t_map *map, int *minmax)
{
	int	i;
	int	j;

	minmax[0] = 1000000;
	minmax[1] = -1000000;
	i = -1;
	while (++i < map->len)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map_get(map, j, i) < minmax[0])
				minmax[0] = map_get(map, j, i);
			if (map_get(map, j, i) > minmax[1])
				minmax[1] = map_get(map, j, i);
		}
	}
}

int	color(t_map *map, t_3d p)
{
	int	range[2];
	int	min;
	int	color;

	hrange(map, range);
//	p.z -= range[0];
	ft_printf("clr: %x\n", rgb((double)p.z / 10.0));
//	color = rgb((double)p.z / (double)(range[1] - range[0]));
	return (rgb((double)p.z / 10.0));
}

void	ft_draw_line(mlx_image_t *img, t_2d p0, t_2d p1, t_3d p, t_map *map)
{
	int	err;
	int	e2;
	t_bres	b;

	b = (t_bres){
		(t_2d){abs(p1.x - p0.x),
			abs(p1.y - p0.y)},
		(t_2d){(p0.x < p1.x) * 2 - 1,
			((p0.y < p1.y) * 2 - 1)}};
	err = ((b.d.x > b.d.y) * b.d.x + !(b.d.x < b.d.y) * (-b.d.y))/2;
	while (1)
	{
		mlx_put_pixel(img, p0.x + (WIDTH / 2), p0.y + (HEIGHT / 3), color(map, p));
		if (p0.x == p1.x && p0.y == p1.y)
			break;
		e2 = err;
		if (e2 > -b.d.x)
		{
			err -= b.d.y;
			p0.x += b.s.x;
		}
		if (e2 < b.d.y) {
			err += b.d.x;
			p0.y += b.s.y;
		}
	}
}

t_2d	iso(t_3d p3d)
{
	t_2d	p;

	p3d = (t_3d){p3d.x * SCALE, p3d.y * SCALE, p3d.z * (SCALE / 2)};
	p = (t_2d){(p3d.x - p3d.y) * cos(0.523599),
		-p3d.z + (p3d.x + p3d.y) * sin(0.523599)};
	return (p);
}

void	draw_point(mlx_image_t *img, t_3d p3d, t_map *map)
{
	t_2d	p;

	p = iso(p3d);
	mlx_put_pixel(img,
				  p.x + (WIDTH / 2),
				  p.y + (HEIGHT / 3),
				  color(map, p3d));//!! Segfaults when values to big
}

int	isfst(t_3d p)
{
	return (p.x == 0);
}

int	istop(t_3d p)
{
	return (p.y == 0);
}

void	draw_conns(mlx_image_t *img, t_3d p, t_map *map)
{
	t_3d	to_left;
	t_3d	to_top;

	if (isfst(p) && istop(p))
		;
	else if (istop(p))
	{
		to_left = (t_3d){p.x - 1, p.y, map_get(map, p.x - 1, p.y)};
		ft_draw_line(img, iso(p), iso(to_left), p, map);
	}
	else if (isfst(p))
	{
		to_top = (t_3d){p.x, p.y - 1, map_get(map, p.x, p.y - 1)};
		ft_draw_line(img, iso(p), iso(to_top), p, map);
	}
	else
	{
		to_left = (t_3d){p.x - 1, p.y, map_get(map, p.x - 1, p.y)};
		to_top = (t_3d){p.x, p.y - 1, map_get(map, p.x, p.y - 1)};
		ft_draw_line(img, iso(p), iso(to_left), p, map);
		ft_draw_line(img, iso(p), iso(to_top), p, map);
	}
	return ;
}

void	draw_a_conn(mlx_image_t *img, t_3d p, t_map *map)
{
	t_3d	to_left = (t_3d){0, 1, map_get(map, 0, 1)};

	ft_draw_line(img, iso(p), iso(to_left), p, map);
}

int	ft_print3d(t_3d p)
{
	ft_printf("x: %i, y: %i, z: %i\n", p.x, p.y, p.z);
	return (0);
}

void	draw(mlx_image_t *img, int x, int y, t_map *map)
{
	t_3d	p;

	p = (t_3d){x, y, map_get(map, x, y)};
	ft_print3d(p);
	draw_point(img, p, map);
	draw_conns(img, p, map);
}

void	draw_fdf(mlx_image_t *img, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->len)
	{
		x = 0;
		while (x < map->width)
		{
			draw(img, x, y, map);
			x++;
		}
		y++;
	}
}

void	draw_wireframe(mlx_image_t *img, t_lip *grid)
{
	t_map *map;

	map = mkmap(grid);
	draw_fdf(img, map);
	delmap(map);
}
