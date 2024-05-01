/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:33:04 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/25 00:44:20 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	display_img(t_param *param)
{
	t_vars	*vars;

	vars = param->vars;
	mlx_destroy_image(param->vars->mlx, param->img->img);
	param->img->img = mlx_new_image(param->vars->mlx, WIDTH, HEIGHT);
	draw_map(*(param->img), param->map);
	mlx_put_image_to_window(vars->mlx, vars->win, param->img->img, 0, 0);
}

void	free_map(t_map ***map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			free(map[y][x]);
			x++;
		}
		free(map[y]);
		y++;
	}
	free(map);
}

int	ftdestroy(t_param *param)
{
	free_map(param->map);
	mlx_destroy_image(param->vars->mlx, param->img->img);
	mlx_destroy_window(param->vars->mlx, param->vars->win);
	mlx_destroy_display(param->vars->mlx);
	free(param->vars->mlx);
	free(param);
	exit(0);
	return (0);
}

int	ftexpose(t_param *param)
{
	t_vars	*vars;

	vars = param->vars;
	center_position(param->map, 0, 0);
	draw_map(*(param->img), param->map);
	mlx_put_image_to_window(vars->mlx, vars->win, param->img->img, 0, 0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, long x, long y, unsigned int color)
{
	char	*dst;

	if (y >= HT || x >= WT || x < 0 || y < 0 || x >= INT_MAX || y >= INT_MAX)
	{
		return ;
	}
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
