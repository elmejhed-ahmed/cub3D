/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:22:43 by anqabbal          #+#    #+#             */
/*   Updated: 2024/11/04 10:24:55 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	get_pixel(uint8_t *pixels, int o)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = pixels[o];
	g = pixels[o + 1];
	b = pixels[o + 2];
	a = pixels[o + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_the_walls22(int rx, t_exec *exec, float angle, t_ray *ray)
{
	static int	n;
	int			y;
	int			clg;

	y = 0;
	ray->wall_height = ((PIXELS) / (ray->ds))
		* (((exec->info.win_wid / 2) / tan(degree_to_rad(AOV / 2))));
	if (isinf(ray->wall_height))
	{
		ray->wall_height = n;
		if (rx == 0)
			ray->wall_height = exec->info.win_hei;
	}
	n = ray->wall_height;
	ray->x = rx;
	clg = ((exec->info.win_hei) / 2) - (ray->wall_height / 2);
	while (y < clg)
		mlx_put_pixel(exec->wind_image, rx, y++, exec->info.clg_cl);
	draw_the_textures(exec, angle, &y, ray);
	while (y < (int)exec->info.win_hei)
		mlx_put_pixel(exec->wind_image, rx, y++, exec->info.flr_cl);
}

static void	complete_catch_moves(t_exec *exec)
{
	if (mlx_is_key_down(exec->mlx, MLX_KEY_C))
	{
		if ((exec->ply.move_inc * 1.5) < 500)
			exec->ply.move_inc *= 1.5;
	}
	else if (mlx_is_key_down(exec->mlx, MLX_KEY_Z))
	{
		if ((exec->ply.move_inc / 1.5) > 100)
			exec->ply.move_inc /= 1.5;
	}
}

void	catch_moves(void *p)
{
	t_exec	*exec;

	exec = p;
	if (mlx_is_key_down(exec->mlx, MLX_KEY_RIGHT))
		move_right(exec, 1);
	else if (mlx_is_key_down(exec->mlx, MLX_KEY_LEFT))
		move_left(exec, 1);
	else if (mlx_is_key_down(exec->mlx, MLX_KEY_W))
		move_up(exec);
	else if (mlx_is_key_down(exec->mlx, MLX_KEY_S))
		move_down(exec);
	else if (mlx_is_key_down(exec->mlx, MLX_KEY_D))
		move_right(exec, 0);
	else if (mlx_is_key_down(exec->mlx, MLX_KEY_A))
		move_left(exec, 0);
	else if (mlx_is_key_down(exec->mlx, MLX_KEY_ESCAPE)
		|| mlx_is_key_down(exec->mlx, MLX_KEY_Q))
		clean_and_exit(exec);
	else
		complete_catch_moves(exec);
	ray_casting(exec);
}
