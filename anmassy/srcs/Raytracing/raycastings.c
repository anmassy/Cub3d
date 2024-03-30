# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include "../../includes/Cub3d.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 1920
#define screenHeight 1080

#define HEX_Red 0xC80707
#define HEX_Green 0x0BB20E
#define HEX_White 0xFFFFFF
#define HEX_Blue 0x186AF1
#define HEX_Yellow 0xF1EE18

void	move(t_data *game);

/*
 initialise les valeurs nécessaires pour calculer le lancer de rayons (raycasting). 
 Elle calcule la position et la direction du rayon de la caméra, détermine dans quelle case de la 
 carte se trouve la caméra, initialise les distances des côtés du mur, calcule les longueurs de rayons jusqu'au prochain côté x ou y,
 initialise la distance perpendiculaire au mur, détermine dans quelle direction il faut marcher dans les directions x et y, et initialise
 les variables de détection de collision.
*/

void	reset_val(t_data *game, int x)
{
	/*
		Calcule la coordonnée x de la caméra dans l'espace de la caméra. 
		Cela normalise la position de la caméra sur l'axe x par rapport à la largeur de l'écran, ce qui donne une valeur entre -1 et 1.
	*/
	game->rayc.cameraX = 2 * x / (double)screenWidth - 1.0;

	/*
		game->rayc.rayDirX et game->rayc.rayDirY: Calculent les composantes x et y de la direction du rayon de la caméra. 
		Elles sont calculées en ajoutant un vecteur représentant la direction de la caméra (stocké dans game->rayc.dirX et game->rayc.dirY)
		à un vecteur représentant le plan de la caméra (stocké dans game->rayc.planeX et game->rayc.planeY), le tout multiplié par la coordonnée x de la caméra.
	*/
	game->rayc.rayDirX =  game->rayc.dirX +  game->rayc.planeX * game->rayc.cameraX;
	game->rayc.rayDirY =  game->rayc.dirY +  game->rayc.planeY * game->rayc.cameraX;

	/*
		Détermination de la case de la carte dans laquelle se trouve la caméra
	*/
	game->rayc.mapX = (int)game->rayc.posX;
	game->rayc.mapY = (int)game->rayc.posY;

	/*
		Initialisation des distances des côtés du mur 
	*/
	game->rayc.sideDistX = 0;
	game->rayc.sideDistY = 0;
	/*
		Ces variables calculent les longueurs des rayons en direction des côtés x ou y. 
		Elles sont calculées en prenant le inverse de la direction du rayon pour chaque axe. 
		Si la direction du rayon est nulle pour un axe, une valeur très grande est utilisée pour éviter les divisions par zéro.
	*/
	if (game->rayc.rayDirX == 0)
		game->rayc.deltaDistX = 1e30;
	else 
		game->rayc.deltaDistX = fabs(1 / game->rayc.rayDirX);
	if (game->rayc.rayDirY == 0)
		game->rayc.deltaDistY = 1e30;
	else 
		game->rayc.deltaDistY = fabs(1 / game->rayc.rayDirY);
	/*
		Initialisation de la distance perpendiculaire au mur 
	*/
	game->rayc.perpWallDist = 0;

	/*
		Détermination de la direction de pas dans les axes x et y
	*/
	game->rayc.stepX = 0;
	game->rayc.stepY = 0;

	/*
		Initialisation des variables de détection de collision
	*/
	game->rayc.hit = 0; //was there a wall hit?
	game->rayc.side = 0;
}

/*
calcule les pas à effectuer dans les directions x et y et les distances des côtés du mur correspondantes.
Elle détermine si les pas sont positifs ou négatifs en fonction de la direction du rayon.
*/

void	calc_step_and_sideDist(t_data *game)
{
	/*
		Si la direction du rayon est négative dans l'axe x, cela signifie que le rayon se dirige vers la gauche sur la carte. Dans ce cas :
	*/
	if (game->rayc.rayDirX < 0)
	{
		/*
			game->rayc.stepX est défini à -1, indiquant que le pas dans la direction x sera vers la gauche.
		*/
		game->rayc.stepX = -1;
		/*
			La distance au côté du mur en x (game->rayc.sideDistX) est calculée en prenant la différence 
			entre la position actuelle de la caméra en x et la coordonnée x de la case de la carte où se trouve la 
			caméra, puis en multipliant cette différence par la longueur du rayon entre chaque côté du mur (game->rayc.deltaDistX).
		*/
	  	game->rayc.sideDistX = (game->rayc.posX - game->rayc.mapX) * game->rayc.deltaDistX;
	}
	else
	{
		/*
			si on vas pas a gauche on vas a droite :)
		*/
	  	game->rayc.stepX = 1;
	  	game->rayc.sideDistX = (game->rayc.mapX + 1.0 - game->rayc.posX) * game->rayc.deltaDistX;
	}
	if (game->rayc.rayDirY < 0)
	{
		/*
			Si la direction du rayon est négative dans l'axe y, le pas dans la direction y (game->rayc.stepY) est défini à -1 
			et la distance au côté du mur en y (game->rayc.sideDistY) est calculée en fonction de la position actuelle de la caméra en y.
		*/
		game->rayc.stepY = -1;
	  	game->rayc.sideDistY = (game->rayc.posY - game->rayc.mapY) * game->rayc.deltaDistY;
	}
	else
	{
	  	game->rayc.stepY = 1;
	  	game->rayc.sideDistY = (game->rayc.mapY + 1.0 - game->rayc.posY) * game->rayc.deltaDistY;
	}
}

/*
Cette fonction implémente l'algorithme DDA (Digital Differential Analyzer) 
pour parcourir la grille de la carte et détecter les intersections avec les murs. 
Elle itère jusqu'à ce qu'un mur soit touché. À chaque itération, elle détermine quelle distance est la plus courte,
celle du côté x ou y, et avance dans cette direction. Elle met à jour les coordonnées de la carte en conséquence et vérifie si le rayon a heurté un mur.

Une fois qu'un mur est touché, elle calcule la distance perpendiculaire au mur en fonction de la distance parcourue dans la direction x ou y.
*/

void	dda(t_data *game)
{
	/*
		tant qu'on touche pas de mur
		on avance de une case a chaque fois
	*/
	while (game->rayc.hit == 0)
	{
		//soit une case vers la direction X
		if (game->rayc.sideDistX < game->rayc.sideDistY)
		{
		  	game->rayc.sideDistX += game->rayc.deltaDistX;
		  	game->rayc.mapX += game->rayc.stepX;
		  	game->rayc.side = 0;
		}
		//sinon une case vers la direction Y
		else
		{
		  	game->rayc.sideDistY += game->rayc.deltaDistY;
		  	game->rayc.mapY += game->rayc.stepY;
		  	game->rayc.side = 1;
		}
		//on check si on touche le mur
		if (game->val->map[game->rayc.mapX][game->rayc.mapY] > 0) 
			game->rayc.hit = 1;
	}
	/*
		Si le côté horizontal était le plus proche (game->rayc.side == 0), la distance est calculée en soustrayant la distance 
		parcourue en x depuis le dernier côté du mur de la longueur du rayon horizontal (game->rayc.deltaDistX).
	*/
	if(game->rayc.side == 0)
		game->rayc.perpWallDist = (game->rayc.sideDistX - game->rayc.deltaDistX);
	/*
		Sinon, si le côté vertical était le plus proche, la distance est calculée de manière similaire en soustrayant 
		la distance parcourue en y depuis le dernier côté du mur de la longueur du rayon vertical (game->rayc.deltaDistY).
	*/
	else          
		game->rayc.perpWallDist = (game->rayc.sideDistY - game->rayc.deltaDistY);
}

int	choose_wall_color(t_data *game)
{
	if (game->val->map[game->rayc.mapX][game->rayc.mapY] == 1)
		return (HEX_Red);
	if (game->val->map[game->rayc.mapX][game->rayc.mapY] == 2)
		return (HEX_Green);
	if (game->val->map[game->rayc.mapX][game->rayc.mapY] == 3)
		return (HEX_Blue);
	if (game->val->map[game->rayc.mapX][game->rayc.mapY] == 4)
		return (HEX_White);
	return (HEX_Yellow);
}

//possiblement modif les values pour correspondre a la manière au bon mur
void	ft_init_texture(t_data *game)
{
	/*
		Si le mur touché est sur le côté gauche (game->rayc.side == 0) et que le rayon se déplace vers la gauche 
		(game->rayc.rayDirX < 0), la direction de la texture est définie sur 0.
	*/
	if (game->rayc.side == 0 && game->rayc.rayDirX < 0)
		game->rayc.textDir = 0;
	/*
		Si le mur touché est sur le côté droit et que le rayon se déplace vers la droite, la direction de la texture est définie sur 1.
	*/
	if (game->rayc.side == 0 && game->rayc.rayDirX >= 0)
		game->rayc.textDir = 1;
	/*
		Si le mur touché est sur le côté haut (game->rayc.side == 1) et que le rayon se déplace vers le haut 
		(game->rayc.rayDirY < 0), la direction de la texture est définie sur 2.
	*/
	if (game->rayc.side == 1 && game->rayc.rayDirY < 0)
		game->rayc.textDir = 2;
	/*
		Si le mur touché est sur le côté bas et que le rayon se déplace vers le bas, la direction de la texture est définie sur 3.
	*/
	if (game->rayc.side == 1 && game->rayc.rayDirY >= 0)
		game->rayc.textDir = 3;
	/*
		Si le mur touché est sur le côté gauche ou droit (game->rayc.side == 0), la position x du mur sur la texture est calculée en 
		fonction de la position y de la caméra (game->rayc.posY) et de la distance perpendiculaire au mur (game->rayc.perpWallDist) 
		multipliée par la direction x du rayon (game->rayc.rayDirY).
	*/
	if (game->rayc.side == 0)
		game->rayc.wallX = game->rayc.posY + game->rayc.perpWallDist \
						* game->rayc.rayDirY;
	/*
		Sinon, si le mur touché est sur le côté haut ou bas, la position x du mur sur la texture est calculée de manière similaire en
		utilisant la position x de la caméra (game->rayc.posX) et la direction y du rayon (game->rayc.rayDirX).
	*/
	else
		game->rayc.wallX = game->rayc.posX + game->rayc.perpWallDist \
						* game->rayc.rayDirX;
	// La position x résultante est normalisée pour qu'elle soit comprise entre 0 et 1 en soustrayant la partie entière de la valeur à sa propre valeur.
	game->rayc.wallX -= floor((game->rayc.wallX));
}

void	print_col(t_data *game, int x)
{
	int lineHeight;
	int	drawStart;
	int drawEnd;
	int y;

	y = 0;
	//calculé en fonction de la distance perpendiculaire au mur, ce qui détermine la hauteur de la colonne à dessiner sur l'écran.

	lineHeight = (int)screenHeight / game->rayc.perpWallDist;
	// déterminent les positions de début et de fin de la colonne à dessiner sur l'écran en fonction de lineHeight

	drawStart = (-1 * lineHeight) / 2 + screenHeight / 2;
	if(drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + screenHeight / 2;
	if (drawEnd >= screenHeight)
		drawEnd = screenHeight - 1;
	//initialisation des textures
	ft_init_texture(game);

	/*
		calculé en fonction de la position où le rayon a frappé le mur. Cela détermine quel pixel de la texture sera 
		utilisé pour dessiner cette partie de la colonne de pixels.
	*/
	game->rayc.texX = (int)(game->rayc.wallX * (double)game->text[game->rayc.textDir].width);
	/*
		Si le mur touché est sur le côté gauche ou droit (game->rayc.side == 0) et que le rayon se dirige vers la droite 
		(game->rayc.rayDirX > 0), la position x de la texture est ajustée pour correspondre à la position du mur sur la texture.
	*/
	if(game->rayc.side == 0 && game->rayc.rayDirX > 0) 
		game->rayc.texX = game->text[game->rayc.textDir].width - game->rayc.texX - 1;
	/*
		Si le mur touché est sur le côté haut ou bas (game->rayc.side == 1) et que le rayon se dirige vers le haut 
		(game->rayc.rayDirY < 0), la position x de la texture est également ajustée.
	*/
	if(game->rayc.side == 1 && game->rayc.rayDirY < 0) 
		game->rayc.texX = game->text[game->rayc.textDir].width - game->rayc.texX - 1;
	// step est calculé pour déterminer le pas de variation de la position de la texture le long de la hauteur de la colonne dessinée.
	double step = 1.0 * game->text[game->rayc.textDir].height / lineHeight;
	// texPos est initialisé en fonction de drawStart pour déterminer où la texture commence le long de la hauteur de la colonne dessinée.
	double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;

	//boucle de rendu
	while (y <= screenHeight)
	{
		if (y >= drawStart && y <= drawEnd)
		{
			int texY = (int)texPos & (game->text[game->rayc.textDir].height - 1);
			texPos += step;
			int color = game->text[game->rayc.textDir].addr[texY * game->text[game->rayc.textDir].line_len / 4 + game->rayc.texX];
			game->img.addr[y * game->img.line_len / 4 + x] = color;
		}
		else if (y > drawEnd)
			game->img.addr[y * game->img.line_len / 4 + x] = 0xD27030; //a recup
		else
			game->img.addr[y * game->img.line_len / 4 + x] = 0x6FC2D3; //a recup
		y++;
	}
}

void	raycast(t_data *game)
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
		reset_val(game, i);
		/*
			calcul de la valeur de déplacement
		*/
		calc_step_and_sideDist(game);
		/*
			cast du rayon
		*/
		dda(game);
		/*
			render
		*/
		print_col(game, i);
		i++;
	}
}


int	hook(void *dt)
{
	t_data *game;

	game = dt;
	/*
		on reset l'image précédente si elle existe
		et on charge la nouvelle
	*/
	if (game->img.mlx_img)
		mlx_destroy_image(game->mlx_ptr, game->img.mlx_img);
	game->img.mlx_img = mlx_new_image(game->mlx_ptr, screenWidth, screenHeight);
	game->img.addr = (int *)mlx_get_data_addr(game->img.mlx_img, &game->img.bpp, &game->img.line_len, &game->img.endian);

	//calcul de toutes les values + préparation de l'image a render
	raycast(game);

	//placement de l'image dans la fenetre
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.mlx_img, 0,0);
	
	//mouvements
	move(game);
	return (0);
}

#define key_up 122
#define key_down 115
#define key_right 100
#define key_left 113
#define key_right_arrow 65363
#define key_left_arrow 65361

void	move(t_data *game)
{
	if (game->rayc.move_up == 1)
	{
		if(!game->val->map[(int)(game->rayc.posX + game->rayc.dirX * game->rayc.movespeed)][(int)game->rayc.posY])
	  		game->rayc.posX += game->rayc.dirX * game->rayc.movespeed;
	  	if(!game->val->map[(int)game->rayc.posX][(int)( game->rayc.posY +  game->rayc.dirY *  game->rayc.movespeed)]) 
	  		game->rayc.posY +=  game->rayc.dirY * game->rayc.movespeed;
	}
	if (game->rayc.move_down == 1)
	{
		if(!game->val->map[(int)(game->rayc.posX - game->rayc.dirX * game->rayc.movespeed)][(int)game->rayc.posY])
	  		game->rayc.posX -= game->rayc.dirX * game->rayc.movespeed;
	  	if(!game->val->map[(int)game->rayc.posX][(int)( game->rayc.posY -  game->rayc.dirY *  game->rayc.movespeed)]) 
	  		game->rayc.posY -=  game->rayc.dirY *  game->rayc.movespeed;
	}
	if (game->rayc.move_left == 1)
	{
		if (!game->val->map[(int)(game->rayc.posX - game->rayc.dirY * game->rayc.movespeed)][(int)game->rayc.posY])
			game->rayc.posX -= game->rayc.dirY * game->rayc.movespeed;
		if (!game->val->map[(int)game->rayc.posX][(int)(game->rayc.posY + game->rayc.dirX * game->rayc.movespeed)]) 
			game->rayc.posY += game->rayc.dirX * game->rayc.movespeed;
	}

	if (game->rayc.move_right == 1)
	{
		if (!game->val->map[(int)(game->rayc.posX + game->rayc.dirY * game->rayc.movespeed)][(int)game->rayc.posY])
			game->rayc.posX += game->rayc.dirY * game->rayc.movespeed;
		if (!game->val->map[(int)game->rayc.posX][(int)(game->rayc.posY - game->rayc.dirX * game->rayc.movespeed)]) 
			game->rayc.posY -= game->rayc.dirX * game->rayc.movespeed;
	}
	if (game->rayc.move_cam_right == 1)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = game->rayc.dirX;
		game->rayc.dirX = game->rayc.dirX * cos(-game->rayc.rotspeed) - game->rayc.dirY * sin(-game->rayc.rotspeed);
		game->rayc.dirY = oldDirX * sin(-game->rayc.rotspeed) + game->rayc.dirY * cos(-game->rayc.rotspeed);
		double oldPlaneX = game->rayc.planeX;
		game->rayc.planeX = game->rayc.planeX * cos(-game->rayc.rotspeed) - game->rayc.planeY * sin(-game->rayc.rotspeed);
		game->rayc.planeY = oldPlaneX * sin(-game->rayc.rotspeed) + game->rayc.planeY * cos(-game->rayc.rotspeed);
	}
	if (game->rayc.move_cam_left == 1)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = game->rayc.dirX;
		game->rayc.dirX = game->rayc.dirX * cos(game->rayc.rotspeed) - game->rayc.dirY * sin(game->rayc.rotspeed);
		game->rayc.dirY = oldDirX * sin(game->rayc.rotspeed) + game->rayc.dirY * cos(game->rayc.rotspeed);
		double oldPlaneX = game->rayc.planeX;
		game->rayc.planeX = game->rayc.planeX * cos(game->rayc.rotspeed) - game->rayc.planeY * sin(game->rayc.rotspeed);
		game->rayc.planeY = oldPlaneX * sin(game->rayc.rotspeed) + game->rayc.planeY * cos(game->rayc.rotspeed);
	}
}

int	key_hook(int key, void *dt)
{
	t_data *game = dt;

	if (key == key_up)
		game->rayc.move_up = 1;
	if (key == key_down)
		game->rayc.move_down = 1;
	if (key == key_left)
		game->rayc.move_left = 1;
	if (key == key_right)
		game->rayc.move_right = 1;
	if (key == key_left_arrow)
		game->rayc.move_cam_left = 1;
	if (key == key_right_arrow)
		game->rayc.move_cam_right = 1;
	return (1);
	/*
	if (key == esc)
		exit(0);
	*/
}

int	key_release(int key, void *dt)
{
	t_data *game = dt;

	if (key == key_up)
		game->rayc.move_up = 0;
	if (key == key_down)
		game->rayc.move_down = 0;
	if (key == key_left)
		game->rayc.move_left = 0;
	if (key == key_right)
		game->rayc.move_right = 0;
	if (key == key_left_arrow)
		game->rayc.move_cam_left = 0;
	if (key == key_right_arrow)
		game->rayc.move_cam_right = 0;
	return (1);
}

#include <errno.h>

void	start_game(t_data *game)
{

	/*
		initilialisation des valeurs de départs
	*/
	game->rayc.posX = 10, game->rayc.posY = 10; //a recup
	game->rayc.dirX = -1, game->rayc.dirY = 0; // a recup en fonction de la direction du joueur au depart
	game->rayc.planeX = 0, game->rayc.planeY = 0.66; //osef c'est le fov
	game->rayc.movespeed = 0.15;
	game->rayc.rotspeed = 0.03;
	game->img.mlx_img = NULL;
	game->rayc.move_up = 0;
	game->rayc.move_down = 0;
	game->rayc.move_left = 0;
	game->rayc.move_right = 0;
	game->rayc.move_cam_left = 0;
	game->rayc.move_cam_right = 0;

	/*
		initialisation mlx
	*/
	game->mlx_ptr = mlx_init();
	
	/*
		initialisation textures
	*/

	//tout ca a recup 
	game->text = calloc(4, sizeof(t_img));
	if (!game->text)
	{
		printf("no alloc");
		exit(1);
	}
	game->text[0].mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, "textures/eagle.xpm", &game->text[0].width, &game->text[0].height);
	if (!game->text[0].mlx_img)
	{
		printf("no img 0");
		exit(1);
	}
	game->text[1].mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, "textures/greyscale.xpm", &game->text[1].width, &game->text[1].height);
	if (!game->text[1].mlx_img)
	{
		printf("no img 1");
		exit(1);
	}
	game->text[2].mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, "textures/purplestone.xpm", &game->text[2].width, &game->text[2].height);
	if (!game->text[2].mlx_img)
	{
		printf("no img 2");
		exit(1);
	}
	game->text[3].mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, "textures/red.xpm", &game->text[3].width, &game->text[3].height);
	if (!game->text[3].mlx_img)
	{
		printf("no img 3");
		exit(1);
	}
	game->text[0].addr = (int *)mlx_get_data_addr(game->text[0].mlx_img, &game->text[0].bpp, &game->text[0].line_len, &game->text[0].endian);
	game->text[1].addr = (int *)mlx_get_data_addr(game->text[1].mlx_img, &game->text[1].bpp, &game->text[1].line_len, &game->text[1].endian);
	game->text[2].addr = (int *)mlx_get_data_addr(game->text[2].mlx_img, &game->text[2].bpp, &game->text[2].line_len, &game->text[2].endian);
	game->text[3].addr = (int *)mlx_get_data_addr(game->text[3].mlx_img, &game->text[3].bpp, &game->text[3].line_len, &game->text[3].endian);

	/*
		boucle mlx
	*/
	game->win_ptr = mlx_new_window(game->mlx_ptr, screenWidth, screenHeight, "Cub3d");
	mlx_hook(game->win_ptr, 2, 1L << 0, key_hook, game);
	mlx_loop_hook(game->mlx_ptr, &hook, game);
	mlx_hook(game->win_ptr, 3, 1L << 1, key_release, game);
	mlx_loop(game->mlx_ptr);
}