/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:35:55 by ael-mejh          #+#    #+#             */
/*   Updated: 2024/10/24 19:31:39 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	init_variables_direction(t_texture *texture)
{
	texture->ea = NULL;
	texture->no = NULL;
	texture->so = NULL;
	texture->we = NULL;
	texture->map = NULL;
	texture->f[0] = -1;
	texture->f[1] = -1;
	texture->f[2] = -1;
	texture->c[0] = -1;
	texture->c[1] = -1;
	texture->c[2] = -1;
}

int	read_file(char **av, t_cub *cub, t_texture *texture)
{
	size_t	j;
	int		fd;
	int		i;

	init_variables_direction(texture);
	fd = open(av[1], O_RDWR);
	if (fd < 0)
		return (1);
	cub->file = get_next_line(fd);
	if (!(cub->file))
		return (write(2, "error\nempty file\n", 17), 1);
	if (read_textures_colors(cub, fd, texture))
		return (1);
	cub->len = 0;
	if (cub->file)
	{
		cub->map = NULL;
		while (cub->file != NULL)
		{
			j = ft_strlen(cub->file);
			i = 0;
			while (cub->file[i])
				i++;
			if (i == 1 && cub->file[i - 1] == '\n')
				return (close(fd), write(2, "error\nerror in map", 18), 1);
			if (j > cub->len)
				cub->len = j;
			cub->map = ft_strjoin1(cub->map, cub->file);
			cub->file = get_next_line(fd);
		}
	}
	else
		return (printf("error\nput your map\n"), 1);
	close(fd);
	if (parsing_map(cub, cub->len))
		return (1);
	else
		texture->map = cub->map1;
	return (0);
}

