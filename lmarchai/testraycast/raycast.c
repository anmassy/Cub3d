# include  "../includes/minilibx-linux/mlx.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../includes/minilibx-linux/mlx.h"
# include <math.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1920
#define screenHeight 1080

#define HEX_Red 0xC80707
#define HEX_Green 0x0BB20E
#define HEX_White 0xFFFFFF
#define HEX_Blue 0x186AF1
#define HEX_Yellow 0xF1EE18

typedef struct s_val
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
}	t_val;

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

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_val				val;
	t_img				img;
	t_img				*text;
}	t_data;

void	move(t_data *data);

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

/*
 initialise les valeurs nécessaires pour calculer le lancer de rayons (raycasting). 
 Elle calcule la position et la direction du rayon de la caméra, détermine dans quelle case de la 
 carte se trouve la caméra, initialise les distances des côtés du mur, calcule les longueurs de rayons jusqu'au prochain côté x ou y,
 initialise la distance perpendiculaire au mur, détermine dans quelle direction il faut marcher dans les directions x et y, et initialise
 les variables de détection de collision.
*/

void	reset_val(t_data *data, int x)
{
	/*
		Calcule la coordonnée x de la caméra dans l'espace de la caméra. 
		Cela normalise la position de la caméra sur l'axe x par rapport à la largeur de l'écran, ce qui donne une valeur entre -1 et 1.
	*/
	data->val.cameraX = 2 * x / (double)screenWidth - 1.0;

	/*
		data->val.rayDirX et data->val.rayDirY: Calculent les composantes x et y de la direction du rayon de la caméra. 
		Elles sont calculées en ajoutant un vecteur représentant la direction de la caméra (stocké dans data->val.dirX et data->val.dirY)
		à un vecteur représentant le plan de la caméra (stocké dans data->val.planeX et data->val.planeY), le tout multiplié par la coordonnée x de la caméra.
	*/
	data->val.rayDirX =  data->val.dirX +  data->val.planeX * data->val.cameraX;
	data->val.rayDirY =  data->val.dirY +  data->val.planeY * data->val.cameraX;

	/*
		Détermination de la case de la carte dans laquelle se trouve la caméra
	*/
	data->val.mapX = (int)data->val.posX;
	data->val.mapY = (int)data->val.posY;

	/*
		Initialisation des distances des côtés du mur 
	*/
	data->val.sideDistX = 0;
	data->val.sideDistY = 0;
	/*
		Ces variables calculent les longueurs des rayons en direction des côtés x ou y. 
		Elles sont calculées en prenant le inverse de la direction du rayon pour chaque axe. 
		Si la direction du rayon est nulle pour un axe, une valeur très grande est utilisée pour éviter les divisions par zéro.
	*/
	if (data->val.rayDirX == 0)
		data->val.deltaDistX = 1e30;
	else 
		data->val.deltaDistX = fabs(1 / data->val.rayDirX);
	if (data->val.rayDirY == 0)
		data->val.deltaDistY = 1e30;
	else 
		data->val.deltaDistY = fabs(1 / data->val.rayDirY);
	/*
		Initialisation de la distance perpendiculaire au mur 
	*/
	data->val.perpWallDist = 0;

	/*
		Détermination de la direction de pas dans les axes x et y
	*/
	data->val.stepX = 0;
	data->val.stepY = 0;

	/*
		Initialisation des variables de détection de collision
	*/
	data->val.hit = 0; //was there a wall hit?
	data->val.side = 0;
}

/*
calcule les pas à effectuer dans les directions x et y et les distances des côtés du mur correspondantes.
Elle détermine si les pas sont positifs ou négatifs en fonction de la direction du rayon.
*/

void	calc_step_and_sideDist(t_data *data)
{
	/*
		Si la direction du rayon est négative dans l'axe x, cela signifie que le rayon se dirige vers la gauche sur la carte. Dans ce cas :
	*/
	if (data->val.rayDirX < 0)
	{
		/*
			data->val.stepX est défini à -1, indiquant que le pas dans la direction x sera vers la gauche.
		*/
		data->val.stepX = -1;
		/*
			La distance au côté du mur en x (data->val.sideDistX) est calculée en prenant la différence 
			entre la position actuelle de la caméra en x et la coordonnée x de la case de la carte où se trouve la 
			caméra, puis en multipliant cette différence par la longueur du rayon entre chaque côté du mur (data->val.deltaDistX).
		*/
	  	data->val.sideDistX = (data->val.posX - data->val.mapX) * data->val.deltaDistX;
	}
	else
	{
		/*
			si on vas pas a droite on vas a gauche :)
		*/
	  	data->val.stepX = 1;
	  	data->val.sideDistX = (data->val.mapX + 1.0 - data->val.posX) * data->val.deltaDistX;
	}
	if (data->val.rayDirY < 0)
	{
		/*
			Si la direction du rayon est négative dans l'axe y, le pas dans la direction y (data->val.stepY) est défini à -1 
			et la distance au côté du mur en y (data->val.sideDistY) est calculée en fonction de la position actuelle de la caméra en y.
		*/
		data->val.stepY = -1;
	  	data->val.sideDistY = (data->val.posY - data->val.mapY) * data->val.deltaDistY;
	}
	else
	{
	  	data->val.stepY = 1;
	  	data->val.sideDistY = (data->val.mapY + 1.0 - data->val.posY) * data->val.deltaDistY;
	}
}

/*
Cette fonction implémente l'algorithme DDA (Digital Differential Analyzer) 
pour parcourir la grille de la carte et détecter les intersections avec les murs. 
Elle itère jusqu'à ce qu'un mur soit touché. À chaque itération, elle détermine quelle distance est la plus courte,
celle du côté x ou y, et avance dans cette direction. Elle met à jour les coordonnées de la carte en conséquence et vérifie si le rayon a heurté un mur.

Une fois qu'un mur est touché, elle calcule la distance perpendiculaire au mur en fonction de la distance parcourue dans la direction x ou y.
*/

void	dda(t_data *data)
{
	/*
		tant qu'on touche pas de mur
		on avance de une case a chaque fois
	*/
	while (data->val.hit == 0)
	{
		//soit une case vers la direction X
		if (data->val.sideDistX < data->val.sideDistY)
		{
		  	data->val.sideDistX += data->val.deltaDistX;
		  	data->val.mapX += data->val.stepX;
		  	data->val.side = 0;
		}
		//sinon une case vers la direction Y
		else
		{
		  	data->val.sideDistY += data->val.deltaDistY;
		  	data->val.mapY += data->val.stepY;
		  	data->val.side = 1;
		}
		//on check si on touche le mur
		if (worldMap[data->val.mapX][data->val.mapY] > 0) 
			data->val.hit = 1;
	}
	/*
		Si le côté horizontal était le plus proche (data->val.side == 0), la distance est calculée en soustrayant la distance 
		parcourue en x depuis le dernier côté du mur de la longueur du rayon horizontal (data->val.deltaDistX).
	*/
	if(data->val.side == 0)
		data->val.perpWallDist = (data->val.sideDistX - data->val.deltaDistX);
	/*
		Sinon, si le côté vertical était le plus proche, la distance est calculée de manière similaire en soustrayant 
		la distance parcourue en y depuis le dernier côté du mur de la longueur du rayon vertical (data->val.deltaDistY).
	*/
	else          
		data->val.perpWallDist = (data->val.sideDistY - data->val.deltaDistY);
}

int	choose_wall_color(t_data *data)
{
	if (worldMap[data->val.mapX][data->val.mapY] == 1)
		return (HEX_Red);
	if (worldMap[data->val.mapX][data->val.mapY] == 2)
		return (HEX_Green);
	if (worldMap[data->val.mapX][data->val.mapY] == 3)
		return (HEX_Blue);
	if (worldMap[data->val.mapX][data->val.mapY] == 4)
		return (HEX_White);
	return (HEX_Yellow);
}

//possiblement modif les values pour correspondre a la manière au bon mur
void	ft_init_texture(t_data *data)
{
	/*
		Si le mur touché est sur le côté gauche (data->val.side == 0) et que le rayon se déplace vers la gauche 
		(data->val.rayDirX < 0), la direction de la texture est définie sur 0.
	*/
	if (data->val.side == 0 && data->val.rayDirX < 0)
		data->val.textDir = 0;
	/*
		Si le mur touché est sur le côté droit et que le rayon se déplace vers la droite, la direction de la texture est définie sur 1.
	*/
	if (data->val.side == 0 && data->val.rayDirX >= 0)
		data->val.textDir = 1;
	/*
		Si le mur touché est sur le côté haut (data->val.side == 1) et que le rayon se déplace vers le haut 
		(data->val.rayDirY < 0), la direction de la texture est définie sur 2.
	*/
	if (data->val.side == 1 && data->val.rayDirY < 0)
		data->val.textDir = 2;
	/*
		Si le mur touché est sur le côté bas et que le rayon se déplace vers le bas, la direction de la texture est définie sur 3.
	*/
	if (data->val.side == 1 && data->val.rayDirY >= 0)
		data->val.textDir = 3;
	/*
		Si le mur touché est sur le côté gauche ou droit (data->val.side == 0), la position x du mur sur la texture est calculée en 
		fonction de la position y de la caméra (data->val.posY) et de la distance perpendiculaire au mur (data->val.perpWallDist) 
		multipliée par la direction x du rayon (data->val.rayDirY).
	*/
	if (data->val.side == 0)
		data->val.wallX = data->val.posY + data->val.perpWallDist \
						* data->val.rayDirY;
	/*
		Sinon, si le mur touché est sur le côté haut ou bas, la position x du mur sur la texture est calculée de manière similaire en
		utilisant la position x de la caméra (data->val.posX) et la direction y du rayon (data->val.rayDirX).
	*/
	else
		data->val.wallX = data->val.posX + data->val.perpWallDist \
						* data->val.rayDirX;
	// La position x résultante est normalisée pour qu'elle soit comprise entre 0 et 1 en soustrayant la partie entière de la valeur à sa propre valeur.
	data->val.wallX -= floor((data->val.wallX));
}

void	print_col(t_data *data, int x)
{
	int lineHeight;
	int	drawStart;
	int drawEnd;
	int y;

	y = 0;
	//calculé en fonction de la distance perpendiculaire au mur, ce qui détermine la hauteur de la colonne à dessiner sur l'écran.

	lineHeight = (int)screenHeight / data->val.perpWallDist;
	// déterminent les positions de début et de fin de la colonne à dessiner sur l'écran en fonction de lineHeight

	drawStart = (-1 * lineHeight) / 2 + screenHeight / 2;
	if(drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + screenHeight / 2;
	if (drawEnd >= screenHeight)
		drawEnd = screenHeight - 1;
	//initialisation des textures
	ft_init_texture(data);

	/*
		calculé en fonction de la position où le rayon a frappé le mur. Cela détermine quel pixel de la texture sera 
		utilisé pour dessiner cette partie de la colonne de pixels.
	*/
	data->val.texX = (int)(data->val.wallX * (double)data->text[data->val.textDir].width);
	/*
		Si le mur touché est sur le côté gauche ou droit (data->val.side == 0) et que le rayon se dirige vers la droite 
		(data->val.rayDirX > 0), la position x de la texture est ajustée pour correspondre à la position du mur sur la texture.
	*/
	if(data->val.side == 0 && data->val.rayDirX > 0) 
		data->val.texX = data->text[data->val.textDir].width - data->val.texX - 1;
	/*
		Si le mur touché est sur le côté haut ou bas (data->val.side == 1) et que le rayon se dirige vers le haut 
		(data->val.rayDirY < 0), la position x de la texture est également ajustée.
	*/
	if(data->val.side == 1 && data->val.rayDirY < 0) 
		data->val.texX = data->text[data->val.textDir].width - data->val.texX - 1;
	// step est calculé pour déterminer le pas de variation de la position de la texture le long de la hauteur de la colonne dessinée.
	double step = 1.0 * data->text[data->val.textDir].height / lineHeight;
	// texPos est initialisé en fonction de drawStart pour déterminer où la texture commence le long de la hauteur de la colonne dessinée.
	double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;

	//boucle de rendu
	while (y <= screenHeight)
	{
		if (y >= drawStart && y <= drawEnd)
		{
			int texY = (int)texPos & (data->text[data->val.textDir].height - 1);
			texPos += step;
			int color = data->text[data->val.textDir].addr[texY * data->text[data->val.textDir].line_len / 4 + data->val.texX];
			data->img.addr[y * data->img.line_len / 4 + x] = color;
		}
		else if (y > drawEnd)
			data->img.addr[y * data->img.line_len / 4 + x] = 0xD27030;
		else
			data->img.addr[y * data->img.line_len / 4 + x] = 0x6FC2D3;
		y++;
	}
}

void	raycast(t_data *data)
{
	int i;

	i = 0;
	/*
		boucle sur la taille de l'écran (on fonctionne colone par colone)
	*/
	while (i < screenWidth)
	{
		/*
			on remet toutes les valeurs a 0;
		*/
		reset_val(data, i);
		/*
			calcul de la valeur de déplacement
		*/
		calc_step_and_sideDist(data);
		/*
			cast du rayon
		*/
		dda(data);
		/*
			render
		*/
		print_col(data, i);
		i++;
	}
}


int	hook(void *dt)
{
	t_data *data;

	data = dt;
	/*
		on reset l'image précédente si elle existe
		et on charge la nouvelle
	*/
	if (data->img.mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, screenWidth, screenHeight);
	data->img.addr = (int *)mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);

	//calcul de toutes les values + préparation de l'image a render
	raycast(data);

	//placement de l'image dans la fenetre
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0,0);
	
	//mouvements
	move(data);
	return (0);
}

#define key_up 122
#define key_down 115
#define key_right 100
#define key_left 113
#define key_right_arrow 65363
#define key_left_arrow 65361

void	move(t_data *data)
{
	if (data->val.move_up == 1)
	{
		if(!worldMap[(int)(data->val.posX + data->val.dirX * data->val.movespeed)][(int)data->val.posY])
	  		data->val.posX += data->val.dirX * data->val.movespeed;
	  	if(!worldMap[(int)data->val.posX][(int)( data->val.posY +  data->val.dirY *  data->val.movespeed)]) 
	  		data->val.posY +=  data->val.dirY * data->val.movespeed;
	}
	if (data->val.move_down == 1)
	{
		if(!worldMap[(int)(data->val.posX - data->val.dirX * data->val.movespeed)][(int)data->val.posY])
	  		data->val.posX -= data->val.dirX * data->val.movespeed;
	  	if(!worldMap[(int)data->val.posX][(int)( data->val.posY -  data->val.dirY *  data->val.movespeed)]) 
	  		data->val.posY -=  data->val.dirY *  data->val.movespeed;
	}
	if (data->val.move_left == 1)
	{
		if (!worldMap[(int)(data->val.posX - data->val.dirY * data->val.movespeed)][(int)data->val.posY])
			data->val.posX -= data->val.dirY * data->val.movespeed;
		if (!worldMap[(int)data->val.posX][(int)(data->val.posY + data->val.dirX * data->val.movespeed)]) 
			data->val.posY += data->val.dirX * data->val.movespeed;
	}

	if (data->val.move_right == 1)
	{
		if (!worldMap[(int)(data->val.posX + data->val.dirY * data->val.movespeed)][(int)data->val.posY])
			data->val.posX += data->val.dirY * data->val.movespeed;
		if (!worldMap[(int)data->val.posX][(int)(data->val.posY - data->val.dirX * data->val.movespeed)]) 
			data->val.posY -= data->val.dirX * data->val.movespeed;
	}
	if (data->val.move_cam_right == 1)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->val.dirX;
		data->val.dirX = data->val.dirX * cos(-data->val.rotspeed) - data->val.dirY * sin(-data->val.rotspeed);
		data->val.dirY = oldDirX * sin(-data->val.rotspeed) + data->val.dirY * cos(-data->val.rotspeed);
		double oldPlaneX = data->val.planeX;
		data->val.planeX = data->val.planeX * cos(-data->val.rotspeed) - data->val.planeY * sin(-data->val.rotspeed);
		data->val.planeY = oldPlaneX * sin(-data->val.rotspeed) + data->val.planeY * cos(-data->val.rotspeed);
	}
	if (data->val.move_cam_left == 1)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->val.dirX;
		data->val.dirX = data->val.dirX * cos(data->val.rotspeed) - data->val.dirY * sin(data->val.rotspeed);
		data->val.dirY = oldDirX * sin(data->val.rotspeed) + data->val.dirY * cos(data->val.rotspeed);
		double oldPlaneX = data->val.planeX;
		data->val.planeX = data->val.planeX * cos(data->val.rotspeed) - data->val.planeY * sin(data->val.rotspeed);
		data->val.planeY = oldPlaneX * sin(data->val.rotspeed) + data->val.planeY * cos(data->val.rotspeed);
	}
}

int	key_hook(int key, void *dt)
{
	t_data *data = dt;

	if (key == key_up)
		data->val.move_up = 1;
	if (key == key_down)
		data->val.move_down = 1;
	if (key == key_left)
		data->val.move_left = 1;
	if (key == key_right)
		data->val.move_right = 1;
	if (key == key_left_arrow)
		data->val.move_cam_left = 1;
	if (key == key_right_arrow)
		data->val.move_cam_right = 1;
	return (1);
}

int	key_release(int key, void *dt)
{
	t_data *data = dt;

	if (key == key_up)
		data->val.move_up = 0;
	if (key == key_down)
		data->val.move_down = 0;
	if (key == key_left)
		data->val.move_left = 0;
	if (key == key_right)
		data->val.move_right = 0;
	if (key == key_left_arrow)
		data->val.move_cam_left = 0;
	if (key == key_right_arrow)
		data->val.move_cam_right = 0;
	return (1);
}

int main()
{
	t_data data;

	/*
		initilialisation des valeurs de départs
	*/
	data.val.posX = 22, data.val.posY = 12;
	data.val.dirX = -1, data.val.dirY = 0;
	data.val.planeX = 0, data.val.planeY = 0.66;
	data.val.movespeed = 0.15;
	data.val.rotspeed = 0.03;
	data.img.mlx_img = NULL;
	data.val.move_up = 0;
	data.val.move_down = 0;
	data.val.move_left = 0;
	data.val.move_right = 0;
	data.val.move_cam_left = 0;
	data.val.move_cam_right = 0;

	/*
		initialisation mlx
	*/
	data.mlx_ptr = mlx_init();
	
	/*
		initialisation textures
	*/
	data.text = calloc(4, sizeof(t_img));
	data.text[0].mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "../textures/eagle.xpm", &data.text[0].width, &data.text[0].height);
	data.text[1].mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "../textures/greyscale.xpm", &data.text[1].width, &data.text[1].height);
	data.text[2].mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "../textures/purplestone.xpm", &data.text[2].width, &data.text[2].height);
	data.text[3].mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "../textures/red.xpm", &data.text[3].width, &data.text[3].height);

	data.text[0].addr = (int *)mlx_get_data_addr(data.text[0].mlx_img, &data.text[0].bpp, &data.text[0].line_len, &data.text[0].endian);
	data.text[1].addr = (int *)mlx_get_data_addr(data.text[1].mlx_img, &data.text[1].bpp, &data.text[1].line_len, &data.text[1].endian);
	data.text[2].addr = (int *)mlx_get_data_addr(data.text[2].mlx_img, &data.text[2].bpp, &data.text[2].line_len, &data.text[2].endian);
	data.text[3].addr = (int *)mlx_get_data_addr(data.text[3].mlx_img, &data.text[3].bpp, &data.text[3].line_len, &data.text[3].endian);

	/*
		boucle mlx
	*/
	data.win_ptr = mlx_new_window(data.mlx_ptr, screenWidth, screenHeight, "Cub3d");
	mlx_hook(data.win_ptr, 2, 1L << 0, key_hook, &data);
	mlx_loop_hook(data.mlx_ptr, &hook, &data);
	mlx_hook(data.win_ptr, 3, 1L << 1, key_release, &data);
	mlx_loop(data.mlx_ptr);
}