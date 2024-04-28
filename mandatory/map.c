/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 04:04:28 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/25 01:08:24 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	**translate(char **str, int nline)
{
	int		i;
	t_map	**tmp;

	tmp = malloc(sizeof(t_map *) * (nline + 1));
	i = 0;
	while (str[i])
	{
		tmp[i] = malloc(sizeof(t_map));
		tmp[i]->z = ft_atoi(str[i]);
		tmp[i]->color = get_color(str[i]);
		i++;
	}
	tmp[i] = NULL;
	return (tmp);
}

t_map	***creat_map(char *str, int count)
{
	int		i;
	int		nline;
	char	*tmp;
	char	**line;
	t_map	***map;

	i = 0;
	tmp = str;
	map = malloc((count + 1) * sizeof(t_map **));
	while (i < count)
	{
		line = split_line(&tmp, &nline);
		map[i] = translate(line, nline);
		ft_free(line);
		i++;
	}
	map[i] = NULL;
	free(str);
	return (map);
}

int	cal_lines(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[i])
		count++;
	while (str[i])
	{
		if (str[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

char	*join_map(int fd, int size, char *str)
{
	char	tmp[1024];
	int		read_size;
	int		i;
	int		j;

	if (fd < 0)
		arg_error(1);
	str = malloc(sizeof(char) * (size));
	if (!str)
		return (NULL);
	j = 0;
	while (1)
	{
		read_size = read(fd, tmp, 1024);
		if (read_size <= 0)
			break ;
		tmp[read_size] = 0;
		i = 0;
		while (tmp[i])
			str[j++] = tmp[i++];
	}
	i = 0;
	while (str[j - i] == '\n' || i == 0)
		str[j - i++] = 0;
	return (close(fd), str);
}

t_map	***get_map(char *input)
{
	int		fd;
	char	*str;
	char	tmp[1024];
	int		size;
	int		read_size;

	size = 0;
	read_size = 0;
	fd = open(input, O_RDONLY);
	if (fd < 0)
		arg_error(1);
	while (1)
	{
		read_size = read(fd, tmp, 1024);
		if (read_size <= 0)
			break ;
		size += read_size;
	}
	if (size == 0)
		arg_error(-2);
	close(fd);
	str = join_map(open(input, O_RDONLY), size + 1, NULL);
	return (creat_map(str, cal_lines(str)));
}
