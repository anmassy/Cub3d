/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:34:21 by lmarchai          #+#    #+#             */
/*   Updated: 2024/04/03 16:36:04 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	move_cam_right(t_data *game)
{
	double	olddirx;
	double	oldplanex;

	olddirx = game->rayc.dirX;
	game->rayc.dirX = game->rayc.dirX * cos(-game->rayc.rotspeed) - \
		game->rayc.dirY * sin(-game->rayc.rotspeed);
	game->rayc.dirY = olddirx * sin(-game->rayc.rotspeed) + \
		game->rayc.dirY * cos(-game->rayc.rotspeed);
	oldplanex = game->rayc.planeX;
	game->rayc.planeX = game->rayc.planeX * cos(-game->rayc.rotspeed) - \
		game->rayc.planeY * sin(-game->rayc.rotspeed);
	game->rayc.planeY = oldplanex * sin(-game->rayc.rotspeed) + \
		game->rayc.planeY * cos(-game->rayc.rotspeed);
}

void	move_cam_left(t_data *game)
{
	double	olddirx;
	double	oldplanex;

	olddirx = game->rayc.dirX;
	game->rayc.dirX = game->rayc.dirX * cos(game->rayc.rotspeed) - \
		game->rayc.dirY * sin(game->rayc.rotspeed);
	game->rayc.dirY = olddirx * sin(game->rayc.rotspeed) + \
		game->rayc.dirY * cos(game->rayc.rotspeed);
	oldplanex = game->rayc.planeX;
	game->rayc.planeX = game->rayc.planeX * cos(game->rayc.rotspeed) - \
		game->rayc.planeY * sin(game->rayc.rotspeed);
	game->rayc.planeY = oldplanex * sin(game->rayc.rotspeed) + \
		game->rayc.planeY * cos(game->rayc.rotspeed);
}
