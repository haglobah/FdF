/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 12:00:02 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/20 12:14:29 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_parse(t_parse *p)
{
	int	i;

	if (p->line != NULL)
		free(p->line);
	if (p->zs == NULL)
		return ;
	i = 0;
	while (p->zs[i] != NULL)
	{
		free(p->zs[i]);
		i++;
	}
	free(p->zs);
}
