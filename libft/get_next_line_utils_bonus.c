/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:18:12 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/19 17:54:35 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_next_line(const char *str, int c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == (char)c)
		return ((char *)&str[i]);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin_next_line(char *s1, char *s2)
{
	char		*ml;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strjoin("", s2));
	if (!s2)
		return (ft_strjoin(s1, ""));
	ml = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!ml)
		return (NULL);
	ft_memcpy(ml, s1, ft_strlen(s1));
	ft_memcpy(ml + ft_strlen(s1), s2, ft_strlen(s2));
	ml[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (ml);
}

void	*ft_memcpy_next_line(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*ds;
	const char	*sr;

	i = 0;
	ds = (char *)dst;
	sr = (const char *)src;
	if (!src && !dst)
		return (NULL);
	if (ds == sr)
		return ((unsigned char *)src);
	while (i < n)
	{
		ds[i] = sr[i];
		i++;
	}
	return (dst);
}