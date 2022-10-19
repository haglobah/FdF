/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:11:11 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/19 16:55:06 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
