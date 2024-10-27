/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:20:52 by ael-mejh          #+#    #+#             */
/*   Updated: 2024/10/27 13:24:19 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

int	switch_rgb_hex(int color[3], int a)
{
	return (color[0] << 24 | color[1] << 16 | color[2] << 8 | a);
}

int	is_invalid(char **map, int i, size_t j)
{
	return (
		((i == 0 || j == 0) && (map[i][j] != '1')) ||
		(map[i][j + 1] == ' ' || map[i][j - 1] == ' ' || map[i][j + 1] == '\0')
		|| ((map[i - 1][j] == ' ' || map[i - 1][j] == '\0')) ||
		(map[i + 1] == NULL
		|| (map[i + 1][j] == ' ' || map[i + 1][j] == '\0')));
}
