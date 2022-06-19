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

t_lip	*ft_lipelem(int	*iarr)
{
	t_lip	*node;

	node = (t_lip *)ft_calloc(1, sizeof(t_lip));
	if (node == NULL)
		return (NULL);
	node->ip = iarr;
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
