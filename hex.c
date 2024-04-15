/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:12:50 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/09 00:02:59 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	sing;

	i = 0;
	res = 0;
	sing = 1;
	while (str[i] == 32 || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sing *= -1;
		i++;
	}
	while (str[i] < 58 && str[i] > 47)
	{
		res *= 10;
		res += str[i] - 48;
		i++;
	}
	return (res * sing);
}

t_color	get_color(char *str)
{
	int				i;
	unsigned int	color;
	t_color			rgba;

	i = 0;
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == ',' && str[i + 1] == '0' && str[i + 2] == 'x')
		color = hexa_dec(str + (i + 3));
	else if (str[i] == ',' && str[i + 1])
		color = ft_atoi(str + (i + 1));
	else
		color = (unsigned int)0x00FFFFFF;
	rgba.ucol = color;
	rgba.a = color >> 24 & 0xff;
	rgba.r = color >> 16 & 0xff;
	rgba.g = color >> 8 & 0xff;
	rgba.b = color & 0xff;
	return (rgba);
}

int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	else
		return (nb * ft_recursive_power(nb, power - 1));
}

int	hexa_dec(char *hex)
{
	long long	decimal;
	int			i;
	int			len;

	decimal = 0;
	i = 0;
	len = ft_strlen(hex);
	len--;
	while (hex[i] != '\0')
	{
		if (hex[i] >= '0' && hex[i] <= '9')
			decimal += (hex[i] - 48) * ft_recursive_power(16, len);
		else if (hex[i] >= 'a' && hex[i] <= 'f')
			decimal += (hex[i] - 97 + 10) * ft_recursive_power(16, len);
		else if (hex[i] >= 'A' && hex[i] <= 'F')
			decimal += (hex[i] - 65 + 10) * ft_recursive_power(16, len);
		len--;
		i++;
	}
	return (decimal);
}
