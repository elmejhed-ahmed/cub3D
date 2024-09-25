/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:34:37 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/25 17:10:09 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./libft/libft.h"
# include <stdio.h>
# include "./part1/get_next_line.h"
# include <math.h>
# include <unistd.h>
# include <mlx.h>
# ifndef PI
# define PI 3.14

# define N (str[i] == 'N' && str[i + 1] == 'O')
# define S (str[i] == 'S' && str[i + 1] == 'O')
# define W (str[i] == 'W' && str[i + 1] == 'E')
# define E (str[i] == 'E' && str[i + 1] == 'A')
# define Fl (str[i] == 'F')
# define Ce (str[i] == 'C')
# endif

#define PIXELS 30

typedef struct s_cub
{
    char	*file;
    char	*file2;    
    char	*copy;    
    char	*tmp;
	char	*map;
	char	**map1;
	int 	n;
	int		s;
	int		w;
	int		e;
}   t_cub;

typedef struct s_texture
{
	char 	*NO;
	char 	*SO;
	char 	*WE;
	char 	*EA;
	int		F[3];
	int		C[3];
	char	**map;
} t_texture;

typedef struct	s_mlx
{
	void	*mlx;
	void	*mlx_w;
	unsigned int	win_hei;
	unsigned int	win_wid;
}	t_mlx;

typedef struct s_info
{
	char		*path;
	unsigned int hei;
	unsigned int wid;
	char		**map;
	int			flr_cl;
	int			clg_cl;

}	t_info;

typedef struct s_exec
{
	t_mlx	mlx;
	t_info	inf;
	char	**av;
}	t_exec;

/*PART 2*/
char	**cub_get_map(t_info *inf, int i);
double	degree_to_rad(double deg);
void	to_free(char **av);
int		file_len(t_info *info);

#endif




