/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:14:44 by anqabbal          #+#    #+#             */
/*   Updated: 2024/10/15 11:43:34 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

int     init_info_struct(t_info *info, t_cub *cub, t_texture *text)
{
    info->map = text->map;
    info->win_wid = cub->len * PIXELS;
    info->win_hei = cub->len_h * PIXELS;
    info->flr_cl = text->F_color;
    // printf("%x\n", );
    info->clg_cl = text->C_color;
    return (0);
}

 int    init_structs(void *ptr, int ind, char **av)
 {
    t_exec *exec;

    (void)ind;
    exec = ptr;
    if (read_file_bonus(av, &exec->cub, &exec->text))
		  return (gc_free_all(), -1);
    init_info_struct(&exec->info, &exec->cub, &exec->text);
    return (0);
}