/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:18:47 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/19 16:52:30 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	delmap(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->len)
	{
		free(map->arr[i]);
		++i;
	}
	free(map->arr);
	free(map);
}

int	map_get(t_map *map, int x, int y)
{
	return (map->arr[y][x]);
}

void	map_set(t_map *map, int x, int y, int z)
{
	map->arr[y][x] = z;
}

int	ft_printmap(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	ft_printf("map: .fdf\n");
	while (++i < map->len)
	{
		j = -1;
		while (++j < map->width)
			ft_printf(" %i", map_get(map, j, i));
		ft_printf("\n");
	}
	ft_printf("\n");
	return (0);
}
