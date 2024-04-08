/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:31:56 by lmarchai          #+#    #+#             */
/*   Updated: 2024/04/08 15:49:22 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	reset_val(t_data *game, int x)
{
	game->rayc.camerax = 2 * x / (double)SCREENWIDTH - 1.0;
	game->rayc.raydirx = game->rayc.dirx \
		+ game->rayc.planex * game->rayc.camerax;
	game->rayc.raydiry = game->rayc.diry \
		+ game->rayc.planey * game->rayc.camerax;
	game->rayc.mapx = (int)game->rayc.posx;
	game->rayc.mapy = (int)game->rayc.posy;
	game->rayc.sidedistx = 0;
	game->rayc.sidedisty = 0;
	if (game->rayc.raydirx == 0)
		game->rayc.deltadistx = 1e30;
	else
		game->rayc.deltadistx = fabs(1 / game->rayc.raydirx);
	if (game->rayc.raydiry == 0)
		game->rayc.deltadisty = 1e30;
	else
		game->rayc.deltadisty = fabs(1 / game->rayc.raydiry);
	game->rayc.perpwalldist = 0;
	game->rayc.stepx = 0;
	game->rayc.stepy = 0;
	game->rayc.hit = 0;
	game->rayc.side = 0;
}

void	calc_step_and_sidedist(t_data *game)
{
	if (game->rayc.raydirx < 0)
	{
		game->rayc.stepx = -1;
		game->rayc.sidedistx = (game->rayc.posx \
			- game->rayc.mapx) * game->rayc.deltadistx;
	}
	else
	{
		game->rayc.stepx = 1;
		game->rayc.sidedistx = (game->rayc.mapx + 1.0 \
			- game->rayc.posx) * game->rayc.deltadistx;
	}
	if (game->rayc.raydiry < 0)
	{
		game->rayc.stepy = -1;
		game->rayc.sidedisty = (game->rayc.posy \
			- game->rayc.mapy) * game->rayc.deltadisty;
	}
	else
	{
		game->rayc.stepy = 1;
		game->rayc.sidedisty = (game->rayc.mapy + 1.0 \
			- game->rayc.posy) * game->rayc.deltadisty;
	}
}

void	dda(t_data *game)
{
	while (game->rayc.hit == 0)
	{
		if (game->rayc.sidedistx < game->rayc.sidedisty)
		{
			game->rayc.sidedistx += game->rayc.deltadistx;
			game->rayc.mapx += game->rayc.stepx;
			game->rayc.side = 0;
		}
		else
		{
			game->rayc.sidedisty += game->rayc.deltadisty;
			game->rayc.mapy += game->rayc.stepy;
			game->rayc.side = 1;
		}
		if (game->val->m[game->rayc.mapy][game->rayc.mapx] == '1')
			game->rayc.hit = 1;
	}
	if (game->rayc.side == 0)
		game->rayc.perpwalldist = (game->rayc.sidedistx \
			- game->rayc.deltadistx);
	else
		game->rayc.perpwalldist = (game->rayc.sidedisty \
			- game->rayc.deltadisty);
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
