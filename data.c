/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:10:28 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/19 17:13:11 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_strslen(char *strs[])
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		i++;
	}
	return (i);
}

static int	ft_printstrs(char *strs[])
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		ft_printf("%s\n", strs[i]);
		i++;
	}
	return (i);
}

t_lip	*ft_strs_to_lip(char *zs[])
{
	int	i;
	int	*iarr;
	int	alen;
	int	tmp;

	i = 0;
	alen = ft_strslen(zs);
	iarr = (int *)ft_calloc(alen, sizeof(int));
	while (zs[i] != NULL)
	{
		iarr[i] = ft_atoi(zs[i]);
		i++;
	}
	return (ft_lipelem(iarr, alen));
}

t_lip	*parse_file(int argc, char *argv[])
{
	t_parse	p;
	t_lip	*lipel;
	t_lip	*grid;

	if (argc != 2)
		return (NULL);
	p.fd = open(argv[1], O_RDONLY);
	if (p.fd == -1)
	{
		ft_printf("Please provide the right file name :)\n");
		return (NULL);
	}
	grid = NULL;
	while (1)
	{
		p.line = get_next_line(p.fd);
		if (!p.line)
			break ;
		p.zs = ft_split(p.line, ' ');
		lipel = ft_strs_to_lip(p.zs);
		ft_lipapp(&grid, lipel);
	}
	close(p.fd);
	return (grid);
}
