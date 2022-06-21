/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhagenlo <bhagenlo@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 12:37:54 by bhagenlo          #+#    #+#             */
/*   Updated: 2022/06/21 11:53:41 by bhagenlo         ###   ########.fr       */
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

//Bresenham
void	ft_draw_line(mlx_image_t *img, t_2d p0, t_2d p1, int color)
{
	int	err;
	int	e2;
	t_bres	b;

	b = (t_bres){
		(t_2d){abs(p1.x - p0.x),
			abs(p1.y - p0.y)},
		(t_2d){(p0.x < p1.x) * 2 - 1,
			((p0.y < p1.y) * 2 - 1)}};
	err = ((b.d.x > b.d.y) * b.d.x + !(b.d.x < b.d.y) * (-b.d.y))/2;
	while (1)
	{
		mlx_put_pixel(img, p0.x + (WIDTH / 2), p0.y + (HEIGHT / 3), color);
		if (p0.x == p1.x && p0.y == p1.y)
			break;
		e2 = err;
		if (e2 > -b.d.x)
		{
			err -= b.d.y;
			p0.x += b.s.x;
		}
		if (e2 < b.d.y) {
			err += b.d.x;
			p0.y += b.s.y;
		}
	}
}

int	**mkmap(t_lip *grid)
{
	int	**map;
	int	*line;
	int	i;

	map = (int **)ft_calloc(ft_liplen(grid), sizeof(int) * grid->width);
	if (!map)
	{
		ft_printf("allocating map failed.");
		return (NULL);
	}
	while ();
	return (map);
}

t_2d	iso(t_3d p3d)
{
	t_2d	p;

	p3d = (t_3d){p3d.x * SCALE, p3d.y * SCALE, p3d.z * (SCALE / 2)};
	p = (t_2d){(p3d.x - p3d.y) * cos(0.523599),
		-p3d.z + (p3d.x + p3d.y) * sin(0.523599)};
	return (p);
}

void	draw_point(mlx_image_t *img, t_3d p3d)
{
	t_2d	p;

	p = iso(p3d);
	mlx_put_pixel(img, p.x + (WIDTH / 2), p.y + (HEIGHT / 3), 0xFFFFFFFF); //!! Segfaults when values are to big.
}

int	isfst(t_3d p)
{
	return (p.x == 0);
}

int	istop(t_3d p)
{
	return (p.y == 0);
}

void	draw_conns(mlx_image_t *img, t_3d p)
{
	t_3d	here;
	t_3d	to_left;
	t_3d	to_top;

	to_top = (t_3d){p.x - 1, p.y, p.z}; //This is not really the top, I have to get the value of (p - 1).z, too.
	to_left = (t_3d){p.x, p.y - 1, p.z};
	if (isfst(p) && istop(p))
		;//nothing
	else if (istop(p))
		ft_draw_line(img, iso(here), iso(to_left), WHITE);
	else if (isfst(p))
		ft_draw_line(img, iso(here), iso(to_top), WHITE);
	else
	{
		ft_draw_line(img, iso(here), iso(to_left), WHITE);
		ft_draw_line(img, iso(here), iso(to_top), WHITE);
	}
	return ;
}

void	draw_a_conn(mlx_image_t *img, t_3d p)
{
	t_3d	to_left = (t_3d){p.x, p.y - 1, p.z};

	ft_draw_line(img, iso(p), iso(to_left), WHITE);
}

int	ft_print3d(t_3d p)
{
	ft_printf("x: %i, y: %i, z: %i\n", p.x, p.y, p.z);
	return (0);
}

void	draw(mlx_image_t *img, int x, int y, t_lip *grid)
{
	t_3d	p;

	p = (t_3d){x, y, grid->ip[y]};
	ft_print3d(p);
	draw_point(img, p);
	draw_a_conn(img, p, grid);
}

void	draw_fdf(mlx_image_t *img, t_lip *grid)
{
	int	x;
	int	y;

	x = 0;
	while (grid != NULL)
	{
		y = 0;
		while (y < grid->width)
		{
			draw(img, x, y, grid);
			y++;
		}
		grid = grid->next;
		x++;
	}
}

void	draw_wireframe(mlx_image_t *img, t_lip *grid)
{
	int	**map;

	map = mkmap(grid);
	draw_fdf(img, grid);
//	isometric projection
//	ft_draw_line(img, (t_2d){0, 50}, (t_2d){100, 100}, 0xFFFFFFFF);
//	ft_draw_line(img, (t_2d){100, 100}, (t_2d){100, 0}, 0xFFFFFFFF);
//	ft_draw_line(img, (t_2d){0, 50}, (t_2d){100, 0}, 0xFFFFFFFF);
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
//	mlx_put_pixel(g_img, 100, 100, 0xFFFFFFFF);
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
