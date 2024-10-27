/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_moves_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:22:43 by anqabbal          #+#    #+#             */
/*   Updated: 2024/10/27 13:12:43 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

float	fixing_fichbowl(float ds, float angle, t_exec *exec)
{
	return (ft_abs((ds * cos(exec->ply.rotangle - angle))));
}

int32_t get_pixel(uint8_t*	pixels, int o)
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    r = pixels[o];
    g = pixels[o + 1];
    b = pixels[o + 2];
    a = pixels[o + 3];
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_the_walls22(int rx, t_exec *exec, float angle, t_ray *ray)
{
    float wall_heigh;
    static int n;
    int y ;
    int x ;
    int color;
    wall_heigh = ((TILE_SIZE) / (ray->ds)) * (((exec->info.win_wid / 2) / tan(degree_to_rad(AOV / 2))));
    if (isinf(wall_heigh))
    {
        wall_heigh = n;
        if (rx == 0)
            wall_heigh = exec->info.win_hei;
    }
    n = wall_heigh;
    y = 0;
    x = 0;
    int clg = ((exec->info.win_hei) / 2) - (wall_heigh / 2);

    while(y < clg)
        mlx_put_pixel(exec->wind_image, rx, y++, exec->info.clg_cl);
    int ofsetX;
    int o = 0;
    if (ray->hv == 1)
        ofsetX = (int)ray->dx % TILE_SIZE;
    else
        ofsetX = (int)ray->dy % TILE_SIZE;
    int max_offset = TILE_SIZE * TILE_SIZE * 4;
    while((int)x++ < wall_heigh && x <= (int)exec->info.win_hei)
    { 
        int top = y + (wall_heigh / 2) - (exec->info.win_hei / 2);
        int ofsetY = top * ((float)TILE_SIZE / wall_heigh);
        o = ((TILE_SIZE * ofsetY) + ofsetX) * 4;
        if (o >= 0 && o + 3 < max_offset)
        {
            if (ray->hv == 0 && ((angle >= 0 && angle < M_PI_2) || (angle >= 3 * M_PI_2 && angle < 2 * M_PI)))
                color = get_pixel(exec->we->pixels, o);
            else if (ray->hv == 0 && angle >= M_PI_2 && angle < 3 * M_PI_2)
                color = get_pixel(exec->ea->pixels, o);
            else if (ray->hv == 1 && angle >= 0 && angle < M_PI)
                color = get_pixel(exec->so->pixels, o);
            else if (ray->hv == 1 && angle >= M_PI && angle < 2 * M_PI)
                color = get_pixel(exec->no->pixels, o);
            if (ray->d == 2)
                color = get_pixel(exec->d->pixels, o);
        }
        mlx_put_pixel(exec->wind_image, rx, y++, color);
    }
    while(y < (int)exec->info.win_hei && y >= x)
        mlx_put_pixel(exec->wind_image, rx, y++, exec->info.flr_cl);
}

void	catch_moves(mlx_key_data_t key, void *p)
{
	t_exec	*exec;

	exec = p;
	if (key.key == MLX_KEY_RIGHT)
		move_right(exec, 1);
	else if (key.key == MLX_KEY_LEFT)
		move_left(exec, 1);
	else if (key.key == MLX_KEY_W)
		move_up(exec);
	else if (key.key == MLX_KEY_S)
		move_down(exec);
	else if (key.key == MLX_KEY_D)
		move_right(exec, 0);
	else if (key.key == MLX_KEY_A)
		move_left(exec, 0);
	else if (key.key == MLX_KEY_ESCAPE || key.key == MLX_KEY_Q)
		clean_and_exit(exec);
    // mouse_fun(exec);
}
