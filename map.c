/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:18:47 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/18 15:48:06 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_map	*mkmap(t_lip *grid)
{
	int	i;
	int	j;
	int	**arr;
	int	*range;
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->len = ft_liplen(grid);
	map->width = grid->width;
	arr = (int **)ft_calloc(map->len, sizeof(int *));
	if (!arr)
		return (NULL);
	i = 0;
	while (grid != NULL)
	{
		arr[i] = (int *)ft_calloc(map->width, sizeof(int));
		j = 0;
		while (j < grid->width)
		{
			arr[i][j] = grid->ip[j];
			j++;
		}
		grid = grid->next;
		i++;
	}
	map->arr = arr;
	range = (int *)ft_calloc(2, sizeof(int));
	hrange(map, map->range);
	ft_printf("ranging from %i to %i\n", map->range[0], map->range[1]);
	return (map);
}

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
