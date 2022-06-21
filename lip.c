/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:11 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/06/19 17:11:44 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_lip	*ft_lipelem(int *iarr, int width)
{
	t_lip	*node;

	node = (t_lip *)ft_calloc(1, sizeof(t_lip));
	if (node == NULL)
		return (NULL);
	node->ip = iarr;
	node->width = width;
	node->next = NULL;
	return (node);
}

void	ft_lipclear(t_lip **lip)
{
	t_lip	*tmp;

	if (!lip)
		return ;
	while (*lip)
	{
		tmp = (*lip)->next;
		free(*lip);
		*lip = tmp;
	}
}

static t_lip	*ft_liplast(t_lip *lip)
{
	if (!lip)
		return (NULL);
	while (lip->next)
		lip = lip->next;
	return (lip);
}

void	ft_lipapp(t_lip **lip, t_lip *lipel)
{
	if (!lip || !lipel)
		return ;
	if (*lip)
		ft_liplast(*lip)->next = lipel;
	else
		*lip = lipel;
}

int	ft_liplen(t_lip *lip)
{
	int	i;

	i = 0;
	while (lip)
	{
		lip = lip->next;
		i++;
	}
	return (i);
}

int	ft_printia(int *ip, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		ft_printf(" %i", ip[i]);
		i++;
	}
	ft_printf("\n");
	return (i);
}

int	ft_printlip(t_lip *lip)
{
	ft_printf(".fdf:\n");
	while (lip)
	{
		ft_printia(lip->ip, lip->width);
		lip = lip->next;
	}
	ft_printf("\n");
	return (0);
}
