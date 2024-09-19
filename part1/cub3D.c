/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:42:03 by ael-mejh          #+#    #+#             */
/*   Updated: 2024/09/17 14:09:36 by ael-mejh         ###   ########.fr       */
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

int read_file(char **av, t_cub *cub)
{
    int fd;
    cub->copy = NULL;
    char **file_split;
    fd = open(av[1], O_RDWR);
    if (fd < 0)
        return (1);
    cub->file = get_next_line(fd);
    if (!(cub->file))
        return (write(2, "error\n", 6) ,1);
    while(cub->file != NULL)
    {   
        cub->tmp = cub->copy;
        cub->copy = ft_strjoin(cub->copy, cub->file);
        free(cub->file);
        free(cub->tmp);
        
        cub->file = get_next_line(fd);
    }
    close(fd);
    file_split = ft_split(cub->copy, '\n');
    return (0);
}

int main(int ac, char **av)
{
    t_cub cub;

    if (ac != 2)
        return (write(0, "error\ninvalid argument\n", 23), 1);
    if (check_extention(av[1]))
        return (write(0, "error\ninvalid extention\n", 24), 1);
    if (read_file(av, &cub))
        return (write(0, "error\ninvalid extention\n", 24), 1);
    
    return 0;
}