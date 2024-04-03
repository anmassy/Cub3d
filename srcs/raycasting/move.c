/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:34:26 by lmarchai          #+#    #+#             */
/*   Updated: 2024/04/03 16:35:25 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	move_up(t_data *game)
{
	if (game->val->m[(int)(game->rayc.posY + game->rayc.dirY * \
		game->rayc.movespeed)][(int)game->rayc.posX] != '1')
		game->rayc.posY += game->rayc.dirY * game->rayc.movespeed;
	if (game->val->m[(int)game->rayc.posY][(int)(game->rayc.posX + \
		game->rayc.dirX * game->rayc.movespeed)] != '1')
		game->rayc.posX += game->rayc.dirX * game->rayc.movespeed;
}

void	move_down(t_data *game)
{
	if (game->val->m[(int)(game->rayc.posY - game->rayc.dirY * \
		game->rayc.movespeed)][(int)game->rayc.posX] != '1')
		game->rayc.posY -= game->rayc.dirY * game->rayc.movespeed;
	if (game->val->m[(int)game->rayc.posY][(int)(game->rayc.posX - \
		game->rayc.dirX * game->rayc.movespeed)] != '1')
		game->rayc.posX -= game->rayc.dirX * game->rayc.movespeed;
}

void	move_left(t_data *game)
{
	if (game->val->m[(int)(game->rayc.posY + game->rayc.dirX * \
		game->rayc.movespeed)][(int)game->rayc.posX] != '1')
		game->rayc.posY += game->rayc.dirX * game->rayc.movespeed;
	if (game->val->m[(int)game->rayc.posY][(int)(game->rayc.posX - \
		game->rayc.dirY * game->rayc.movespeed)] != '1')
		game->rayc.posX -= game->rayc.dirY * game->rayc.movespeed;
}

void	move_right(t_data *game)
{
	if (game->val->m[(int)(game->rayc.posY - game->rayc.dirX * \
		game->rayc.movespeed)][(int)game->rayc.posX] != '1')
		game->rayc.posY -= game->rayc.dirX * game->rayc.movespeed;
	if (game->val->m[(int)game->rayc.posY][(int)(game->rayc.posX + \
		game->rayc.dirY * game->rayc.movespeed)] != '1')
		game->rayc.posX += game->rayc.dirY * game->rayc.movespeed;
}

void	move(t_data *game)
{
	if (game->rayc.move_up == 1)
		move_up(game);
	if (game->rayc.move_down == 1)
		move_down(game);
	if (game->rayc.move_left == 1)
		move_left(game);
	if (game->rayc.move_right == 1)
		move_right(game);
	if (game->rayc.move_cam_right == 1)
		move_cam_right(game);
	if (game->rayc.move_cam_left == 1)
		move_cam_left(game);
}
