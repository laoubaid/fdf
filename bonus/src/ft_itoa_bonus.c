/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:19:30 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/22 16:54:23 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*join;

	i = 0;
	if (!s1 && !s2)
		return (0);
	join = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (0);
	if (s1)
	{
		while (s1[i])
		{
			join[i] = s1[i];
			i++;
		}
		free(s1);
	}
	if (s2)
	{
		while (*s2)
			join[i++] = *s2++;
	}
	join[i] = 0;
	return (join);
}

static int	cal_len(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size;
	long	ln;

	ln = (long) n;
	size = cal_len(ln);
	ptr = (char *)malloc(size + 1);
	if (!ptr)
		return (NULL);
	if (ln < 0)
	{
		ln *= -1;
		ptr[0] = '-';
	}
	ptr[size--] = '\0';
	if (ln == 0)
		ptr[0] = '0';
	while (ln > 0)
	{
		ptr[size--] = (ln % 10) + 48;
		ln /= 10;
	}
	return (ptr);
}
