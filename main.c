/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:05:01 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/15 23:58:43 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int	main(int ac, char **av)
{
	int		tmp[2];
	t_vars	vars;
	t_data	img;
	t_map	***map;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "fdf");
	img.img = mlx_new_image(vars.mlx, IMGW, IMGH);
	img.addr = mlx_get_data_addr(img.img, tmp, tmp + 1, &img.endian);
	img.line_length = tmp[1];
	img.bits_per_pixel = tmp[0];
	map = get_map(av[1]);
	isometric_transform(map, 1);
	center_position(map, 0, 0);
	handle_hooks(map, &vars, &img);
	mlx_loop(vars.mlx);
	return (0);
}
