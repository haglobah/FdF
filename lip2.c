/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lip2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:54:23 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/20 12:33:13 by bhagenlo         ###   ########.fr       */
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
		free((*lip)->ip);
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

void	ft_lipapp(t_lip **lip, t_lip *new)
{
	if (!lip || !new)
		return ;
	if (*lip)
		ft_liplast(*lip)->next = new;
	else
		*lip = new;
}

void	ft_lipprep(t_lip **lip, t_lip *new)
{
	if (!lip || !new)
		return ;
	if (*lip)
	{
		new->next = *lip;
		*lip = new;
	}
	else
		*lip = new;
}
