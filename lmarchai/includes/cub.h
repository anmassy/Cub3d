/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:08:00 by lmarchai          #+#    #+#             */
/*   Updated: 2024/03/27 07:20:05 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../includes/minilibx-linux/mlx.h"
# include "../libft/header/libft.h"
# include  "minilibx-linux/mlx.h"
# include <math.h>

#define M_PI       3.14159265358979323846

# define ERRARG_NB "Error : arg is empty\n"
# define ERRARG_EXT "Error : Extension is not right should be .cub\n"
# define ERROPEN "Error : open returned -1\n"
# define ERRALLOC "Error : allocation failed\n"
# define ERRORMAP "Error : Map Error\n"

# define NO_TX "NO"
# define SO_TX "SO"
# define WE_TX "WE"
# define EA_TX "EA"
# define FLO_COL "F"
# define CEL_COL "C"

# define S_W 1900 // largeur de l'écran
# define S_H 1000 // hauteur de l'écran
# define TILE_SIZE 30 // taille des tuiles
# define FOV 60 // champ de vision
# define focal_len (S_W / 2) / tan(fov / 2); //distance focale
# define ROTATION_SPEED 0,045 // vitesse de rotation
# define PLAYER_SPEED 4 // vitesse du joueur
#define DEG_TO_RAD(angle_deg) ((angle_deg) * M_PI / 180.0)

typedef enum { false, true } bool;

typedef struct s_text
{
	char 	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
}			t_text;

typedef struct s_textures
{
	
} t_textures;

typedef struct s_pos
{
	int x;
	int y;
}		t_pos;

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

typedef struct s_map
{
    char **map;
    bool 	N;
	bool	S;
	bool	E;
	bool	W;
	bool	is_valid;
	struct s_text *t;
	struct s_pos start;
	int 	*size_x;
	int 	size_y;
}			t_map;

typedef  struct  s_player {
	// le  structure du joueur  
double   plyr_x; 
double   plyr_y;
double 	angle ; // angle du joueur 
float 	fov_rd; // champ de vision en radians 
int   	rot; // indicateur de rotation 
int   	l_r; // drapeau gauche droite 
int   	u_d; // drapeau haut vers le bas
} t_player; 

typedef  struct  s_ray { // la  structure des rayons  

 	double	ray_ngl; // angle de rayon 
 	double	distance ; // distance au mur 
 	char	direction;
	double	ray_x;
	double	ray_y;
} t_ray;

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	int					screenX;
	int					screenY;
	t_map				*map;
	t_player  			*ply;
	t_ray				*ray;
	t_img				img;
	t_img				wall_img;
}	t_data;

void	free_map(char **map);
bool all_textures(struct s_map *m);

struct s_map	*parsing(char *av);
void			*ft_realloc(void *ptr, size_t size);
struct s_map	*fit_texture(struct s_map*m, char *s);
struct s_map	*get_textures(struct s_map *m, int fd);
t_map			depth_first_check(t_map map, t_pos pos);
bool 			check_dfs(t_map map);
bool 			check_text_files(char *s);
bool 			check_entry(struct s_map *m);
struct s_map 	*check_start(struct s_map *m, char *s, int y);
char 			*pass_blank(char *temp, int fd);
struct s_map 	*init_map(void);
char 			**dup_map(char **map, int i);
struct s_map	 *store_map(int fd);
struct s_map	*input_size_map(struct s_map *m);
t_data			init_data(t_data *data, t_map *map);
t_data			*init_player(t_data *data);

int				handle_keypress(int keysym, t_data *data);
int				handle_click_end(t_data *data);
double			nor_angle(double angle);
void			render_wall(t_data *mlx, int ray);
t_data 			*cast_rays(t_data *data);
#endif