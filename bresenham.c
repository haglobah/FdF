/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:07:24 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/19 17:17:21 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	offset_x(int window_width)
{
	return (window_width / 3);
}

int	offset_y(int window_height)
{
	return (window_height / 8);
}

void	put_pxl(mlx_image_t *img, t_3d p0, int color)
{
	int	pxl_x;
	int	pxl_y;

	pxl_x = p0.x + offset_x(WIDTH);
	pxl_y = p0.y + offset_y(HEIGHT);
	if (pxl_x >= WIDTH || pxl_x < 0 || pxl_y >= HEIGHT || pxl_y < 0)
		return ;
	mlx_put_pixel(img, pxl_x, pxl_y, color);
}

void	ft_draw_line(mlx_image_t *img, t_3d p0, t_3d p1, t_map *map)
{
	t_bres	b;
	t_3d	start;

	b = (t_bres){(t_2d){abs(p1.x - p0.x), abs(p1.y - p0.y)},
		(t_2d){(p0.x < p1.x) * 2 - 1, ((p0.y < p1.y) * 2 - 1)}, (int)0, (int)0};
	b.err = ((b.d.x > b.d.y) * b.d.x + !(b.d.x < b.d.y) * (-b.d.y)) / 2;
	start = p0;
	while (1)
	{
		put_pxl(img, p0, get_color(p0, start, p1, b));
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		b.e2 = b.err;
		if (b.e2 > -b.d.x)
		{
			b.err -= b.d.y;
			p0.x += b.s.x;
		}
		if (b.e2 < b.d.y)
		{
			b.err += b.d.x;
			p0.y += b.s.y;
		}
	}
}
