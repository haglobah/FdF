/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:29:16 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/20 09:31:18 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_rgb	*mk_rgb(uint8_t r, uint8_t g, uint8_t b)
{
	t_rgb	*c;

	c = (t_rgb *)ft_calloc(3, sizeof(t_rgb));
	c->r = r;
	c->g = g;
	c->b = b;
	return (c);
}

void	rgb_assign(t_rgb *c, uint8_t r, uint8_t g, uint8_t b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}

void	rgb_region_switch(t_rgb *c, int region, int x)
{
	if (region == 0)
		rgb_assign(c, 255, x, 0);
	else if (region == 1)
		rgb_assign(c, 255 - x, 255, 0);
	else if (region == 2)
		rgb_assign(c, 0, 255, x);
	else if (region == 3)
		rgb_assign(c, 0, 255 - x, 255);
	else if (region == 4)
		rgb_assign(c, x, 0, 255);
	else if (region == 5)
		rgb_assign(c, 255, 0, 255 - x);
}

uint32_t	rgb(double ratio)
{
	int			normalized;
	int			region;
	int			x;
	t_rgb		*c;
	uint32_t	clr;		

	normalized = (int)(ratio * 256 * 6);
	region = normalized / 256;
	x = normalized % 256;
	c = mk_rgb(0, 0, 0);
	rgb_region_switch(c, region, x);
	clr = (c->r << 24) | (c->g << 16) | (c->b << 8) | 255;
	free(c);
	return (clr);
}

int	assign_color(int z, int *range)
{
	double		absrange;
	double		ratio;
	uint32_t	color;

	absrange = (double)range[1] - (double)range[0];
	ratio = ((double)z - (double)range[0]) / absrange;
	color = rgb(ratio);
	return (color);
}
