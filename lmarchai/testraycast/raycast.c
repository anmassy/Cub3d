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

void	reset_val(t_data *data, int x)
{
	//calculate ray position and direction
    data->val.cameraX = 2 * x / (double)screenWidth - 1.0; //x-coordinate in camera space
    data->val.rayDirX =  data->val.dirX +  data->val.planeX * data->val.cameraX;
    data->val.rayDirY =  data->val.dirY +  data->val.planeY * data->val.cameraX;

    //which box of the map we're in
    data->val.mapX = (int)data->val.posX;
    data->val.mapY = (int)data->val.posY;

	data->val.sideDistX = 0;
    data->val.sideDistY = 0;

    //length of ray from current position to next x or y-side
	if (data->val.rayDirX == 0)
    	data->val.deltaDistX = 1e30;
	else 
		data->val.deltaDistX = fabs(1 / data->val.rayDirX);
	if (data->val.rayDirY == 0)
    	data->val.deltaDistY = 1e30;
	else 
		data->val.deltaDistY = fabs(1 / data->val.rayDirY);
	
	data->val.perpWallDist = 0;

	data->val.stepX = 0;
    data->val.stepY = 0;
    //what direction to step in x or y-direction (either +1 or -1)
    data->val.hit = 0; //was there a wall hit?
	data->val.side = 0;
}

void	calc_step_and_sideDist(t_data *data)
{
	if (data->val.rayDirX < 0)
    {
		data->val.stepX = -1;
      	data->val.sideDistX = (data->val.posX - data->val.mapX) * data->val.deltaDistX;
    }
    else
    {
      	data->val.stepX = 1;
      	data->val.sideDistX = (data->val.mapX + 1.0 - data->val.posX) * data->val.deltaDistX;
    }
    if (data->val.rayDirY < 0)
    {
    	data->val.stepY = -1;
      	data->val.sideDistY = (data->val.posY - data->val.mapY) * data->val.deltaDistY;
    }
    else
    {
      	data->val.stepY = 1;
      	data->val.sideDistY = (data->val.mapY + 1.0 - data->val.posY) * data->val.deltaDistY;
    }
}

void	dda(t_data *data)
{
	while (data->val.hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
        if (data->val.sideDistX < data->val.sideDistY)
        {
          data->val.sideDistX += data->val.deltaDistX;
          data->val.mapX += data->val.stepX;
          data->val.side = 0;
        }
        else
        {
          data->val.sideDistY += data->val.deltaDistY;
          data->val.mapY += data->val.stepY;
          data->val.side = 1;
        }
        //Check if ray has hit a wall
        if (worldMap[data->val.mapX][data->val.mapY] > 0) 
			data->val.hit = 1;
	}
	if(data->val.side == 0) 
		data->val.perpWallDist = (data->val.sideDistX - data->val.deltaDistX);
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

void	ft_init_texture(t_data *data)
{
	if (data->val.side == 0 && data->val.rayDirX < 0)
		data->val.textDir = 0;
	if (data->val.side == 0 && data->val.rayDirX >= 0)
		data->val.textDir = 1;
	if (data->val.side == 1 && data->val.rayDirY < 0)
		data->val.textDir = 2;
	if (data->val.side == 1 && data->val.rayDirY >= 0)
		data->val.textDir = 3;
	if (data->val.side == 0)
		data->val.wallX = data->val.posY + data->val.perpWallDist \
						* data->val.rayDirY;
	else
		data->val.wallX = data->val.posX + data->val.perpWallDist \
						* data->val.rayDirX;
	data->val.wallX -= floor((data->val.wallX));
}

void	print_col(t_data *data, int x)
{
	int lineHeight;
	int	drawStart;
	int drawEnd;
	int y;

	y = 0;
	lineHeight = (int)screenHeight / data->val.perpWallDist;
	drawStart = (-1 * lineHeight) / 2 + screenHeight / 2;
	if(drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + screenHeight / 2;
	if (drawEnd >= screenHeight)
		drawEnd = screenHeight - 1;
	ft_init_texture(data);
	data->val.texX = (int)(data->val.wallX * (double)data->text[data->val.textDir].width);
	if(data->val.side == 0 && data->val.rayDirX > 0) 
		data->val.texX = data->text[data->val.textDir].width - data->val.texX - 1;
    if(data->val.side == 1 && data->val.rayDirY < 0) 
		data->val.texX = data->text[data->val.textDir].width - data->val.texX - 1;
	double step = 1.0 * data->text[data->val.textDir].height / lineHeight;
	double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
	while (y <= screenHeight)
	{
		if (y > drawStart && y < drawEnd)
		{
			int texY = (int)texPos & (data->text[data->val.textDir].height - 1);
			texPos += step;
			int color = data->text[data->val.textDir].addr[texY * data->text[data->val.textDir].line_len / 4 + data->val.texX];
			data->img.addr[y * data->img.line_len / 4 + x] = color;
		}
		else
			data->img.addr[y * data->img.line_len / 4 + x] = 0xffffff;
		y++;
	}
}

void	raycast(t_data *data)
{
	int i;

	i = 0;
	while (i < screenWidth)
	{
		reset_val(data, i);
		calc_step_and_sideDist(data);
		dda(data);
		print_col(data, i);
		i++;
	}
}

int	hook(void *dt)
{
	t_data *data;

	data = dt;
	if (data->img.mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, screenWidth, screenHeight);
	data->img.addr = (int *)mlx_get_data_addr(data->img.mlx_img, &data->img.bpp, &data->img.line_len, &data->img.endian);
	raycast(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0,0);
	return (0);
}

#define key_up 122
#define key_down 115
#define key_right 65363
#define key_left 65361

int	key_hook(int key, void *dt)
{
	t_data *data;

	data = dt;
	if (key == key_up)
    {
		if(!worldMap[(int)(data->val.posX + data->val.dirX * data->val.movespeed)][(int)data->val.posY])
	  		data->val.posX += data->val.dirX * data->val.movespeed;
      	if(!worldMap[(int)data->val.posX][(int)( data->val.posY +  data->val.dirY *  data->val.movespeed)]) 
	  		data->val.posY +=  data->val.dirY *  data->val.movespeed;
    }
	if (key == key_down)
    {
		if(!worldMap[(int)(data->val.posX - data->val.dirX * data->val.movespeed)][(int)data->val.posY])
	  		data->val.posX -= data->val.dirX * data->val.movespeed;
      	if(!worldMap[(int)data->val.posX][(int)( data->val.posY -  data->val.dirY *  data->val.movespeed)]) 
	  		data->val.posY -=  data->val.dirY *  data->val.movespeed;
    }
	if (key == key_right)
    {
    	//both camera direction and camera plane must be rotated
    	double oldDirX = data->val.dirX;
    	data->val.dirX = data->val.dirX * cos(-data->val.rotspeed) - data->val.dirY * sin(-data->val.rotspeed);
    	data->val.dirY = oldDirX * sin(-data->val.rotspeed) + data->val.dirY * cos(-data->val.rotspeed);
    	double oldPlaneX = data->val.planeX;
    	data->val.planeX = data->val.planeX * cos(-data->val.rotspeed) - data->val.planeY * sin(-data->val.rotspeed);
    	data->val.planeY = oldPlaneX * sin(-data->val.rotspeed) + data->val.planeY * cos(-data->val.rotspeed);
    }
	if (key == key_left)
    {
    	//both camera direction and camera plane must be rotated
    	double oldDirX = data->val.dirX;
    	data->val.dirX = data->val.dirX * cos(data->val.rotspeed) - data->val.dirY * sin(data->val.rotspeed);
    	data->val.dirY = oldDirX * sin(data->val.rotspeed) + data->val.dirY * cos(data->val.rotspeed);
    	double oldPlaneX = data->val.planeX;
    	data->val.planeX = data->val.planeX * cos(data->val.rotspeed) - data->val.planeY * sin(data->val.rotspeed);
    	data->val.planeY = oldPlaneX * sin(data->val.rotspeed) + data->val.planeY * cos(data->val.rotspeed);
    }
	return (1);
}

int main()
{
	t_data data;

	data.val.posX = 22, data.val.posY = 12; //x and y start position
	data.val.dirX = -1, data.val.dirY = 0; //initial direction vector
	data.val.planeX = 0, data.val.planeY = 0.66; //the 2d raycaster version of camera plane
	data.val.movespeed = 0.5;
	data.val.rotspeed = 0.3;
	data.img.mlx_img = NULL;

	data.mlx_ptr = mlx_init();
	
	data.text = calloc(4, sizeof(t_img));
	data.text[0].mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "../textures/eagle.xpm", &data.text[0].width, &data.text[0].height);
	data.text[1].mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "../textures/greyscale.xpm", &data.text[1].width, &data.text[1].height);
	data.text[2].mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "../textures/purplestone.xpm", &data.text[2].width, &data.text[2].height);
	data.text[3].mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "../textures/red.xpm", &data.text[3].width, &data.text[3].height);

	data.text[0].addr = (int *)mlx_get_data_addr(data.text[0].mlx_img, &data.text[0].bpp, &data.text[0].line_len, &data.text[0].endian);
	data.text[1].addr = (int *)mlx_get_data_addr(data.text[1].mlx_img, &data.text[1].bpp, &data.text[1].line_len, &data.text[1].endian);
	data.text[2].addr = (int *)mlx_get_data_addr(data.text[2].mlx_img, &data.text[2].bpp, &data.text[2].line_len, &data.text[2].endian);
	data.text[3].addr = (int *)mlx_get_data_addr(data.text[3].mlx_img, &data.text[3].bpp, &data.text[3].line_len, &data.text[3].endian);

	data.win_ptr = mlx_new_window(data.mlx_ptr, screenWidth, screenHeight, "Cub3d");
	mlx_loop_hook(data.mlx_ptr, &hook, &data);
	mlx_key_hook(data.win_ptr, &key_hook, &data);
	mlx_loop(data.mlx_ptr);
}