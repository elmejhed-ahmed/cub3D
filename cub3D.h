/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:16:59 by ael-mejh          #+#    #+#             */
/*   Updated: 2024/09/17 14:04:24 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include <unistd.h>
#include <stdio.h>
#include "get_next_line.h"

typedef struct s_cub
{
    char *file;
    char *file2;    
    char *copy;    
    char *tmp;    
}   t_cub;

char	**ft_split(char const *s, char c);
#endif 