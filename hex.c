/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 02:12:50 by laoubaid          #+#    #+#             */
/*   Updated: 2024/03/23 04:46:56 by laoubaid         ###   ########.fr       */
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

int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	else
		return (nb * ft_recursive_power(nb, power - 1));
}

int    hexa_dec(char *hex)
{
    long long decimal;
    int i = 0, len;

    decimal = 0;

    len = strlen(hex);
    len--;

    while (hex[i] != '\0')
    {
        if(hex[i]>='0' && hex[i]<='9')
            decimal += (hex[i] - 48) * ft_recursive_power(16, len);
        else if(hex[i]>='a' && hex[i]<='f')
            decimal += (hex[i] - 97 + 10) * ft_recursive_power(16, len);
        else if(hex[i]>='A' && hex[i]<='F')
            decimal += (hex[i] - 65 + 10) * ft_recursive_power(16, len);
        len--;
        i++;
    }
    return (decimal);
}

