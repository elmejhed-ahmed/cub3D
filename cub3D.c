/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:42:03 by ael-mejh          #+#    #+#             */
/*   Updated: 2024/09/16 15:40:06 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int check_extention(char *str)
{
    int i;
    
    i = 0;
    while(str[i])
        i++;
    if (str[i - 1] != 'b' || str[i - 2] != 'u'
        || str[i - 3] != 'c' || str[i - 4] != '.')
        return (1);
    return 0;
}
int main(int ac, char **av)
{
    if (ac != 2)
        return (write(0, "error\ninvalid argument\n", 23), 1);
    if (check_extention(av[1]))
        return (write(0, "error\ninvalid extention\n", 24), 1);
   
    return 0;
}