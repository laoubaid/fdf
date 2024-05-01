/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 04:24:43 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/25 00:43:16 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	calcul_space(t_map ***map)
{
	int	max_x;
	int	max_y;
	int	tmp;
	int	space;

	get_max_col_lin(map, &max_x, &max_y);
	space = (HEIGHT / (max_y + 1)) * 0.6;
	tmp = (WIDTH / (max_x + 1)) * 0.6;
	if (space < tmp)
		space = tmp;
	if (!space)
		space = 1;
	return (space);
}

void	isometric_projection(t_param *param)
{
	int		x;
	int		y;
	int		space;
	t_map	***map;
	double	scale;

	map = param->map;
	space = calcul_space(map);
	y = 0;
	scale = get_scale(map);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			map[y][x]->x = x * space;
			map[y][x]->y = y * space;
			map[y][x]->z = map[y][x]->z * scale;
			x++;
		}
		y++;
	}
	rotate(param);
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
			map[y][x]->y += (HEIGHT / 2) - (halfy / 2) - fix_y;
			map[y][x]->x += (WIDTH / 2) - (halfx / 2) - fix_x;
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
			my_mlx_pixel_put(&img, map[y][x]->x, map[y][x]->y, \
map[y][x]->color.ucol);
			if (map[y][x + 1])
				drawline(&img, map[y][x], map[y][x + 1], map[y][x]->color);
			if (map[y + 1])
			{
				if (isvalid(map[y + 1], x))
					drawline(&img, map[y][x], map[y + 1][x], map[y][x]->color);
			}
			x++;
		}
		y++;
	}
}
