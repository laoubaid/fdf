/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 05:12:07 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/25 04:20:22 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	get_cst(int steps, t_color color1, t_color color2, t_cst *cst)
{
	if (steps)
	{
		cst->csta = ((float )(color2.a) - (float )color1.a) / steps;
		cst->cstr = ((float )(color2.r) - (float )color1.r) / steps;
		cst->cstg = ((float )(color2.g) - (float )color1.g) / steps;
		cst->cstb = ((float )(color2.b) - (float )color1.b) / steps;
	}
	else
	{
		cst->csta = 0;
		cst->cstr = 0;
		cst->cstg = 0;
		cst->cstb = 0;
	}
}

void	next_xy(t_diff *ds, int *x, int *y)
{
	ds->e2 = 2 * ds->err;
	if (ds->e2 > -ds->dy)
	{
		ds->err -= ds->dy;
		*x += ds->sx;
	}
	if (ds->e2 < ds->dx)
	{
		ds->err += ds->dx;
		*y += ds->sy;
	}
}

void	next_color(t_color *c, t_cst cst)
{
	if (!cst.csta && !cst.cstr && !cst.cstg && !cst.cstb)
		return ;
	c->a += cst.csta;
	c->r += cst.cstr;
	c->g += cst.cstg;
	c->b += cst.cstb;
	c->ucol = (unsigned int)c->a * 256 * 256 * 256;
	c->ucol += (unsigned int)c->r * 256 * 256;
	c->ucol += (unsigned int)c->g * 256;
	c->ucol += c->b;
}

void	drawline_aide(t_diff *ds)
{
	if (ds->dx > 0)
		ds->sx = 1;
	else if (ds->dx < 0)
		ds->sx = -1;
	else
		ds->sx = 0;
	if (ds->dy > 0)
		ds->sy = 1;
	else if (ds->dy < 0)
		ds->sy = -1;
	else
		ds->sy = 0;
	ds->dx = abs(ds->dx);
	ds->dy = abs(ds->dy);
	ds->err = ds->dx - ds->dy;
}
