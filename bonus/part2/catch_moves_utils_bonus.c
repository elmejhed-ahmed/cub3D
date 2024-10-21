/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_moves_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:18:47 by anqabbal          #+#    #+#             */
/*   Updated: 2024/10/20 12:50:47 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

void	clean_and_exit(void *ptr)
{
	t_exec	*exec;

	exec = ptr;
	gc_free_all();
	mlx_delete_image(exec->mlx, exec->wind_image);
	mlx_terminate(exec->mlx);
	exit (0);
}
void update_player_pos(t_exec *exec, float oldx, float oldy)
{
	// it_the_old_a_door();
	exec->info.map[(int)floor(oldy / PIXELS)][(int)floor(oldx / PIXELS)] = '0';
	exec->info.map[(int)floor(exec->ply.py / PIXELS)][(int)floor(exec->ply.px / PIXELS)] = exec->ply_char;
}

void	move_left(t_exec *exec, char ind)
{
	if (ind == 0)
	{
		float	oldx;
		float	oldy;

		if (!ft_check_walls(exec, 0))
			return ;
		oldx = exec->ply.px;
		oldy = exec->ply.py;
		exec->ply.py -= (sin(exec->ply.rotangle
					- degree_to_rad(90)) * exec->ply.move_inc);
		exec->ply.px -= (cos(exec->ply.rotangle
					- degree_to_rad(90)) * exec->ply.move_inc);
		update_player_pos(exec, oldx, oldy);
	}
	else
	{
		exec->ply.rotangle -= VIEW_SPEED;
		if (exec->ply.rotangle < (float)0)
			exec->ply.rotangle += 2 * M_PI;
	}
}


void	move_up(t_exec *exec)
{
	float	oldx;
	float	oldy;

	if (!ft_check_walls(exec, 1))
		return ;
	oldx = exec->ply.px;
	oldy = exec->ply.py;
	exec->ply.py -= (sin(exec->ply.rotangle) * exec->ply.move_inc);
	exec->ply.px -= (cos(exec->ply.rotangle) * exec->ply.move_inc);
	update_player_pos(exec, oldx, oldy);
}

void	move_right(t_exec *exec, char ind)
{
	if (ind == 0)
	{
		float	oldx;
		float	oldy;

		if (!ft_check_walls(exec, 2))
			return ;
		oldx = exec->ply.px;
		oldy = exec->ply.py;
		exec->ply.py -= (sin(exec->ply.rotangle
					+ degree_to_rad(90)) * exec->ply.move_inc);
		exec->ply.px -= (cos(exec->ply.rotangle
					+ degree_to_rad(90)) * exec->ply.move_inc);
		update_player_pos(exec, oldx, oldy);
	}
	else
	{
		if (exec->ply.rotangle > (M_PI * 2))
			exec->ply.rotangle -= 2 * M_PI;
		exec->ply.rotangle += VIEW_SPEED;
	}
}

void	move_down(t_exec *exec)
{
	float	oldx;
	float	oldy;

	if (!ft_check_walls(exec, 3))
		return ;
	oldx = exec->ply.px;
	oldy = exec->ply.py;
	exec->ply.py += (sin(exec->ply.rotangle) * exec->ply.move_inc);
	exec->ply.px += (cos(exec->ply.rotangle) * exec->ply.move_inc);
	update_player_pos(exec, oldx, oldy);
}
