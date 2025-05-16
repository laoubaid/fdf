/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 05:14:21 by laoubaid          #+#    #+#             */
/*   Updated: 2025/05/16 21:10:21 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

long	ft_sqrt(long nb)
{
	long	i;

	i = 1;
	while (i * i <= nb && i < 46500)
	{
		if (i * i == nb)
			return (i);
		i++;
	}
	return (i);
}

void	drawline(t_data *img, t_map *p1, t_map *p2, t_color color)
{
	int				x;
	int				y;
	unsigned int	steps;
	t_diff			ds;
	t_cst			cst;

	ds.dx = p2->x - p1->x;
	ds.dy = p2->y - p1->y;
	drawline_aide(&ds);
	steps = ft_sqrt(ds.dx * ds.dx + ds.dy * ds.dy);
	get_cst(steps, p1->color, p2->color, &cst);
	x = p1->x;
	y = p1->y;
	while (x != p2->x || y != p2->y)
	{
		my_mlx_pixel_put(img, x, y, color.ucol);
		next_xy(&ds, &x, &y);
		next_color(&color, cst);
	}
	my_mlx_pixel_put(img, x, y, color.ucol);
}
