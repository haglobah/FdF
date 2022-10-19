/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:19:11 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/19 17:19:29 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	red(int clr)
{
	return ((clr >> 24) & 0xFF);
}

static int	green(int clr)
{
	return ((clr >> 16) & 0xFF);
}

static int	blue(int clr)
{
	return ((clr >> 8) & 0xFF);
}

static int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	color(t_3d s, t_3d e, double percent)
{
	int	r;
	int	g;
	int	b;

	r = get_light(red(s.clr), red(e.clr), percent);
	g = get_light(green(s.clr), green(e.clr), percent);
	b = get_light(blue(s.clr), blue(e.clr), percent);
	return ((r << 24) | (g << 16) | (b << 8) | (255));
}
