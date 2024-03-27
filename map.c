/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 04:04:28 by laoubaid          #+#    #+#             */
/*   Updated: 2024/03/26 03:38:47 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int    ft_strlen_line(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i] && str[i] != '\n')
        i++;
    return (i);
}
char    **split_line(char **str, int *nline)
{
    char *ptr;
    char *tmp;
    char **res;
    int i;
    
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
    return (res);
}

int get_color(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != ',')
        i++;
    if (str[i] == ',' && str[i + 1] == '0' && str[i + 2] == 'x')
        return (hexa_dec(str + (i + 3)));
    else
        return (-1);
    return (ft_atoi(str + (i + 1)));
}

t_map   **translate(char **str, int nline)
{
    int i;
    t_map   **tmp;

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

t_map ***creat_map(char *str, int count)
{
    int     i;
    int     nline;
    char    *tmp;
    char    **line;
    t_map    ***map;

    i = 0;
    tmp = str;
    map = malloc((count + 1) * sizeof(t_map **));
    while (i < count)
    {
        line = split_line(&tmp, &nline);
        map[i]= translate(line, nline);
        i++;
    }
    map[i] = NULL;
    return (map);
}

t_map ***get_map(char *input)
{
    int fd;
    int     count;
    char *str;
    char *tmp;
    t_map ***map;

    fd = open(input, O_RDONLY);
    str = NULL;
    tmp = NULL;
    count = 0;
    while (1)
    {
        free(tmp);
        tmp = get_next_line(fd);
        if (!tmp)
            break ;
        count++;
        str = ft_strjoin(str, tmp);
    }
    close(fd);
    // exit(0);
    map = creat_map(str, count);
    return (map);
}