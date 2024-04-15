/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:35:54 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/16 00:49:25 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void side_panel(t_param *param)
{
	int x, y;

	mlx_destroy_image(param->vars->mlx, param->img->img);
    param->img->img = mlx_new_image(param->vars->mlx, IMGW, IMGH);

	y = 0;
	while (y < TXTH)
	{
		x = 0;
		while (x < TXTW)
		{
			fill_img(param->img, x, y, 0xffffff);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(param->vars->mlx, param->vars->win, param->img->img, 0, 0);
	// mlx_string_put(param->vars->mlx, param->vars->win, 10, 20, 0xFFFFFF, "Use Mouse scroll button to zoom");
	// mlx_string_put(param->vars->mlx, param->vars->win, 10, 40, 0xFFFFFF, "Press 'M' to change the projection");
	// if (param->proj)
	// 	mlx_string_put(param->vars->mlx, param->vars->win, 10, 60, 0xFFFFFF, "Parallel Prj:");
	// else
	// 	mlx_string_put(param->vars->mlx, param->vars->win, 10, 60, 0xFFFFFF, "Isometric Prj:");
}

void handle_text(void *mlx, void *win, t_param *param)
{
	int x, y;
	t_data img;


	// mlx_destroy_image(param->vars->mlx, param->img->img);
    // param->img->img = mlx_new_image(param->vars->mlx, IMGW, IMGH);
	// y = 0;
	// while (y < TXTH)
	// {
	// 	x = 0;
	// 	while (x < TXTW)
	// 	{
	// 		fill_img(param->img, x, y, 0);
	// 		// mlx_put_image_to_window(param->vars->mlx, param->vars->win, param->img->img, 0, 0);
	// 		x++;
	// 	}
	// 	y++;
	// }
	// mlx_put_image_to_window(param->vars->mlx, param->vars->win, param->img->img, 0, 0);
	mlx_string_put(mlx, win, 10, 20, 0, "Use Mouse scroll button to zoom");
	mlx_string_put(mlx, win, 10, 40, 0, "Press 'M' to change the projection");
	if (param->proj)
		mlx_string_put(mlx, win, 10, 60, 0, "Parallel Prj:");
	else
		mlx_string_put(mlx, win, 10, 60, 0, "Isometric Prj:");
}

int handle_mouse(int button, int x, int y, t_param *param)
{
	double zoom = param->zoom;

	if (button == 4 && param->zoom < 5)
        ftzoom(param, 1);
    else if (button == 5 && param->zoom > 0.2)
        ftzoom(param, -1);
    else
        return (0);
	side_panel(param);
    // mlx_destroy_image(param->vars->mlx, param->img->img);
    // param->img->img = mlx_new_image(param->vars->mlx, IMGW, IMGH);
	// int i,j;
	// j = 0;
	// while (j < TXTH)
	// {
	// 	i = 0;
	// 	while (i < TXTW)
	// 	{
	// 		fill_img(param->img, i, j, 0xffffff);
	// 		i++;
	// 	}
	// 	j++;
	// }
	// printf("end\n");
	// mlx_put_image_to_window(param->vars->mlx, param->vars->win, param->img->img, 0, 0);
	mlx_destroy_image(param->vars->mlx, param->img->img);
	param->img->img = mlx_new_image(param->vars->mlx, IMGW, IMGH);
	center_position(param->map, 0, 0);
	draw_map(*(param->img), param->map);
    mlx_put_image_to_window(param->vars->mlx, param->vars->win, param->img->img, WIDTH - IMGW, 0);
	handle_text(param->vars->mlx, param->vars->win, param);
	char tmp[10];

	sprintf(tmp, "%f", zoom);
	mlx_string_put(param->vars->mlx, param->vars->win, 10, 80, 0xFFFFFF, tmp);
    return (0);
}

int	handle_key(int keycode, t_param *param)
{
    if (keycode == 65307)
    {
        free_map(param->map);
        mlx_destroy_window(param->vars->mlx, param->vars->win);
        exit(0);
    }
    else if (keycode >= 65361 && keycode <= 65364)
        change_position(param->map, keycode);
    else if (keycode == 109)
	{
		if (param->proj)
		{
			isometric_transform(param->map, param->zoom);
			param->proj = 0;
		}
		else
        {
			parallel_projection(param->map, param->zoom);
			param->proj = 1;
		}
		center_position(param->map, 0, 0);
	}
    else
        return (0);
    mlx_destroy_image(param->vars->mlx, param->img->img);
    param->img->img = mlx_new_image(param->vars->mlx, IMGW, IMGH);
    draw_map(*(param->img), param->map);
    mlx_put_image_to_window(param->vars->mlx, param->vars->win, param->img->img, WIDTH - IMGW, 0);
	handle_text(param->vars->mlx, param->vars->win, param);
	return (0);
}

void	handle_hooks(t_map ***map, t_vars *vars, t_data *img)
{
	t_param *param;

	param = malloc(sizeof(t_param));
	param->map = map;
	param->vars = vars;
	param->img = img;
	param->proj = 0;
	param->zoom = 1;

	
	mlx_hook(param->vars->win, 17, ButtonPressMask, ftdestroy, param);
	mlx_expose_hook(param->vars->win, ftexpose, param);
	mlx_key_hook(param->vars->win, handle_key, param);
	mlx_mouse_hook(param->vars->win, handle_mouse, param);
}
