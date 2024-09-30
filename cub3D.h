/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-mejh <ael-mejh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 09:34:37 by anqabbal          #+#    #+#             */
/*   Updated: 2024/09/30 13:52:12 by ael-mejh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "./minilibx-linux/mlx.h"

# define AOV 60
# define PIXELS 30
# define SPEED 10
# define VIEW_SPEED 10
# define P_2_PP 150
#define PIXELS 30


typedef struct s_cub
{
    char	*file;
    char	*file2;    
    char	*copy;    
    char	*tmp;
	char	*map;
	char	**map1;
	int 	count_player;
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
	void	*mlx_img_add;
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

typedef struct s_img
{
	void			*image;
	char			*image_add;
	int				bits_pp;
	int				line_;
	int				endian;
	unsigned int	xlen;
	unsigned int	ylen;
	int				color;
}	t_img;

typedef struct s_ply
{
	void	*img;
	int		turn;
	double		rotangle;
	int		px;
	int		py;
	int		rds;
	int		endlx;
	int		endrx;
	int		enduy;
	int		enddy;
} t_ply;

typedef struct s_tex
{
	void	*image;
	void	*flr;
	void	*wall;
	t_ply	ply;

} t_tex;

typedef struct s_ray
{
	int	x;
	int	y;
	int	len;
} t_ray;

typedef struct s_cir
{
	int	x;
	int	y;
	int	cx;
	int cy;
	int rds;
	int to_center;
	int to_fill;
} t_cir;

typedef struct s_exec
{
	t_mlx	mlx;
	t_info	inf;
	t_img	img;
	t_tex	tex;
	t_ray	line;
	char	**av;

}	t_exec;

/*PART1*/
int read_file(char **av, t_cub *cub, t_texture *texture);

/*PART 2*/
char	**cub_get_map(t_info *inf, int i);
double	degree_to_rad(double deg);
void	to_free(char **av);
int		file_len(t_info *info);

#endif




