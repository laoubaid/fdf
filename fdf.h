/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:22:46 by laoubaid          #+#    #+#             */
/*   Updated: 2024/03/26 01:42:46 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "get_next_line.h"
#include "./mlx_linux/mlx.h"
#include "./mlx_linux/mlx_int.h"


typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct  s_map
{
    int x;
    int y;
    int z;
    unsigned int color;
}               t_map;

/* basic libft functions */
int		ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
int		hexa_dec(char *hex);
int		ft_atoi(const char *str);
int		ft_recursive_power(int nb, int power);

/* Functions in favor of parsing the map */
int		get_color(char *str);
int		ft_strlen_line(char *str);
char	**split_line(char **str, int *nline);
t_map	***creat_map(char *str, int count);
t_map	**translate(char **str, int nline);
t_map	***get_map(char *input);


#endif