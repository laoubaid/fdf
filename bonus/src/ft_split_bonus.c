/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laoubaid <laoubaid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:58:59 by laoubaid          #+#    #+#             */
/*   Updated: 2024/04/12 19:07:53 by laoubaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	count_words(char const *s, char c)
{
	int	count;
	int	i;
	int	len;

	i = 1;
	count = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if ((s[i] == c || s[i] == '\0') && s[i - 1] != c)
			count++;
		i++;
	}
	return (count);
}

static char	*count_chars(char const *s, char c, int *nbc, int *ns)
{
	int		i;
	char	*ptr;

	i = 0;
	*ns = 0;
	*nbc = 0;
	ptr = (char *)s;
	while (ptr[i] == c)
		i++;
	while (!(ptr[i] == c || ptr[i] == '\0'))
	{
		(*nbc)++;
		i++;
	}
	*ns = *nbc;
	while (ptr[i] == c)
	{
		i++;
		(*ns)++;
	}
	return (&ptr[i]);
}

char	**ft_free(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

static char	**ft_fill(char **ptr, const char *s, char c, int nw)
{
	int	i;
	int	nc;
	int	j;
	int	ns;

	nc = 0;
	ns = 0;
	i = 0;
	while (i < nw)
	{
		s = count_chars(s, c, &nc, &ns);
		ptr[i] = (char *)malloc(nc + 1);
		if (!ptr[i])
			return (ft_free(ptr));
		j = 0;
		while (*(s - ns) != c && *(s - ns))
		{
			ptr[i][j] = *(s - ns);
			ns--;
			j++;
		}
		ptr[i][j] = '\0';
		i++;
	}
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		nword;

	if (!s)
		return (0);
	nword = count_words(s, c);
	ptr = (char **)malloc((nword + 1) * sizeof(char *));
	if (!ptr)
		return (NULL);
	ptr = ft_fill(ptr, s, c, nword);
	if (ptr)
		ptr[nword] = (NULL);
	return (ptr);
}
