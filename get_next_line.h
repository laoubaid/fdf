/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 22:03:37 by laoubaid          #+#    #+#             */
/*   Updated: 2024/03/24 01:06:22 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*ft_strjoin(char *s1, char *s2);
void	ft_bzero(void *p, int n);
int		ft_strlen(const char *str);
int		check(char *p);
int		cal_len(char *p);
char	*get_save(char *str, char *save);
char	*get_lin(char *str);
char	*get_next_line(int fd);
int		get_next(int fd, char **str, char **line);

#endif