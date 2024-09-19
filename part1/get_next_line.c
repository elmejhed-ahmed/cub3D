/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:16:55 by ael-mejh          #+#    #+#             */
/*   Updated: 2023/12/28 12:59:22 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*checknextlinge(char *checkstr)
{
	int		i;
	char	*rslt;

	i = 0;
	while (checkstr[i] != '\n' && checkstr[i] != '\0')
		i++;
	if (checkstr[i] == '\n')
		i++;
	rslt = malloc(sizeof(char) * (ft_strlen(checkstr) - i) + 1);
	if (!rslt)
	{
		free(checkstr);
		return (checkstr = NULL, NULL);
	}
	ft_memcpy(rslt, checkstr + i, ft_strlen(checkstr) - (i));
	rslt[ft_strlen(checkstr) - i] = '\0';
	free(checkstr);
	checkstr = NULL;
	return (rslt);
}

static char	*checkline(char *check)
{
	int		i;
	char	*str;

	i = 0;
	while (check[i] != '\n' && check[i])
		i++;
	if (check[i] == '\n')
		i++;
	str = malloc(sizeof(char) * i + 1);
	if (str == NULL)
		return (free(check), check = NULL, NULL);
	ft_memcpy(str, check, i);
	str[i] = '\0';
	return (str);
}

static char	*get_str(char *str, int fd, char *buf)
{
	char	*joinstr;
	int		openfile;

	openfile = 1;
	while (!ft_strchr(str, '\n') && openfile)
	{
		openfile = read(fd, buf, BUFFER_SIZE);
		if (openfile < 0)
			return (free(buf), free(str), buf = NULL, str = NULL, NULL);
		buf[openfile] = '\0';
		joinstr = str;
		str = ft_strjoin(str, buf);
		if (!str)
		{
			free(joinstr);
			joinstr = NULL;
			return (free(buf), buf = NULL, NULL);
		}
		free(joinstr);
		joinstr = NULL;
	}
	free(buf);
	if (str && str[0] == '\0')
		return (free(str), str = NULL, NULL);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*printline;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	buff = malloc((size_t)BUFFER_SIZE + 1);
	if (!buff)
		return (free(str), str = NULL, NULL);
	str = get_str(str, fd, buff);
	if (str == NULL)
		return (NULL);
	printline = checkline(str);
	if (!printline)
		return (str = NULL, NULL);
	str = checknextlinge(str);
	return (printline);
}
