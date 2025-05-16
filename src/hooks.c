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

void	print_angles(t_param *param)
{
	char	*str;
	char	*strx;
	char	*stry;
	char	*strz;

	strx = ft_itoa((int)(param->ang.x * (180 / PI)));
	stry = ft_itoa((int)(param->ang.y * (180 / PI)));
	strz = ft_itoa((int)(param->ang.z * (180 / PI)));
	str = malloc(1);
	str[0] = 0;
	str = ft_strjoin(str, "Angles: X [");
	str = ft_strjoin(str, strx);
	str = ft_strjoin(str, "] Y [");
	str = ft_strjoin(str, stry);
	str = ft_strjoin(str, "] Z [");
	str = ft_strjoin(str, strz);
	str = ft_strjoin(str, "]");
	mlx_string_put(param->vars->mlx, param->vars->win, 10, 340, -1, str);
	free(str);
	free(strx);
	free(stry);
	free(strz);
}

void	handle_text(t_param *param)
{
	void	*mlx;
	void	*win;

	mlx = param->vars->mlx;
	win = param->vars->win;
	mlx_string_put(mlx, win, 10, 20, -1, "//// USAGE INFO ////");
	mlx_string_put(mlx, win, 10, 40, -1, "> Use Mouse scroll button to zoom");
	mlx_string_put(mlx, win, 10, 60, -1, "> Use arrow keys to move the map");
	mlx_string_put(mlx, win, 10, 80, -1, "> Use + & - keys to scale z");
	mlx_string_put(mlx, win, 10, 100, -1, "> Use numbers to rotate the map");
	mlx_string_put(mlx, win, 10, 120, -1, "  X: 4, 6 | Y: 8, 2 | Z: 1, 9");
	mlx_string_put(mlx, win, 10, 160, -1, "//// CONTROL INFO ////");
	mlx_string_put(mlx, win, 10, 180, -1, "> Press 'C' to center the map");
	mlx_string_put(mlx, win, 10, 200, -1, "> Press 'M' to change projection");
	mlx_string_put(mlx, win, 10, 220, -1, "> Press 'Q' to set basic colors");
	mlx_string_put(mlx, win, 10, 240, -1, "> Press 'R' to reset everything");
	mlx_string_put(mlx, win, 10, 260, -1, "> Press ESC to Exit the program");
	mlx_string_put(mlx, win, 10, 300, -1, "//// PROJECTION INFO ////");
	if (param->proj)
		mlx_string_put(mlx, win, 10, 320, -1, "current Proj: Parallel Prj");
	else
		mlx_string_put(mlx, win, 10, 320, -1, "current Proj: Isometric Prj");
	print_angles(param);
}

int	handle_mouse(int button, int x, int y, t_param *param)
{
	(void)x;
	(void)y;
	if (button == 4 && param->zoom < 5)
	{
		param->zoom += 0.1;
		rotate(param);
	}
	else if (button == 5 && param->zoom > 0.2)
	{
		param->zoom -= 0.1;
		rotate(param);
	}
	else
	{
		return (0);
	}
	center_position(param->map, 0, 0);
	display_img(param);
	return (0);
}

int	handle_key(int keycode, t_param *param)
{
	if (keycode == 65307)
		ftdestroy(param);
	else if (keycode >= 65361 && keycode <= 65364)
		change_position(param->map, keycode);
	else if (keycode == 113)
		add_color(param);
	else if (keycode == 65451 || keycode == 65453)
		scale_z_and_reset(param, keycode);
	else if (keycode == 61 || keycode == 45 || keycode == 114)
		scale_z_and_reset(param, keycode);
	else if (keycode >= 65430 && keycode <= 65436 && keycode != 65435)
		handle_rotation1(keycode, param);
	else if (keycode == 109 || keycode == 99)
	{
		if (param->proj && keycode == 109)
			isometric_projection(param);
		else if (keycode == 109)
			parallel_projection(param);
		center_position(param->map, 0, 0);
	}
	display_img(param);
	return (0);
}

void	handle_hooks(t_map ***map, t_vars *vars, t_data *img)
{
	t_param	*param;

	param = malloc(sizeof(t_param));
	param->map = map;
	param->vars = vars;
	param->img = img;
	param->proj = 0;
	param->zoom = 1;
	param->ang.x = 0;
	param->ang.y = 0;
	param->ang.z = 0;
	param->scale = 1;
	mlx_hook(param->vars->win, 17, 1L << 2, ftdestroy, param);
	mlx_expose_hook(param->vars->win, ftexpose, param);
	mlx_key_hook(param->vars->win, handle_key, param);
	mlx_mouse_hook(param->vars->win, handle_mouse, param);
}
