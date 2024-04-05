/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:57:45 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/05 20:03:07 by anmassy          ###   ########.fr       */
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
#include <math.h>

#include "../mlx_linux/mlx.h"

/* TEXTURES */
# define NO_T "./textures/north_texture.xpm"
# define SO_T "./textures/south_texture.xpm"
# define EA_T "./textures/east_texture.xpm"
# define WE_T "./textures/west_texture.xpm"
# define FLOOR_T "./images/floor_texture.xpm"
# define CEILING_T "./images/ceiling_texture.xpm"


/* KEYS */
# define L 65363 //fleche de droite
# define R 65361 //fleche de gauche
# define S 119
# define D 100
# define W 115
# define A 97
# define ESC 65307

# define SCREENWIDTH 1920
# define SCREENHEIGHT 1080

# define ERR_MALLOC "malloc"
# define ERR_ELEMENT "the elements (texture) are not well written"
# define ERR_PATH "path is invalid"
# define ERR_COLOR "this color (RGP) does not exist"
# define EMPTY_LINE "the line is empty"
# define ERR_WALL "the map is not closed"
# define NB_ARG "number of arguments incorect"
# define EMPTY_FILE "the file is empty or does not exist"
# define ERR_MAP "the map is not well written"
# define ERR_PLAYER "number of players incorrect"


typedef struct s_player
{
	char	**m;
    int     first_row;
    int     last_row;
    char    orientation;
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

typedef struct s_print
{
	int 	x;
	int		y;
	int 	lineheight;
	int		drawstart;
	int		drawend;
	double step;
	double texPos;
	int 	color;
	int 	texY;
}	t_print;

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
void	display_map(char **map);
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
int		cut_path(t_data *game, char *line, int count);
void	get_textures(t_data *game, int fd);

/* get_path */
int		lenght(char *line, int j);
int		search_texture(char *word, char *line);
int		find_elements(char *line);
char	*get_path(char *line, int j);
void	set_path(t_data *game, char *line, char *element);

/* exit_fonction.c */
int	err(int nb, char *msg);
int		ft_exit(int nb, char *msg);
void	ft_free(t_data *game);

/* get_next_line.c/ get_next_line_utils.c */
int		ft_strlen(const char *str);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char const *s2);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		size_line(char *strings, int i);
char	*get_next_line(int fd);

/* ft_utils.c */
int		ft_strstr(char *str, char *to_find);
int		ft_strncmp(char *s1, char *s2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
char	*ft_strdup(const char *s);
int		ft_atoi(char *nptr);

/* autre fonction utils */
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_realloc(void *ptr, size_t size);

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


/* verif_wall.c */
int    check_up(char **map, int x, int y);
int    check_down(char **map, int x, int y);
int    check_left(char **map, int x, int y);
int    check_right(char **map, int x, int y);
char    **depth_first_check(char **map, int x, int y);

int	side(char **map, int i, int j);
int	map_is_close(char **map);
int skip_space(char *line);
int get_height(char **map);


/*raycast*/
/*--------------------------------------------------------*/
void	start_game(t_data *game);
int		hook(void *dt);
void	reset_val(t_data *game, int x);
void	calc_step_and_sidedist(t_data *game);
void	dda(t_data *game);
void	raycast(t_data *game);
int		handle_click_end(t_data *game);
int		key_release(int key, void *dt);
int		key_hook(int key, void *dt);
void	init_text_addr(t_data *game);
void	init_text_img(t_data *game);
void	init_game(t_data *game);
void	ft_init_texture(t_data *game);
void	init_direction_n_s(t_data *game);
void	init_direction_e_w(t_data *game);
void	move_cam_left(t_data *game);
void	move_cam_right(t_data *game);
void	move(t_data *game);
void	move_right(t_data *game);
void	move_left(t_data *game);
void	move_down(t_data *game);
void	move_up(t_data *game);
int		pass_to_comas(char *s, int nb);
int		rgb(char *rgb);
t_print	init_print(t_data *game);
void	print_col(t_data *game, int x);

#endif