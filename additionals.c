/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additionals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:56:03 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/15 23:46:51 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void ftzoom(t_param *param, int sign)
{
    int x;
    int y;
    t_map ***map;
    
    y = 0;
    map = param->map;
    param->zoom += 0.1 * sign;
    while(map[y])
    {
        x = 0;
        while(map[y][x])
        {
            map[y][x]->y = map[y][x]->oy * param->zoom;
            map[y][x]->x = map[y][x]->ox * param->zoom;
            map[y][x]->z = map[y][x]->oz * param->zoom;
            if (param->proj == 0)
                map[y][x]->y -= map[y][x]->z;
            x++;
        }
        y++;
    }
}

void    shift_map(t_map ***map, int shifty, int shiftx)
{
    int x;
    int y;
    
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            map[y][x]->x += shiftx;
            map[y][x]->y += shifty;
            x++;
        }
        y++;
    }
}

void    change_position(t_map ***map, int keycode)
{
    if (keycode == 65362)
        shift_map(map, (HEIGHT / 10), 0);
    else if (keycode == 65364)
        shift_map(map, -(HEIGHT / 10), 0);
    else if (keycode == 65363)
        shift_map(map, 0, -(WIDTH / 10));
    else if (keycode == 65361)
        shift_map(map, 0, (WIDTH / 10));
    return ;
}

void parallel_projection(t_map ***map, float zoom)
{
    int	x;
	int	y;
	int	space;

    space = calcul_space(map);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			map[y][x]->ox = x * space;
			map[y][x]->oy = y * space;
            map[y][x]->x = map[y][x]->ox * zoom;
            map[y][x]->y = map[y][x]->oy * zoom;
            map[y][x]->z = map[y][x]->oz * zoom;
			x++;
		}
		y++;
	}
}
