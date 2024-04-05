/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:31:56 by lmarchai          #+#    #+#             */
/*   Updated: 2024/04/05 19:36:44 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	reset_val(t_data *game, int x)
{
	game->rayc.cameraX = 2 * x / (double)SCREENWIDTH - 1.0;
	game->rayc.rayDirX = game->rayc.dirX \
		+ game->rayc.planeX * game->rayc.cameraX;
	game->rayc.rayDirY = game->rayc.dirY \
		+ game->rayc.planeY * game->rayc.cameraX;
	game->rayc.mapX = (int)game->rayc.posX;
	game->rayc.mapY = (int)game->rayc.posY;
	game->rayc.sideDistX = 0;
	game->rayc.sideDistY = 0;
	if (game->rayc.rayDirX == 0)
		game->rayc.deltaDistX = 1e30;
	else
		game->rayc.deltaDistX = fabs(1 / game->rayc.rayDirX);
	if (game->rayc.rayDirY == 0)
		game->rayc.deltaDistY = 1e30;
	else
		game->rayc.deltaDistY = fabs(1 / game->rayc.rayDirY);
	game->rayc.perpWallDist = 0;
	game->rayc.stepX = 0;
	game->rayc.stepY = 0;
	game->rayc.hit = 0;
	game->rayc.side = 0;
}

void	calc_step_and_sidedist(t_data *game)
{
	if (game->rayc.rayDirX < 0)
	{
		game->rayc.stepX = -1;
		game->rayc.sideDistX = (game->rayc.posX \
			- game->rayc.mapX) * game->rayc.deltaDistX;
	}
	else
	{
		game->rayc.stepX = 1;
		game->rayc.sideDistX = (game->rayc.mapX + 1.0 \
			- game->rayc.posX) * game->rayc.deltaDistX;
	}
	if (game->rayc.rayDirY < 0)
	{
		game->rayc.stepY = -1;
		game->rayc.sideDistY = (game->rayc.posY \
			- game->rayc.mapY) * game->rayc.deltaDistY;
	}
	else
	{
		game->rayc.stepY = 1;
		game->rayc.sideDistY = (game->rayc.mapY + 1.0 \
			- game->rayc.posY) * game->rayc.deltaDistY;
	}
}

void	dda(t_data *game)
{
	while (game->rayc.hit == 0)
	{
		if (game->rayc.sideDistX < game->rayc.sideDistY)
		{
			game->rayc.sideDistX += game->rayc.deltaDistX;
			game->rayc.mapX += game->rayc.stepX;
			game->rayc.side = 0;
		}
		else
		{
			game->rayc.sideDistY += game->rayc.deltaDistY;
			game->rayc.mapY += game->rayc.stepY;
			game->rayc.side = 1;
		}
		if (game->val->m[game->rayc.mapY][game->rayc.mapX] == '1')
			game->rayc.hit = 1;
	}
	if (game->rayc.side == 0)
		game->rayc.perpWallDist = (game->rayc.sideDistX \
			- game->rayc.deltaDistX);
	else
		game->rayc.perpWallDist = (game->rayc.sideDistY \
			- game->rayc.deltaDistY);
}

void	raycast(t_data *game)
{
	int	i;

	i = 0;
	while (i < SCREENWIDTH)
	{
		reset_val(game, i);
		calc_step_and_sidedist(game);
		dda(game);
		print_col(game, i);
		i++;
	}
}
