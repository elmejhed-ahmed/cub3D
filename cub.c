/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:23:04 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/22 17:32:24 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int pars_color_floor_ceiling(char *str, t_texture *texture, int j)
{
    int i;
    int k;
    char **new;
    char *trim;

    i = j + 1;
    printf("%s", &str[i]);
    trim = ft_strtrim(&str[i],"\n");
    i = 0;
    if (trim[i] == ',')
        return (printf("Errsor: In111111 \n"), 1);
    // while (str[k] != '\0' &&  str[k] != '\n')
    // {
    //     if (str[k] == ' ')
    //     {
    //         k++;
    //         continue;
    //     }
    //     if ((str[k] == ',' && str[k + 1] == ','))
    //         return (printf("Error: Invalid character '%c' at position %d\n", str[k], k), 1);
    //     if (str[k] == ',' && (str[k + 1] == '\n' || str[k + 1] == '\0'))
    //         return (printf("Errsor: In \n"), 1);
    //     k++;
    // }
    new = ft_split(&trim[i], ',');
    k = 0;
    while (new[k])
    {
        int o = 0;
        trim = ft_strtrim(new[k]," ");
        printf("trim ====>> %s\n", trim);
        while (trim[o] && trim[o] != '\n')
        {
            if (trim[o] == ' ')
                return (printf("error\n\n\n"), 1);
            o++;
        }
        free(trim);
        printf("[%s] |\n", new[k]);
        k++;
    }
    
    // k = i;
    // while (str[i] != '\0' &&  str[i] != '\n')
    // {
    //     if (!ft_isdigit(str[i]) && str[i] != ',' && str[i] != ' ') {
    //         printf("Error: Invalid character '%c' at position %d\n", str[i], i);
    //         return 1;
    //     }
    //     i++;
    // }
    // int p = 0;
    // while (str[k] != '\0' &&  str[k] != '\n')
    // {
    //     int nu = 0;
    //     while (str[k + nu] != '\0' && str[k + nu] != ',' &&  str[k + nu] != '\n')
    //     {
    //         if (str[k + nu] == ',')
    //             p++;
    //         nu++;
    //     }
    //     if (nu > 3)
    //         return (printf("len len len len number \n"), 1);
    //     k += nu;
    //     if (str[k] == ',')
    //         k++;
    // }
    // printf("---------------->>    num ==== {%d}\n", p);
    if (str[j] == 'F')
    {
        texture->F[0] = 225;
    }
    return 0;
}

int go_to_check(char *str, t_texture *texture, int i)
{
    while (str[i] == ' ')
        i++;
    int j = i;
    if ((Fl || Ce ) && (str[i + 1] == ' '))
    {
        if (pars_color_floor_ceiling(str, texture, i))
            return 1;
    }
    else if (((N || S || W || E || Fl || Ce )) && (str[i + 2] == ' '))
    {
        i += 2;
        while(str[i] == ' ')
            i++;
        if (str[j] == 'N' && str[j + 1] == 'O')
            texture->NO = ft_strdup1(&str[i]);
        if (str[j] == 'S' && str[j + 1] == 'O')
            texture->SO = ft_strdup1(&str[i]);
        if (str[j] == 'W' && str[j + 1] == 'E')
            texture->WE = ft_strdup1(&str[i]);
        if (str[j] == 'E' && str[j + 1] == 'A')
            texture->EA = ft_strdup1(&str[i]);
    }
    else 
        return (printf("error\nerror in direction -> %s", str), 1);
    return 0;
}

void init_variables_direction(t_texture *texture)
{
    texture->EA = NULL;
    texture->NO = NULL;
    texture->SO = NULL;
    texture->WE = NULL;
    // texture->F = NULL;
    // texture->C = NULL;
}
int read_file(char **av, t_cub *cub, t_texture *texture)
{
    int fd;
    
    fd = open(av[1], O_RDWR);
    if (fd < 0)
        return (1);
    cub->file = get_next_line(fd);
    if (!(cub->file))
        return (write(2, "error\n", 6) ,1);
    init_variables_direction(texture);
    while(cub->file != NULL)
    {   
        int i = 0;
        while(cub->file[i])
            i++;
        if ((i > 0) && cub->file[i - 1] != '\n')
            return (write(2, "error\nerror new line\n", 21) ,1);
        if (i == 1 && cub->file[i - 1] == '\n')
        {
            free(cub->file);
            cub->file = get_next_line(fd);
            continue;
        }
        if (go_to_check(cub->file, texture, 0))
                return (1);
        free(cub->file);
        cub->file = get_next_line(fd);
    }
    close(fd);
    
    return (0);
}

int main(int ac, char **av)
{
    t_cub cub;
    t_texture texture;
    if (ac != 2)
        return (write(0, "error\ninvalid argument\n", 23), 1);
    if (check_extention(av[1]))
        return (write(0, "error\ninvalid extention\n", 24), 1);
    if (read_file(av, &cub, &texture))
        return (1);
    printf("NO ---> [[[%s]]]\n", texture.NO);
    printf("SO ---> [[[%s]]]\n", texture.SO);
    printf("WE ---> [[[%s]]]\n", texture.WE);
    printf("EA ---> [[[%s]]]\n", texture.EA);
    // printf("F ---> %s\n", texture.F);
    // printf("C ---> %s\n", texture.C);
    return 0;
}