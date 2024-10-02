/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:23:04 by anqabbal          #+#    #+#             */
/*   Updated: 2024/10/02 18:07:21 by ael-mejh         ###   ########.fr       */
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



void fr(){system("leaks cub");}
int main(int ac, char **av)
{
	t_exec exec;
	t_cub cub;
	t_texture texture;
	// atexit(fr);
	if (ac != 2)
		return (write(0, "error\ninvalid argument\n", 23), 1);
	if (check_extention(av[1]))
		return (write(0, "error\ninvalid extention\n", 24), 1);
	if (read_file(av, &cub, &texture))
		return (gc_free_all(), 1);
	int i = 0;
	while (texture.map[i])
		i++;
	exec.mlx.mlx = mlx_init((int)cub.len * 30, i * 30, "Cub3D", true);
	exec.mlx.mlx_w = mlx_new_image(exec.mlx.mlx, 0, 0);

	mlx_loop(exec.mlx.mlx);
	// mlx_texture_to_image()
	// printf("%zu\n\n\n", cub.len);
	// printf("%s\n", texture.NO);
	// printf("%s\n", texture.SO);
	// printf("%s\n", texture.WE);
	// printf("%s\n", texture.EA);
	// printf("F (%d, %d, %d)\n", texture.F[0], texture.F[1], texture.F[2]);
	// printf("C (%d, %d, %d)\n", texture.C[0], texture.C[1], texture.C[2]);
	// int i = 0;
	// while (texture.map[i])
	// {
	// 	printf("%s\n", texture.map[i]);
	// 	i++;
	// }


	gc_free_all();
	return 0;
}
