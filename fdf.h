/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:22:46 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/16 00:10:21 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <limits.h>
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"

# define WIDTH 1500
# define HEIGHT 1000
# define IMGW 1200
# define IMGH 1000
# define TXTW 300
# define TXTH 1000

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_color
{
	float			r;
	float			g;
	float			b;
	float			a;
	unsigned int	ucol;
}	t_color;

typedef struct s_diff
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_diff;

typedef struct s_cst
{
	float	cstr;
	float	cstg;
	float	cstb;
	float	csta;
}	t_cst;

typedef struct s_map
{
	long		x;
	long		y;
	long		z;
	long		ox;
	long		oy;
	long		oz;
	t_color	color;
}	t_map;

typedef struct s_param
{
	t_map	***map;
	t_vars	*vars;
	t_data	*img;
	int		proj;
	double	zoom;
}	t_param;

typedef struct s_max
{
	long	max_x;
	long	max_y;
	long	min_x;
	long	min_y;
}	t_max;

/* basic libft functions */
int		ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
int		hexa_dec(char *hex);
int		ft_atoi(const char *str);
int		ft_recursive_power(int nb, int power);

/* Functions in favor of parsing the map */
t_color	get_color(char *str);
int		ft_strlen_line(char *str);
char	**split_line(char **str, int *nline);
t_map	***creat_map(char *str, int count);
t_map	**translate(char **str, int nline);
t_map	***get_map(char *input);
char	**ft_free(char **ptr);

/* mlx utils functions */
void	my_mlx_pixel_put(t_data *data, long x, long y, unsigned int color);
void	fill_img(t_data *data, long x, long y, unsigned int color);
int		ftdestroy(t_param *param);
int		handle_key(int keycode, t_param *param);

/* get functions */
long	get_half(t_map ***map, int flag, long *fix_x, long *fix_y);
void	get_maxt(t_map ***map, int *x, int *y);
void	get_max_t(t_map ***map, t_max *max, int y, int x);
double	get_scale(t_map ***map);
int		isvalid(t_map **map, int x);

/* draw functions */
void	isometric_transform(t_map ***map, float zoom);
void	center_position(t_map ***map, int x, int y);
void	drawline(t_data *img, t_map *p1, t_map *p2, t_color color);
void	waytodraw(t_data *img, t_map *p1, t_map *p2);
void	draw_map(t_data img, t_map ***map);

/* draw line utils functions */
int		count_steps(t_map *p1, t_map *p2, t_diff *ds);
void	get_cst(int steps, t_color color1, t_color color2, t_cst *cst);
void	next_xy(t_diff *ds, int *x, int *y);
void	next_color(t_color *c, t_cst cst);
void	drawline_aide(t_diff *ds);
int		calcul_space(t_map ***map);

/* mlx hooks functions */
void	handle_hooks(t_map ***map, t_vars *vars, t_data *img);
int		handle_mouse(int button, int x, int y, t_param *param);
void	handle_text(void *mlx, void *win, t_param *param);
void	free_map(t_map ***map);
int		ftexpose(t_param *param);

/* additional functions for bonus part */
void	shift_map(t_map ***map, int shifty, int shiftx);
void	ftzoom(t_param *param, int sign);
void	change_position(t_map ***map, int keycode);
void	parallel_projection(t_map ***map, float zoom);

#endif