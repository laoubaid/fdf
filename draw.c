/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 04:24:43 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/16 00:20:48 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	calcul_space(t_map ***map)
{
	int	max_x;
	int	max_y;
	int	tmp;
	int	space;

	get_maxt(map, &max_x, &max_y);
	space = (HEIGHT / (max_y + 1)) * 0.4;
	tmp = (WIDTH / (max_x + 1)) * 0.4;
	if (space < tmp)
		space = tmp;
	return (space);
}

void	isometric_transform(t_map ***map, float zoom)
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
			map[y][x]->ox = (x - y) * cos(0.52359877) * space;
			map[y][x]->oy = (x + y) * sin(0.52359877) * space;
			map[y][x]->x = map[y][x]->ox * zoom;
			map[y][x]->y = map[y][x]->oy * zoom;
			map[y][x]->z = map[y][x]->oz * zoom;
			map[y][x]->y -= map[y][x]->z;
			x++;
		}
		y++;
	}
}

void	center_position(t_map ***map, int x, int y)
{
	long	fix_x;
	long	fix_y;
	long	halfx;
	long	halfy;

	halfx = get_half(map, 1, &fix_x, &fix_y);
	halfy = get_half(map, 0, &fix_x, &fix_y);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			map[y][x]->y += (IMGH / 2) - (halfy / 2) - fix_y;
			map[y][x]->x += (IMGW / 2) - (halfx / 2) - fix_x;
			x++;
		}
		y++;
	}
}

void	draw_map(t_data img, t_map ***map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x + 1])
				waytodraw(&img, map[y][x], map[y][x + 1]);
			if (map[y + 1])
				if (isvalid(map[y + 1], x))
					waytodraw(&img, map[y][x], map[y + 1][x]);
			x++;
		}
		y++;
	}
}
