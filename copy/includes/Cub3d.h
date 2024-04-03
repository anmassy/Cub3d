/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:57:45 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/03 14:35:22 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>

#include "../mlx_linux/mlx.h"

/* TEXTURES */
# define NO_T "./textures/north_texture.xpm"
# define SO_T "./textures/south_texture.xpm"
# define EA_T "./textures/east_texture.xpm"
# define WE_T "./textures/west_texture.xpm"
# define FLOOR_T "./images/floor_texture.xpm"
# define CEILING_T "./images/ceiling_texture.xpm"

/* KEYS */
# define L 67 //fleche de droite
# define R 68 //fleche de gauche
# define W 119
# define A 97
# define S 115
# define D 100
# define ESC 65307

# define TOP_ELEM "element pas au top ou element en trop"
# define ERR_PATH "path incorrect"
# define ERR_COLOR "rgb envoye pas bonne"
# define EMPTY_LINE "ligne vide"
# define ERR_FILE "fd incorect"


typedef struct s_player
{
	char	**m;
    int     first_row;
    int     last_row;
    char    orientation;
    int     height;
	double	startX;
	double	startY;
    int     x;
    int     y;
}				t_player;

typedef struct s_texture
{
    char    *n_path;
	char    *s_path;
	char    *e_path;
	char    *w_path;
    char    *c_color;
    char    *f_color;
}				t_texture;

typedef struct s_img
{
	void	*mlx_img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int 	width;
	int 	height;
}	t_img;

typedef struct s_rayc
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int	  	mapX;
	int	  	mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double 	deltaDistY;
	int		stepX;
	int		stepY;
	int 	hit;
	int 	side;
	double	perpWallDist;
	double	movespeed;
	double	rotspeed;
	int		textDir;
	double	wallX;
	int		texX;
	int		move_up;
	int		move_down;
	int		move_left;
	int		move_right;
	int		move_cam_left;
	int		move_cam_right;
}	t_rayc;

typedef struct  s_data
{
    struct s_player 	*val;
    struct s_texture 	*mesh;
    t_img				img;
	t_img				*text;
    t_rayc	          	rayc;
    void	            *mlx_ptr;
	void	            *win_ptr;
}               t_data;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

/* get_next_line.c/ get_next_line_utils.c */
int		ft_strlen(const char *str);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		size_line(char *strings, int i);
char	*get_next_line(int fd);

/* init_struct.c */
void	set_null(t_data *game);
void	set_null2(t_data *game);
void	set_null3(t_data *game);
t_data	*init_struct(void);

/* verif_map.c */
int	who_is_that_player(t_data *game);
int	check_value(t_data *game);
int set_first_row(t_data *game);
int verif_map(t_data *game);

/* ft_utils.c */
int ft_strncmp(char *s1, char *s2, size_t n);
int	ft_strstr(char *str, char *to_find);
void set_size_map(t_data *game);

/* verif_texture.c */
int all_texture(t_data *game) ;
int texture_on_top(t_data *game);
int verif_texture(t_data *game);

/* verif_path.c */
int lenght(char *line, int j);
void cut_path(t_data *game, char *line);
int	path_xpm(char *path);
int verif_path(t_data *game);
void get_textures(t_data *game, int fd);

/* verif_color.c */
char *cut_color(t_data *game, int line, char *element);
int color_lenght(char *line, int pos);
int range_color(int nb);
int	valid_color(char *line);
int verif_color(t_data *game);

/* verif_wall.c */
int check_up(t_data *game, int i, int j);
int check_down(t_data *game, int i, int j);
int check_left(t_data *game, int i, int j);
int check_right(t_data *game, int i, int j);
int map_close(t_data *game);

/* main.c */
void	display_map(t_data *game);

/* convert_map.c */
int	    len_doc(char *av);
int	count_line(char *av, t_data *game);
void	convert_map(t_data *game, char *av);
int	check_file(char *av);
int	file_exist(char *path);

/*start game*/
void	start_game(t_data *game);
void	catch_map(t_data *game);

int ft_exit(int nb, char *msg);

#endif