/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:19:55 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/23 20:25:24 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(long *x, long *y, long *z, t_param *param)
{
	long	new_x;
	long	new_y;

	(void)z;
	new_x = (*x * cos(param->ang.z) - *y * sin(param->ang.z));
	new_y = (*x * sin(param->ang.z) + *y * cos(param->ang.z));
	*x = new_x;
	*y = new_y;
}

void	rotate_x(long *x, long *y, long *z, t_param *param)
{
	long	new_y;
	long	new_z;

	(void)x;
	new_y = (*y * cos(param->ang.x) - *z * sin(param->ang.x));
	new_z = (*y * sin(param->ang.x) + *z * cos(param->ang.x));
	*y = new_y;
	*z = new_z;
}

void	rotate_y(long *x, long *y, long *z, t_param *param)
{
	long	new_x;
	long	new_z;

	(void)y;
	new_x = (*x * cos(param->ang.y) + *z * sin(param->ang.y));
	new_z = (-*x * sin(param->ang.y) + *z * cos(param->ang.y));
	*x = new_x;
	*z = new_z;
}

void	rotate(t_param *param)
{
	int		x;
	int		y;
	t_map	***map;

	y = 0;
	map = param->map;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			rotate_x(&map[y][x]->x, &map[y][x]->y, &map[y][x]->z, param);
			rotate_y(&map[y][x]->x, &map[y][x]->y, &map[y][x]->z, param);
			rotate_z(&map[y][x]->x, &map[y][x]->y, &map[y][x]->z, param);
			x++;
		}
		y++;
	}
}
