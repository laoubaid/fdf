/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 05:14:21 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/15 13:51:29 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	steps = count_steps(p1, p2, &ds);
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

void	waytodraw(t_data *img, t_map *p1, t_map *p2)
{
	if (p2->color.ucol >= p1->color.ucol)
		drawline(img, p1, p2, p1->color);
	else
		drawline(img, p2, p1, p2->color);
}
