/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:57:45 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/03 19:52:33 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

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

# define ERR_ELEMENT "element pas au top ou element en trop"
# define ERR_PATH "path incorrect"
# define ERR_COLOR "rgb envoye pas bonne"
# define EMPTY_LINE "ligne vide"
# define ERR_FILE "fd incorect"
# define NB_ARG "nombre d'argument incorect"
# define EMPTY_FILE "fichier vide ou n'existe pas"
# define ERR_MALLOC "malloc a foirer / dupmap"
# define ERR_MAP "value map"
# define ERR_PLAYER "player"


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

typedef enum
{
	NO = 0,
	SO = 1,
	EA = 2,
	WE = 3,
	F = 4,
	C = 5
}		elements;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

/* main.c */
int		check_file(char *av);
int		file_exist(char *path);

/* convert_map.c */
char			*pass_blank(char *temp, int fd);
char			**dup_map(char **map, int i);
void			check_char(t_player *m, char c);
struct s_player	*check_start(struct s_player *m, char *s, int y);
void			convert_map(t_data *game, char *av);

/* verif_texture.c */
int		path_xpm(char *path);
int		all_textures(t_data *game);
int	cut_path(t_data *game, char *line, int count);
void	get_textures(t_data *game, int fd);

/* get_path */
int		lenght(char *line, int j);
int		search_texture(char *word, char *line);
int		find_elements(char *line);
char	*get_path(char *line, int j);
void	set_path(t_data *game, char *line, char *element);

/* exit_fonction.c */
int		ft_exit(int nb, char *msg);
int 	err(char *msg, int nb);

/* get_next_line.c/ get_next_line_utils.c */
int		ft_strlen(const char *str);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		size_line(char *strings, int i);
char	*get_next_line(int fd);

/* ft_utils.c */
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_strstr(char *str, char *to_find);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
char	*ft_strdup(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *ptr, size_t size);
int		ft_atoi(char *nptr);

/* init_struct.c */
void	set_null(t_data *game);
void	set_null2(t_data *game);
void	set_null3(t_data *game);
t_data	*init_struct(void);


/* verif_color.c */
int	color_lenght(char *line, int pos);
int	range_color(int nb);
int	comma(char *line);
char *get_nb(char *line, char *temp, int i);
int	valid_color(char *line);

void	display_map(t_data *game);

/* verif_wall.c */
int	map_close(t_data *game);



#endif