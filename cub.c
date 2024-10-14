/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:23:04 by anqabbal          #+#    #+#             */
/*   Updated: 2024/10/14 14:05:52 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void bresenham_line_algo2(int y0, int x0, int y1, int x1, t_exec *exec)
 {
    int dx;
    int dy;
    int sx ;
    int sy ;
    int err;
    int e2;

    dx = ft_abs(x1 - x0);
    dy = ft_abs(y1 - y0);
    if (x0 < x1)
        sx = 1;
    else 
        sx = -1;
    if (y0 < y1)
        sy = 1;
    else
        sy = -1;
    err = dx - dy;
    mlx_put_pixel(exec->wind_image, x0, y0, 0x12FF0012);
    while (1)
    {
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
         {
            err += dx;
            y0 += sy; 
        }
        if ((x0 < 0 || y0 < 0 || x0 >= (int)exec->info.win_wid  || y0 >= (int)exec->info.win_hei) ||  (x0 == x1 && y0 == y1))
            break;
        mlx_put_pixel(exec->wind_image, x0, y0, 0x00000000);
    }
}

int ft_dda_algo(t_exec *exec, float endy, float endx)
{
    float m;
    float starty;
    float startx;

    starty = exec->tex.ply.py;
    startx = exec->tex.ply.px;
    m = (endy - starty) / (endx - startx);
    int i = 1;
    while(i < 30)
    {
        if (m < 1)
        {
            startx += 1;
            starty += m;
        }
        else if (m > (float)1)
        {
            startx += 1;
            starty += (1 / m);
        }
        else
        {
            startx += 1;
            starty += 1;
        }
        mlx_put_pixel (exec->wind_image, startx, starty, 0x000000);
        i++;
    }
    return (0);
}

void my_close(void *ptr)
{
    t_exec *exec;

    exec = ptr;
    exit (0);
}

mlx_image_t *ft_texture(t_exec *exec, char *path_texture)
{
    mlx_texture_t *texture;
    mlx_image_t *image;
    texture = mlx_load_png(path_texture);
    if (!texture)
	{
		write(2,"Error\nIn valid path",19);
		printf("'%s'", path_texture);
		clean_and_exit(exec);
	}
    image = mlx_texture_to_image(exec->mlx, texture);
	mlx_delete_texture(texture);
    return image;
}
int start_cub(char **av)
{
    t_exec exec;

    if (init_structs(&exec, 0, av) < 0)
        return (-1);
    if (creat_and_start_awindow(&exec) < 0)
        return (-1);
    // mlx_destroy_window(exec.mlx.mlx, exec.mlx.mlx_w); //TODO to destory 2d map uncomment this destroy
    // mlx_destroy_window(exec.mlx.mlx, exec.mlx.mlx_w1); //TODO to destory 3d map uncomment this destroy
    draw_map(&exec);       // the same
    exec.no = ft_texture(&exec, exec.text.NO);
    exec.so = ft_texture(&exec, exec.text.SO);
    exec.we = ft_texture(&exec, exec.text.WE);
    exec.ea = ft_texture(&exec, exec.text.EA);
    set_player_info(&exec);
    ray_casting(&exec);
    mlx_key_hook(exec.mlx, &catch_moves, &exec);
    mlx_loop(exec.mlx);
    // mlx_hook(exec.mlx.mlx_w1, 2, 0, catch_moves, &exec); // switch the window pointer for which window you want to catch keys
    return (0);
}
/* FOR PARSING */
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

int	main(int ac, char **av)
{
	if (ac != 2)
		return (write(0, "error\ninvalid argument\n", 23), 1);
	if (check_extention(av[1]))
		return (write(0, "error\ninvalid extention\n", 24), 1);
    if (start_cub(av) < 0)
        return (1);
}