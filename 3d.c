/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:09:51 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/19 16:30:22 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_3d	mk_3d(t_map *map, int x, int y)
{
	int	z;
	int	clr;

	z = map_get(map, x, y);
	clr = assign_color(z, map->range);
	return ((t_3d){x, y, z, clr});
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
