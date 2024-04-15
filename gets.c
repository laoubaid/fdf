/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:37:07 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/15 18:02:52 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_max_t(t_map ***map, t_max *max, int y, int x)
{
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x]->x > max->max_x)
				max->max_x = map[y][x]->x;
			if (map[y][x]->x < max->min_x)
				max->min_x = map[y][x]->x;
			if (map[y][x]->y > max->max_y)
				max->max_y = map[y][x]->y;
			if (map[y][x]->y < max->min_y)
				max->min_y = map[y][x]->y;
			x++;
		}
		y++;
	}
}

long	get_half(t_map ***map, int flag, long *fx, long *fy)
{
	t_max	max;

	max.max_x = map[0][0]->x;
	max.min_x = map[0][0]->x;
	max.max_y = map[0][0]->y;
	max.min_y = map[0][0]->y;
	get_max_t(map, &max, 0, 0);
	*fx = max.min_x;
	*fy = max.min_y;
	if (flag)
		return (max.max_x - max.min_x);
	return (max.max_y - max.min_y);
}

void	get_maxt(t_map ***map, int *x, int *y)
{
	int	i;
	int	j;

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
}

double	get_scale(t_map ***map)
{
	int		i;
	int		j;
	int		max;
	int		min;

	i = 0;
	max = 0;
	min = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j]->z > max)
				max = map[i][j]->z;
			if (map[i][j]->z < min)
				min = map[i][j]->z;
			j++;
		}
		i++;
	}
	if (max - min == 0)
		return (1);
	else
		return ((HEIGHT / (max - min)) * 0.4);
}

int	isvalid(t_map **map, int x)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	if (i > x)
		return (1);
	return (0);
}
