/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:36:28 by lmarchai          #+#    #+#             */
/*   Updated: 2024/04/03 16:44:28 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	key_hook(int key, void *dt)
{
	t_data	*game;

	game = dt;
	if (key == S)
		game->rayc.move_up = 1;
	if (key == W)
		game->rayc.move_down = 1;
	if (key == A)
		game->rayc.move_left = 1;
	if (key == D)
		game->rayc.move_right = 1;
	if (key == L)
		game->rayc.move_cam_left = 1;
	if (key == R)
		game->rayc.move_cam_right = 1;
	if (key == ESC)
		exit(0);
	return (1);
}

int	key_release(int key, void *dt)
{
	t_data	*game;

	game = dt;
	if (key == S)
		game->rayc.move_up = 0;
	if (key == W)
		game->rayc.move_down = 0;
	if (key == A)
		game->rayc.move_left = 0;
	if (key == D)
		game->rayc.move_right = 0;
	if (key == L)
		game->rayc.move_cam_left = 0;
	if (key == R)
		game->rayc.move_cam_right = 0;
	return (1);
}

int	handle_click_end(t_data *game)
{
	(void) game;
	exit(0);
	return (0);
}
