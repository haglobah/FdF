/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mk_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:45:15 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/20 12:27:26 by bhagenlo         ###   ########.fr       */
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

void	free_behind(int **arr, int i)
{
	int	k;

	k = -1;
	while (++k < i)
		free(arr[k]);
}

int	fill_arr(t_map *map, t_lip *grid, int **arr)
{
	int		i;
	int		j;

	i = 0;
	while (grid != NULL)
	{
		arr[i] = (int *)ft_calloc(map->width, sizeof(int));
		if (arr[i] == NULL)
		{
			free_behind(arr, i);
			return (0);
		}
		j = 0;
		while (j < grid->width)
		{
			arr[i][j] = grid->ip[j];
			j++;
		}
		grid = grid->next;
		i++;
	}
	return (1);
}

t_map	*mkmap(t_lip *grid)
{
	int		**arr;
	t_map	*map;

	map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->len = ft_liplen(grid);
	map->width = grid->width;
	arr = (int **)ft_calloc(map->len, sizeof(int *));
	if (!arr)
		return (NULL);
	if (!fill_arr(map, grid, arr))
		return (NULL);
	map->arr = arr;
	hrange(map, map->range);
	return (map);
}
