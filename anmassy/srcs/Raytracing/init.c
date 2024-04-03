/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:29:49 by lmarchai          #+#    #+#             */
/*   Updated: 2024/04/03 16:35:35 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	init_direction_e_w(t_data *game)
{
	if (game->val->orientation == 'E' || game->val->orientation == 'W')
	{
		if (game->val->orientation == 'E')
		{
			game->rayc.dirX = 1.0000001;
			game->rayc.dirY = 0;
		}
		else
		{
			game->rayc.dirX = -1.0000001;
			game->rayc.dirY = 0;
		}
		game->rayc.planeX = 0;
		game->rayc.planeY = 0.66;
	}
	else
		init_direction_n_s(game);
}

void	init_direction_n_s(t_data *game)
{
	if (game->val->orientation == 'N' || game->val->orientation == 'S')
	{
		if (game->val->orientation == 'N')
		{
			game->rayc.dirX = 0;
			game->rayc.dirY = -1.0000001;
		}
		else
		{
			game->rayc.dirX = 0;
			game->rayc.dirY = 1.0000001;
		}
		game->rayc.planeX = 0.66;
		game->rayc.planeY = 0;
	}
}

void	ft_init_texture(t_data *game)
{
	if (game->rayc.side == 0 && game->rayc.rayDirX < 0)
		game->rayc.textDir = 0;
	if (game->rayc.side == 0 && game->rayc.rayDirX >= 0)
		game->rayc.textDir = 1;
	if (game->rayc.side == 1 && game->rayc.rayDirY < 0)
		game->rayc.textDir = 2;
	if (game->rayc.side == 1 && game->rayc.rayDirY >= 0)
		game->rayc.textDir = 3;
	if (game->rayc.side == 0)
		game->rayc.wallX = game->rayc.posY + game->rayc.perpWallDist \
						* game->rayc.rayDirY;
	else
		game->rayc.wallX = game->rayc.posX + game->rayc.perpWallDist \
						* game->rayc.rayDirX;
	game->rayc.wallX -= floor((game->rayc.wallX));
}

void	init_game(t_data *game)
{
	game->rayc.posX = game->val->startX + 0.5;
	game->rayc.posY = game->val->startY + 0.5;
	init_direction_e_w(game);
	game->rayc.movespeed = 0.1;
	game->rayc.rotspeed = 0.03;
	game->img.mlx_img = NULL;
	game->rayc.move_up = 0;
	game->rayc.move_down = 0;
	game->rayc.move_left = 0;
	game->rayc.move_right = 0;
	game->rayc.move_cam_left = 0;
	game->rayc.move_cam_right = 0;
	init_text_img(game);
}
