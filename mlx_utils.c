/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 23:33:04 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/16 00:10:09 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void free_map(t_map ***map)
{
    int y;
    int x;

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

int ftdestroy(t_param *param)
{
    free_map(param->map);
    mlx_destroy_window(param->vars->mlx, param->vars->win);
    exit(0);
    return (0);
}

int ftexpose(t_param *param)
{
    mlx_destroy_image(param->vars->mlx, param->img->img);
    param->img->img = mlx_new_image(param->vars->mlx, IMGW, IMGH);
    center_position(param->map, 0, 0);
    draw_map(*(param->img), param->map);
    mlx_put_image_to_window(param->vars->mlx, param->vars->win, param->img->img, WIDTH - IMGW, 0);
    handle_text(param->vars->mlx, param->vars->win, param);
    return (0);
}

void	fill_img(t_data *data, long x, long y, unsigned int color)
{
	char	*dst;

    if (y >= TXTH || x >= TXTW || x < 0 || y < 0 || x >= INT_MAX || y >= INT_MAX)
    {
        return ;
    }
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	my_mlx_pixel_put(t_data *data, long x, long y, unsigned int color)
{
	char	*dst;

    if (y >= IMGH || x >= IMGW || x < 0 || y < 0 || x >= INT_MAX || y >= INT_MAX)
    {
        return ;
    }
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
