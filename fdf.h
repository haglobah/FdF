/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:57 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/06/19 12:38:43 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <memory.h>
# include <fcntl.h>

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

# define WIDTH 256
# define HEIGHT 256

typedef struct s_iplist
{
	int	*ip;
	struct s_iplist	*next;
}	t_lip;

t_lip	*ft_lipelem(int	*iarr);
void	ft_lipclear(t_lip **lip);
//t_lip	*ft_lipcpy(t_lip *lip);
void	ft_lipapp(t_lip **lip, t_lip *lipel);

typedef struct s_grid
{
	t_lip	*coors;
}	t_grid;

#endif
