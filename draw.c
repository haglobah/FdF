/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:09:56 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/20 12:24:39 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_conns(mlx_image_t *img, t_3d p, t_map *map)
{
	t_3d	to_left;
	t_3d	to_top;

	if (isfst(p) && istop(p))
		;
	else if (istop(p))
	{
		to_left = mk_3d(map, p.x - 1, p.y);
		ft_draw_line(img, iso(p), iso(to_left));
	}
	else if (isfst(p))
	{
		to_top = mk_3d(map, p.x, p.y - 1);
		ft_draw_line(img, iso(p), iso(to_top));
	}
	else
	{
		to_left = mk_3d(map, p.x - 1, p.y);
		to_top = mk_3d(map, p.x, p.y - 1);
		ft_draw_line(img, iso(p), iso(to_left));
		ft_draw_line(img, iso(p), iso(to_top));
	}
}

void	draw_map(mlx_image_t *img, t_map *map)
{
	int	x;
	int	y;

	y = -1;
	while (++y < map->len)
	{
		x = -1;
		while (++x < map->width)
			draw_conns(img, mk_3d(map, x, y), map);
	}
}

void	draw_wireframe(mlx_image_t *img, t_lip *grid)
{
	t_map	*map;

	map = mkmap(grid);
	draw_map(img, map);
	delmap(map);
}
