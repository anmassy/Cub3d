/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:29:49 by lmarchai          #+#    #+#             */
/*   Updated: 2024/04/11 00:52:17 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	init_direction_e_w(t_data *game)
{
	printf("%c\n", game->val->orientation);
	if (game->val->orientation == 'W')
		game->rayc.dirx = -1.001001;
	if (game->val->orientation == 'E')
		game->rayc.dirx = 1.001001;
	if (game->val->orientation == 'S')
		game->rayc.diry = 1.001001;
	if (game->val->orientation == 'N')
		game->rayc.diry = -1.001001;
	if (game->val->orientation == 'W')
		game->rayc.planey = 0.66;
	if (game->val->orientation == 'E')
		game->rayc.planey = -0.66;
	if (game->val->orientation == 'S')
		game->rayc.planex = 0.66;
	if (game->val->orientation == 'N')
		game->rayc.planex = -0.66;
}

void	ft_init_texture(t_data *game)
{
	if (game->rayc.side == 0 && game->rayc.raydirx < 0)
		game->rayc.textdir = 0;
	if (game->rayc.side == 0 && game->rayc.raydirx >= 0)
		game->rayc.textdir = 1;
	if (game->rayc.side == 1 && game->rayc.raydiry < 0)
		game->rayc.textdir = 3;
	if (game->rayc.side == 1 && game->rayc.raydiry >= 0)
		game->rayc.textdir = 2;
	if (game->rayc.side == 0)
		game->rayc.wallx = game->rayc.posy + game->rayc.perpwalldist \
						* game->rayc.raydiry;
	else
		game->rayc.wallx = game->rayc.posx + game->rayc.perpwalldist \
						* game->rayc.raydirx;
	game->rayc.wallx -= floor((game->rayc.wallx));
}

void	init_game(t_data *game)
{
	game->rayc.dirx = 0;
	game->rayc.diry = 0;
	game->rayc.planex = 0;
	game->rayc.planey = 0;
	game->rayc.posx = game->val->startx + 0.5;
	game->rayc.posy = game->val->starty + 0.5;
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
