/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additionals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:56:03 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/22 16:52:06 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	handle_rotation2(int keycode, t_param *param)
{
	if (keycode == 65433)
	{
		param->ang.x -= ROTANG;
		if (param->ang.x <= -PI * 2)
			param->ang.x = 0;
	}
	else if (keycode == 65436)
	{
		param->ang.z -= ROTANG;
		if (param->ang.z <= -PI * 2)
			param->ang.z = 0;
	}
	else if (keycode == 65430)
	{
		param->ang.y -= ROTANG;
		if (param->ang.y <= -PI * 2)
			param->ang.y = 0;
	}
}

void	handle_rotation1(int keycode, t_param *param)
{
	if (keycode == 65432)
	{
		param->ang.y += ROTANG;
		if (param->ang.y >= PI * 2)
			param->ang.y = 0;
	}
	else if (keycode == 65434)
	{
		param->ang.z += ROTANG;
		if (param->ang.z >= PI * 2)
			param->ang.z = 0;
	}
	else if (keycode == 65431)
	{
		param->ang.x += ROTANG;
		if (param->ang.x >= PI * 2)
			param->ang.x = 0;
	}
	else
		handle_rotation2(keycode, param);
	rotate(param);
	center_position(param->map, 0, 0);
}

void	shift_map(t_map ***map, int shifty, int shiftx)
{
	int	x;
	int	y;

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

void	change_position(t_map ***map, int keycode)
{
	t_max	max;

	max.max_x = map[0][0]->x;
	max.min_x = map[0][0]->x;
	max.max_y = map[0][0]->y;
	max.min_y = map[0][0]->y;
	get_max_values(map, &max, 0, 0);
	if (keycode == 65362 && max.min_y < HEIGHT)
		shift_map(map, (HEIGHT / 10), 0);
	else if (keycode == 65364 && max.max_y > 0)
		shift_map(map, -(HEIGHT / 10), 0);
	else if (keycode == 65363 && max.max_x > 0)
		shift_map(map, 0, -(WIDTH / 10));
	else if (keycode == 65361 && max.min_x < WIDTH)
		shift_map(map, 0, (WIDTH / 10));
	return ;
}

void	parallel_projection(t_param *param)
{
	int		x;
	int		y;
	int		space;
	t_map	***map;

	map = param->map;
	space = calcul_space(map);
	param->ang.x = 0;
	param->ang.y = 0;
	param->ang.z = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			map[y][x]->ox = x * space;
			map[y][x]->oy = y * space;
			x++;
		}
		y++;
	}
	param->proj = 1;
	rotate(param);
}
