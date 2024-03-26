/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:12:27 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/22 21:54:52 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int destroy_map(t_data *game)
{
	mlx_destroy_window(game->img->mlx, game->img->window);
	mlx_destroy_display(game->img->mlx);
	exit(0); //evite de segfault
}

int	find_key(int key, t_data *game)
{
	if (key == ESC)
		destroy_map(game);
	return (1);
}

void create_window(t_data *game)
{
    game->img->mlx = mlx_init();
    if (!game->img->mlx)
        printf("error init");
    game->img->window = mlx_new_window(game->img->mlx, 200, 200, "Cub3d");
    if (!game->img->window)
        printf("error window");
    mlx_hook(game->img->window, 33, 0L, destroy_map, game); //gere la croix
    mlx_key_hook(game->img->window, find_key, game); //gere le echap
    mlx_loop(game->img->mlx); // permet que la fenetre reste en faisant une boucle
}