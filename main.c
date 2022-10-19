/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:54 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/10/19 16:53:51 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

int32_t	main(int argc, char *argv[])
{
	mlx_t		*mlx;
	mlx_image_t	*g_img;
	t_lip		*grid;

	mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	grid = parse_file(argc, argv);
	if (grid == NULL)
	{
		ft_printf("Parsing failed. Did you supply a *.fdf file?\n");
		return (EXIT_FAILURE);
	}
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	draw_wireframe(g_img, grid);
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_loop_hook(mlx, &key_hook, mlx);
	mlx_close_hook(mlx, (void (*)(void *))mlx_close_window, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
