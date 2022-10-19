/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_interpolation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 15:54:37 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/19 17:19:25 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	if (distance == 0)
		return (1.0);
	return (placement / distance);
}

int	get_color(t_3d current, t_3d start, t_3d end, t_bres b)
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
