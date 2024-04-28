/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 18:22:46 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/25 00:47:59 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <mlx.h>

# define WIDTH 1080
# define HEIGHT 720
# define WT 1080
# define HT 720

# define ROTANG 0.174533
# define ISOANG 0.610865
# define PI 3.1415926

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
	long	x;
	long	y;
	long	z;
	t_color	color;
}	t_map;

typedef struct s_ang
{
	float	x;
	float	y;
	float	z;
}	t_ang;

typedef struct s_param
{
	t_map	***map;
	t_vars	*vars;
	t_data	*img;
	t_ang	ang;
}	t_param;

typedef struct s_max
{
	long	max_x;
	long	max_y;
	long	min_x;
	long	min_y;
}	t_max;

/* main page functions */
void	arg_error(int ac);
int		checkmap(t_map ***map);
int		main(int ac, char **av);

/* basic libft functions */
int		ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
int		hexa_dec(char *hex);
int		ft_atoi(const char *str);
char	*ft_strjoin(char *s1, char *s2);
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
void	display_img(t_param *param);
void	my_mlx_pixel_put(t_data *data, long x, long y, unsigned int color);
int		ftdestroy(t_param *param);
int		handle_key(int keycode, t_param *param);

/* get functions */
long	get_half(t_map ***map, int flag, long *fix_x, long *fix_y);
void	get_max_col_lin(t_map ***map, int *x, int *y);
void	get_max_values(t_map ***map, t_max *max, int y, int x);
double	get_scale(t_map ***map);
int		isvalid(t_map **map, int x);

/* draw functions */
void	isometric_projection(t_param *param);
void	center_position(t_map ***map, int x, int y);
void	drawline(t_data *img, t_map *p1, t_map *p2, t_color color);
void	draw_map(t_data img, t_map ***map);

/* draw line utils functions */
void	get_cst(int steps, t_color color1, t_color color2, t_cst *cst);
void	next_xy(t_diff *ds, int *x, int *y);
void	next_color(t_color *c, t_cst cst);
void	drawline_aide(t_diff *ds);
int		calcul_space(t_map ***map);

/* mlx hooks functions */
void	handle_hooks(t_map ***map, t_vars *vars, t_data *img);
void	free_map(t_map ***map);
int		ftexpose(t_param *param);

/* rotation functions */
void	rotate(t_param *param);
void	rotate_z(long *x, long *y, long *z, t_param *param);
void	rotate_y(long *x, long *y, long *z, t_param *param);
void	rotate_x(long *x, long *y, long *z, t_param *param);

#endif