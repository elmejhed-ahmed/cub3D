/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:23:04 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/25 17:35:00 by ael-mejh         ###   ########.fr       */
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
	/*initialaze avariable*/
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
	/*check all variable in struct is full*/
	if (texture->EA != NULL &&  texture->NO != NULL
		&& texture->SO != NULL &&  texture->WE != NULL
		&& texture->F[0] >= 0 && texture->F[1] >= 0
		&& texture->F[2] >= 0 && texture->C[0] >= 0
		&& texture->C[1] >= 0 && texture->C[2] >= 0)
		return 1;
	return 0;
}

int parsing_map(t_cub *cub)
{
	cub->s = 0;
	cub->n = 0;
	cub->w = 0;
	cub->e = 0;
	
	/* split '\n' in map to change it to 2D array */
	cub->map1 = ft_split(cub->map, '\n');
	int i = 0;
	/*check valid caracter in map*/
	while(cub->map1[i])
	{
		int j = 0;
		while(cub->map1[i][j])
		{
			/*count map is have this caracters '1' '0' ' ' 'S' 'W' 'N' 'E' */
			if (cub->map1[i][j] != '1' && cub->map1[i][j] != '0'
				&& cub->map1[i][j] != ' ' && cub->map1[i][j] != 'N'
				&& cub->map1[i][j] != 'S' && cub->map1[i][j] != 'E'
				&& cub->map1[i][j] != 'W')
			{
				return (printf("Error\ninvalid caracter '%c' in map\n", cub->map1[i][j]),1);
			}
			/*count player*/
			if (cub->map1[i][j] == 'S')
				cub->s++;
			if (cub->map1[i][j] == 'W')
				cub->w++;
			if (cub->map1[i][j] == 'E')
				cub->e++;
			if (cub->map1[i][j] == 'N')
				cub->n++;
			j++;
		}
		i++;
	}
	/*check player*/
	if (cub->s > 1 || cub->w > 1 || cub->e > 1 || cub->n > 1)
		return (printf("you have multiple player\n"), 1);
	if (cub->s == 1 && (cub->w > 0 || cub->e > 0 || cub->n > 0))
		return (printf("you have multiple player\n"), 1);
	if (cub->w == 1 && (cub->s > 0 || cub->e > 0 || cub->n > 0))
		return (printf("you have multiple player\n"), 1);
	if (cub->e == 1 && (cub->s > 0 || cub->w > 0 || cub->n > 0))
		return (printf("you have multiple player\n"), 1);
	if (cub->n == 1 && (cub->s > 0 || cub->e > 0 || cub->w > 0))
		return (printf("you have multiple player\n"), 1);
	i = 0;
	size_t j = 0;
	int p = 0;
	/*now check  is avalid map or not*/
	while (cub->map1[i])
	{
		j = 0;
		/*skip just ' '*/
		while (cub->map1[i][j] == ' ')
			j++;

		if (cub->map1[i][j] == '\0')
		{
			int k = i - 1;
			while(cub->map1[k][j] == ' ')
				j++;
			while (cub->map1[k][j])
			{
				if (cub->map1[k][j] == '0')
					return (printf("NOT VALID ==> %s\n", cub->map1[k]),1);
				j++;
			}
			i++;
			p = i;
			continue;
		}
		while (cub->map1[i][j])
		{
			if (((i == 0) && cub->map1[i][j] == '0')
				|| (j == 0 && cub->map1[i][j] == '0')
				|| (i == p && cub->map1[i][j] == '0')
				|| (cub->map1[i][j] == '0' && cub->map1[i][j + 1] == ' ')
				|| (cub->map1[i][j] == '0' && cub->map1[i][j + 1] == '\0')
				|| (i != 0 && j < ft_strlen(cub->map1[i - 1]) && cub->map1[i][j] == ' ' && cub->map1[i][j + 1] == '0')
				|| (i != 0 && j < ft_strlen(cub->map1[i - 1]) && cub->map1[i][j] == '0' && cub->map1[i - 1][j] == ' ')
				|| (i != 0 && j < ft_strlen(cub->map1[i - 1]) && cub->map1[i][j] == '0' && cub->map1[i - 1][j] == '\0')
				|| (i != 0 && j < ft_strlen(cub->map1[i - 1]) && cub->map1[i][j] == ' ' && cub->map1[i - 1][j] == '0')
				|| (cub->map1[i + 1] == NULL && cub->map1[i][j] == '0') // for last line if have '0'
				|| (cub->map1[i + 1]&& i != 0 && j < ft_strlen(cub->map1[i + 1]) && cub->map1[i][j] == ' ' && cub->map1[i + 1][j] == '0'))
				return (printf("NOT VALID ==> %s\n", cub->map1[i]),1);
			j++;
		}
		i++;
	}
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
	/*read just a textures and color*/
	while(cub->file != NULL)
	{   
		i = 0;
		char *trim = ft_strtrim(cub->file, " ");
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
	/*if all variable (texture and color is full) go to read map now and join in this variable cub->map*/
	if (cub->file)
	{
		cub->map = NULL;
		while(cub->file != NULL)
		{
			i = 0;
			while(cub->file[i])
				i++;
			if ((i > 0) && cub->file[i - 1] != '\n')
				return (close(fd), write(2, "error\nadd a new line in the last line in map\n", 45) ,1);
			if (i == 1 && cub->file[i - 1] == '\n')
				return (close(fd), write(2, "error\nerror in map", 18) ,1);
			cub->map = ft_strjoin1(cub->map, cub->file);
			free(cub->file);
			cub->file = get_next_line(fd);
		}
		
	}
	else
		return (printf("error\nput your map\n"), 1);
	close(fd);
	/*after read map go to parsing this map*/
	if (parsing_map(cub))
		return (1);
	else
		texture->map = cub->map1;
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
	
	printf("%s\n", texture.NO);
	printf("%s\n", texture.SO);
	printf("%s\n", texture.WE);
	printf("%s\n", texture.EA);
	printf("F (%d, %d, %d)\n", texture.F[0], texture.F[1], texture.F[2]);
	printf("C (%d, %d, %d)\n", texture.C[0], texture.C[1], texture.C[2]);
	int i = 0;
	while (texture.map[i])
	{
		printf("%s\n", texture.map[i]);
		i++;
	}
	
	return 0;
}
