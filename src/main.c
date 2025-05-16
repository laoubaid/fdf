/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:05:01 by laoubaid          #+#    #+#             */
/*   Updated: 2025/05/17 00:06:28 by laoubaid         ###   ########.fr       */
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

void	arg_error(int ac)
{
	if (ac < 0)
		write(2, "Error: Invalid argument map is invalid\n", 39);
	else if (ac != 2)
	{
		write(2, "Error: Invalid usage of program\n", 33);
		write(2, "Usage: ./fdf <filename>\n", 24);
	}
	else
		write(2, "Error: Invalid argument coudn't open file\n", 42);
	exit(1);
}

int	checkmap(t_map ***map)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = -1;
	if (!map)
		return (1);
	if (!map[0])
		return (1);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j == 0)
			return (1);
		if (len < 0)
			len = j;
		else if (len != j)
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	int		tmp[2];
	t_vars	vars;
	t_data	img;
	t_map	***map;

	if (ac != 2 || open(av[1], O_RDONLY) < 0)
		arg_error(ac);
	map = get_map(av[1]);
	if (checkmap(map))
	{
		free_map(map);
		arg_error(-1);
	}
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "fdf");
	img.img = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, tmp, tmp + 1, &img.endian);
	img.line_length = tmp[1];
	img.bits_per_pixel = tmp[0];
	handle_hooks(map, &vars, &img);
	mlx_loop(vars.mlx);
	return (0);
}
