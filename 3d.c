/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:09:51 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/19 14:48:00 by bhagenlo         ###   ########.fr       */
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

int	assign_color(int z, int *range)
{
	double	absrange = (double)range[1] - (double)range[0];

	double	ratio = ((double)z - (double)range[0])/ absrange;
	printf("%f, ", ratio);
	uint32_t	color = rgb(ratio);
	
	return (color);
}

t_3d	mk_3d(t_map *map, int x, int y)
{
	int	z = map_get(map, x, y);
	int	clr = assign_color(z, map->range);
	return (t_3d){x, y, z, clr};
}

int	ft_print3d(t_3d p)
{
	ft_printf("x: %i, y: %i, z: %i, clr: %p\n", p.x, p.y, p.z, p.clr);
	return (0);
}

int	isfst(t_3d p)
{
	return (p.x == 0);
}

int	istop(t_3d p)
{
	return (p.y == 0);
}

t_3d	iso(t_3d p3d)
{
	t_3d	p_iso;
	int		x;
	int		y;

	p3d.x *= SCALE;
	p3d.y *= SCALE;
	x = (p3d.x - p3d.y) * cos(0.523599);
	y = -(p3d.z * (SCALE / 16)) + (p3d.x + p3d.y) * sin(0.523599);
	p_iso.x = x;
	p_iso.y = y;
	p_iso.z = p3d.z;
	p_iso.clr = p3d.clr;
	return (p_iso);
}
