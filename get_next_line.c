/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 22:06:45 by laoubaid          #+#    #+#             */
/*   Updated: 2024/03/24 01:06:07 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check(char *p)
{
	int	i;

	i = 0;
	if (!p)
		return (1);
	while (p[i])
	{
		if (p[i] == '\n')
			return (0);
		i++;
	}
	if (i == BUFFER_SIZE)
		return (1);
	return (0);
}

char	*get_save(char *str, char *save)
{
	int	i;
	int	line_len;
	int	len_save;

	i = 0;
	line_len = cal_len(str);
	len_save = ft_strlen(str) - line_len;
	save = (char *)malloc(len_save + 1);
	while (i < len_save)
	{
		save[i] = str[line_len + i];
		i++;
	}
	save[len_save] = 0;
	if (ft_strlen(save) == 0)
	{
		free(save);
		save = NULL;
	}
	return (save);
}

char	*get_lin(char *str)
{
	int		count;
	int		i;
	char	*line;

	i = 0;
	count = cal_len(str);
	if (!count)
		return (NULL);
	line = malloc(count + 1);
	if (!line)
		return (NULL);
	while (i < count)
	{
		line[i] = str[i];
		i++;
	}
	line[count] = 0;
	return (line);
}

int	get_next(int fd, char **str, char **line)
{
	int			read_bytes;

	while (check(*line))
	{
		free(*line);
		*line = malloc(BUFFER_SIZE + 1);
		if (!(*line))
			return (0);
		read_bytes = read(fd, *line, BUFFER_SIZE);
		if (read_bytes == 0)
			break ;
		if (read_bytes == -1)
		{
			free(*line);
			return (0);
		}
		(*line)[read_bytes] = 0;
		*str = ft_strjoin(*str, *line);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*save;
	char		*line;

	if (fd < 0)
		return (NULL);
	str = NULL;
	line = NULL;
	str = ft_strjoin(str, save);
	free(save);
	save = NULL;
	if (!get_next(fd, &str, &line))
	{
		free(str);
		free(save);
		save = NULL;
		return (NULL);
	}
	free(line);
	line = NULL;
	line = get_lin(str);
	save = get_save(str, save);
	free(str);
	return (line);
}