/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:06:13 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/13 17:06:30 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	ft_strlen_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	**split_line(char **str, int *nline)
{
	char	*ptr;
	char	*tmp;
	char	**res;
	int		i;

	i = 0;
	ptr = *str;
	*nline = ft_strlen_line(*str);
	tmp = malloc((*nline + 1) * sizeof(char));
	while (ptr[i] && ptr[i] != '\n')
	{
		tmp[i] = ptr[i];
		i++;
	}
	tmp[i] = 0;
	i++;
	*str = &ptr[i];
	res = ft_split(tmp, ' ');
	free(tmp);
	return (res);
}
