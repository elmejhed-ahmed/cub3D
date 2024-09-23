/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:23:04 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/23 19:30:31 by ael-mejh         ###   ########.fr       */
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
	trim = ft_strtrim(&str[i],"\n");
	trim = ft_strtrim(trim," ");

	i = 0;
	while (trim[i] != '\0')
	{
		if (!ft_isdigit(trim[i]) && trim[i] != ',' && trim[i] != ' ') {
			printf("Error\nadd just numbers separetly with `,` in F and C\n");
			return 1;
		}
		i++;
	}
	i = 0;
	if (trim[i] == ',')
		return (printf("Error\nError:`,` in the first \n"), 1);
	int sq = 0;
	while (trim[i] != '\0')
	{
		if (trim[i] == ',')
			sq++;
		if (trim[i] == ' ')
		{
			i++;
			continue;
		}
		if ((trim[i] == ',' && trim[i + 1] == ','))
			return (printf("Error: Invalid character '%c' at position %d\n", trim[i],i), 1);
		if (trim[i] == ',' && (trim[i + 1] == '\n' || trim[i + 1] == '\0'))
			return (printf("Errror\nYou have a `,` in the last in F or C\n"), 1);
		i++;
	}
	if (sq > 2)
		return (printf("Error\nthe number of parametr in F or C is not correct\n"), 1);
	new = ft_split(trim, ',');
	k = 0;
	while (new[k])
	{
		int o = 0;
		int count = 0;
		trim = ft_strtrim(new[k]," ");
		// printf("trim ====>> %s\n", trim);
		while (trim[o])
		{
			if (trim[o] == ' ')
				return (printf("error\nthis number {%s} is not correct \n", trim), 1);
			if (ft_isdigit(trim[o]))
				count ++;
			o++;
		}
		if (count > 3)
			return (printf("error\nthis number {%s} is not correct \n",trim), 1);
		free(trim);
		k++;
	}
	if (str[j] == 'F')
	{
		i = 0;
		while(new[i])
		{
			texture->F[i] = ft_atoi(new[i]);
			if ( texture->F[i] > 255)
				return (printf("error\nthis number {%d} > 255\n",texture->F[i]), 1);
			i++;
		}
	}
	if (str[j] == 'C')
	{
		i = 0;
		while(new[i])
		{
			texture->C[i] = ft_atoi(new[i]);
			if ( texture->C[i] > 255)
				return (printf("error\nthis number {%d} > 255\n",texture->C[i]), 1);
			i++;
		}
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
	texture->map = NULL;
	texture->F[0] = -1;
	texture->F[1] = -1;
	texture->F[2] = -1;
	texture->C[0] = -1;
	texture->C[1] = -1;
	texture->C[2] = -1;
}
int check_all_is_full(t_texture *texture)
{
	if (texture->EA != NULL &&  texture->NO != NULL
		&& texture->SO != NULL &&  texture->WE != NULL
		&& texture->F[0] >= 0 && texture->F[1] >= 0
		&& texture->F[2] >= 0 && texture->C[0] >= 0
		&& texture->C[1] >= 0 && texture->C[2] >= 0)
		return 1;
	return 0;
}
int read_file(char **av, t_cub *cub, t_texture *texture)
{
	int f;
	int fd;
	int i;
	f = 0;
	fd = open(av[1], O_RDWR);
	if (fd < 0)
		return (1);
	cub->file = get_next_line(fd);
	if (!(cub->file))
		return (write(2, "error\n", 6) ,1);
	init_variables_direction(texture);
	while(cub->file != NULL)
	{   
		i = 0;
		char *trim = ft_strtrim(cub->file, " ");
		// printf("%s", trim);
		while(trim[i])
			i++;
		if ((i > 0) && trim[i - 1] != '\n')
			return (close(fd), write(2, "error\nerror new line\n", 21) ,1);
		if (i == 1 && trim[i - 1] == '\n')
		{
			free(cub->file);
			cub->file = get_next_line(fd);
			continue;
		}
		if (check_all_is_full(texture))
		{
			f = 100;
			break;
		}
		if (go_to_check(cub->file, texture, 0))
				return (close(fd),1);
		free(cub->file);
		cub->file = get_next_line(fd);
	}
	if (f == 100)
	{
		while(cub->file != NULL)
		{   
			i = 0;
			while(cub->file[i])
				i++;
			if ((i > 0) && cub->file[i - 1] != '\n')
				return (close(fd), write(2, "error\nadd a new line in the last line in map\n", 45) ,1);
			texture->map = ft_strjoin1(texture->map, cub->file);
			free(cub->file);
			cub->file = get_next_line(fd);
		}
	}
	printf("%s", texture->map);
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
	// printf("NO ---> [[[%s]]]\n", texture.NO);
	// printf("SO ---> [[[%s]]]\n", texture.SO);
	// printf("WE ---> [[[%s]]]\n", texture.WE);
	// printf("EA ---> [[[%s]]]\n", texture.EA);
	// printf("------------------------------------\n");
	// printf("F ---> %d\n", texture.F[0]);
	// printf("F ---> %d\n", texture.F[1]);
	// printf("F ---> %d\n", texture.F[2]);
	// printf("------------------------------------\n");
	// printf("C ---> %d\n", texture.C[0]);
	// printf("C ---> %d\n", texture.C[1]);
	// printf("C ---> %d\n", texture.C[2]);
	return 0;
}
