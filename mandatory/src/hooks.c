/* ************************************************************************** */
/*                                                        */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 03:35:54 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/22 16:55:02 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_key(int keycode, t_param *param)
{
	if (keycode == 65307)
		ftdestroy(param);
	return (0);
}

void	handle_hooks(t_map ***map, t_vars *vars, t_data *img)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	param->map = map;
	param->vars = vars;
	param->img = img;
	param->ang.x = ISOANG;
	param->ang.y = -ISOANG;
	param->ang.z = ISOANG;
	isometric_projection(param);
	mlx_hook(param->vars->win, 17, 1L << 2, ftdestroy, param);
	mlx_expose_hook(param->vars->win, ftexpose, param);
	mlx_key_hook(param->vars->win, handle_key, param);
}
