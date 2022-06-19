/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:54 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/06/19 12:39:42 by bhagenlo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_hook(void* param)
{
	mlx_t* mlx;

	mlx = param;
	if (mlx_is_key_down(param, MLX_KEY_ESCAPE))
		mlx_close_window(param);
}

static int	ft_strslen(char *strs[])
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		i++;
	}
	return (i);
}

t_lip	*ft_strs_to_lip(char *zs[])
{
	int	i;
	int	*iarr;

	i = 0;
	while (zs[i] != NULL)
	{
		iarr[i] = ft_atoi(zs[i]);
	}
	return (ft_lipelem(iarr));
}

t_lip	*parse_map(int argc, char *argv[])
{
	char	*fname;
	int		fd;
	char	*line;
	char	**zs;
	int	width;
	int	*iarr;
	t_lip	*lip;

	if (argc != 2)
		return (NULL);
	fname = argv[1];
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Please provide the right file name :)\n");
		return (NULL);
	}
	line = get_next_line(fd);
	zs = ft_split(line, ' ');
	width = ft_strslen(zs);
	iarr = (int *)ft_calloc(width, sizeof(int));
	lip = ft_strs_to_lip(zs);
	close(fd);
	return (lip);
}

mlx_image_t	*create_map(mlx_t *mlx, t_lip *grid)
{
	return (mlx_new_image(mlx, WIDTH, HEIGHT));
}

int32_t	main(int argc, char *argv[])
{
	mlx_t	*mlx;
	mlx_image_t	*g_img;
	t_lip	*grid;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	grid = parse_map(argc, argv);
	if (grid == NULL)
	{
		ft_printf("Parsing failed. Did you supply a *.fdf file?\n");
		return (EXIT_FAILURE);
	}
	g_img = create_map(mlx, grid);   // Creates a new image.
	mlx_image_to_window(mlx, g_img, 0, 0);   // Adds an image to the render queue.
	mlx_loop_hook(mlx, &key_hook, mlx);
	mlx_close_hook(mlx, (void (*)(void *))mlx_close_window, mlx);
	mlx_put_pixel(g_img, 100, 100, 0xFFFFFFFF);
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
