/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:34:21 by lmarchai          #+#    #+#             */
/*   Updated: 2024/04/08 15:47:37 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	move_cam_right(t_data *game)
{
	double	olddirx;
	double	oldplanex;

	olddirx = game->rayc.dirx;
	game->rayc.dirx = game->rayc.dirx * cos(-game->rayc.rotspeed) - \
		game->rayc.diry * sin(-game->rayc.rotspeed);
	game->rayc.diry = olddirx * sin(-game->rayc.rotspeed) + \
		game->rayc.diry * cos(-game->rayc.rotspeed);
	oldplanex = game->rayc.planex;
	game->rayc.planex = game->rayc.planex * cos(-game->rayc.rotspeed) - \
		game->rayc.planey * sin(-game->rayc.rotspeed);
	game->rayc.planey = oldplanex * sin(-game->rayc.rotspeed) + \
		game->rayc.planey * cos(-game->rayc.rotspeed);
}

void	move_cam_left(t_data *game)
{
	double	olddirx;
	double	oldplanex;

	olddirx = game->rayc.dirx;
	game->rayc.dirx = game->rayc.dirx * cos(game->rayc.rotspeed) - \
		game->rayc.diry * sin(game->rayc.rotspeed);
	game->rayc.diry = olddirx * sin(game->rayc.rotspeed) + \
		game->rayc.diry * cos(game->rayc.rotspeed);
	oldplanex = game->rayc.planex;
	game->rayc.planex = game->rayc.planex * cos(game->rayc.rotspeed) - \
		game->rayc.planey * sin(game->rayc.rotspeed);
	game->rayc.planey = oldplanex * sin(game->rayc.rotspeed) + \
		game->rayc.planey * cos(game->rayc.rotspeed);
}
