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

t_lip	*parse_map(int argc, char *argv[])
{
	char	*fname;
	int		fd;
	char	*line;
	char	**zs;
	t_lip	*lipel;
	t_lip	*grid;

	if (argc != 2)
		return (NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Please provide the right file name :)\n");
		return (NULL);
	}
	grid = NULL;
	while ((line = get_next_line(fd)))
	{
		zs = ft_split(line, ' ');
		lipel = ft_strs_to_lip(zs);
		ft_lipapp(&grid, lipel);
	}
	ft_printlip(grid);
	close(fd);
	return (grid);
}

void	ft_putline(mlx_image_t *img, t_2d p1, t_2d p2, int color)
{
	//Bresenham
	while (p1.x < p2.x)
	{
		mlx_put_pixel(img, p1.x, p1.y, color);
		p1.x++;
	}
}

t_map	*mkmap(t_lip *grid)
{
	t_map	*map;

	map = (t_map *)ft_calloc(ft_liplen(grid), sizeof(int) * grid->width);
	if (!map)
	{
		ft_printf("allocating map failed.");
		return (NULL);
	}
	// DO I NEED THAT?
	return (NULL);
}

t_2d	iso(t_3d p3d)
{
	t_2d	p;

	p = (t_2d){(p3d.x - p3d.y) * cos(0.523599),
		-p3d.z + (p3d.x + p3d.y) * sin(0.523599)};
	return (p);
}

void	draw_point(mlx_image_t *img, t_3d p3d)
{
	t_2d	p;

	p = iso(p3d);
	mlx_put_pixel(img, p.x * 20 + 500, p.y * 20 + 500, 0xFFFFFFFF); //!! Segfaults when values are to big.
}

void	draw_conns(mlx_image_t *img,t_3d p)
{
	return ;
}

void	draw(mlx_image_t *img, int x, int y, t_lip *grid)
{
	t_3d	p;

	p = (t_3d){x, y, grid->ip[x]};
	draw_point(img, p);
	draw_conns(img, p);
}

void	draw_fdf(mlx_image_t *img, t_lip *grid)
{
	int	i;
	int	j;

	i = 0;
	while (grid != NULL)
	{
		j = 0;
		while (j < grid->width)
		{
			draw(img, i, j, grid);
			j++;
		}
		grid = grid->next;
		i++;
	}
}

void	draw_wireframe(mlx_image_t *img, t_lip *grid)
{
	t_map	*map;

	map = mkmap(grid);
	draw_fdf(img, grid);
	//isometric projection
	//ft_putline(img, (t_2d){0, 50}, (t_2d){100, 50}, 0xFFFFFFFF);
}

int32_t	main(int argc, char *argv[])
{
	mlx_t	*mlx;
	mlx_image_t	*g_img;
	t_lip	*grid;

	mlx = mlx_init(WIDTH, HEIGHT, "FDF", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	grid = parse_map(argc, argv);
	if (grid == NULL)
	{
		ft_printf("Parsing failed. Did you supply a *.fdf file?\n");
		return (EXIT_FAILURE);
	}
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	draw_wireframe(g_img, grid);
	mlx_image_to_window(mlx, g_img, 0, 0);   // Adds an image to the render queue.
	mlx_loop_hook(mlx, &key_hook, mlx);
	mlx_close_hook(mlx, (void (*)(void *))mlx_close_window, mlx);
	mlx_put_pixel(g_img, 100, 100, 0xFFFFFFFF);
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
