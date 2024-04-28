/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 00:38:58 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/22 18:53:17 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	reset_color(t_map ***map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			map[i][j]->color.ucol = map[i][j]->color.ocol;
			map[i][j]->color.a = map[i][j]->color.ucol >> 24 & 0xff;
			map[i][j]->color.r = map[i][j]->color.ucol >> 16 & 0xff;
			map[i][j]->color.g = map[i][j]->color.ucol >> 8 & 0xff;
			map[i][j]->color.b = map[i][j]->color.ucol & 0xff;
			j++;
		}
		i++;
	}
}

void	scale_z_and_reset(t_param *param, int keycode)
{
	if (keycode == 114)
	{
		param->scale = 1;
		param->zoom = 1;
		reset_color(param->map);
		isometric_projection(param);
		param->proj = 0;
	}
	else if (keycode == 45 || keycode == 65453)
		param->scale -= 0.5;
	else
		param->scale += 0.5;
	if (param->scale < 1)
		param->scale = 1;
	rotate(param);
	center_position(param->map, 0, 0);
}

void	zaverage(t_map ***map, long *min, long *max)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			map[i][j]->oz = map[i][j]->oz;
			if (map[i][j]->oz < *min)
				*min = map[i][j]->oz;
			if (map[i][j]->oz > *max)
				*max = map[i][j]->oz;
			j++;
		}
		i++;
	}
}

void	new_color(t_map ***map, long part)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j]->oz <= 0)
				map[i][j]->color.ucol = 0x0000FF;
			else if (map[i][j]->oz < part)
				map[i][j]->color.ucol = 0x00FF00;
			else if (map[i][j]->oz < part * 2)
				map[i][j]->color.ucol = 0xFF0000;
			else
				map[i][j]->color.ucol = 0xFFFFFF;
			map[i][j]->color.a = map[i][j]->color.ucol >> 24 & 0xff;
			map[i][j]->color.r = map[i][j]->color.ucol >> 16 & 0xff;
			map[i][j]->color.g = map[i][j]->color.ucol >> 8 & 0xff;
			map[i][j]->color.b = map[i][j]->color.ucol & 0xff;
			j++;
		}
		i++;
	}
}

void	add_color(t_param *param)
{
	long	min;
	long	max;
	long	part;
	t_map	***map;

	map = param->map;
	min = map[0][0]->oz;
	max = map[0][0]->oz;
	zaverage(map, &min, &max);
	part = (max - min) / 3;
	new_color(map, part);
}
