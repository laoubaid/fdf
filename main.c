/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:05:01 by laoubaid          #+#    #+#             */
/*   Updated: 2024/03/26 03:49:33 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ftclose(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
    exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;
    if (y > 1080 || x > 1920 || x < 0 || y < 0)
    {
        return ;
    }
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void   get_maxt(t_map ***map, int *x, int *y)
{
    int i, j;

    i = 0;
    *x = 0;
    *y = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
            j++;
        if (j > *x)
            *x = j;
        i++;
    }
    *y = i;
    printf("%d %d\n", *x, *y);
    fflush(stdout);
}

void drawline(t_data *img, t_map *p1, t_map *p2)
{
    int dx, dy, x, y;
    int cst, color;
 
    dx = p2->x - p1->x;
    dy = p2->y - p1->y;
    x = p1->x;
    y = p1->y;
    int sx, sy, err, e2;

    if (dx > 0)
		sx = 1;
    else if (dx < 0)
		sx = -1;
    else
		sx = 0;

    if (dy > 0)
		sy = 1;
    else if (dy < 0)
		sy = -1;
    else
		sy = 0;

    dx = abs(dx);
    dy = abs(dy);

    err = dx - dy;
    if (dx > dy && dx && dy)
        cst = abs(p1->color - p2->color) / (dy);
    else if (dx && dy)
        cst = abs(p1->color - p2->color) / (dy);
    color = p1->color;
    while (x != p2->x || y != p2->y)
	{
		my_mlx_pixel_put(img, x, y, color);
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
        color += cst;
    }
}

int	main(int ac, char **av)
{
    int x, y;
    int i, j;
    int h = 1080, w= 1920;
	t_vars  vars;
	t_data	img;
    t_map    ***map;
    int max_x, max_y; 

	vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, w, h, "test");
	img.img = mlx_new_image(vars.mlx, w, h);

	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    map = get_map(av[1]);
    y = 0;
    get_maxt(map, &max_x, &max_y);
    // printf("%d\n", max_y);
    int space_h = (h / max_y) * 0.8;
    int space_w = (w / max_x) * 0.8;
    int tmp_y = 0;
    int tmp_x = 0;
    i = max_y / 2;
    while (map[y])
    {
        x = 0;
        j = max_x / 2;
        while (map[y][x])
        {
            tmp_y = y * space_h - (space_h / 1 * j);
            tmp_x = x * space_w + (space_w / 2 * i);
            tmp_y += (h / 2) - (((max_y - 1) * space_h) / 2);
            tmp_x += (w / 2) - (((max_x - 1) * space_w) / 2);
            tmp_y -= map[y][x]->z;
            // printf("x: %d , y: %d , color: %d\n", tmp_x, tmp_y, map[y][x]->color);
            map[y][x]->x = tmp_x;
            map[y][x]->y = tmp_y;
            my_mlx_pixel_put(&img, tmp_x, tmp_y, map[y][x]->color);
            j--;
            x++;
        }
        mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
        i--;
        y++;
    }
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x+1])
                drawline(&img, map[y][x], map[y][x+1]);
            if (map[y+1])
                if (map[y+1][x])
                    drawline(&img, map[y][x], map[y+1][x]);
            x++;
        }
        y++;
    }
    mlx_hook(vars.win, 2, 1L<<0, ftclose, &vars);
	mlx_loop(vars.mlx);
}


