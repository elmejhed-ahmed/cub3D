/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:07:54 by ael-mejh          #+#    #+#             */
/*   Updated: 2024/09/19 18:08:36 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
char	*ft_strchr_get_next_line(const char *str, int c);
size_t	ft_strlen_get_next_line(const char *str);
char	*ft_strjoin_get_next_line(char *s1, char *s2);
void	*ft_memcpy_get_next_line(void *dst, const void *src, size_t n);
#endif
