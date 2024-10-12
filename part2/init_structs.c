/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 13:14:44 by anqabbal          #+#    #+#             */
/*   Updated: 2024/10/12 16:57:18 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d.h"

int     init_info_struct(t_info *info, t_cub *cub, t_texture *text)
{
    info->map = text->map;
    info->win_wid = cub->len * PIXELS;
    info->win_hei = cub->len_h * PIXELS;
    info->flr_cl = 0xE3E3E3E3;
    info->clg_cl = 0x332d3133;
    return (0);
}

 int    init_structs(void *ptr, int ind, char **av)
 {
    t_exec *exec;

    (void)ind;
    exec = ptr;
    if (read_file(av, &exec->cub, &exec->text))
		  return (gc_free_all(), 0);
    init_info_struct(&exec->info, &exec->cub, &exec->text);
    return (0);
}