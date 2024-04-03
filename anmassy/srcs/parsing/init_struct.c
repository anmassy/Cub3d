/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:16:08 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/03 04:45:41 by lmarchai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	set_null(t_data *game)
{
	game->val->m = NULL;
    game->val->first_row = 0;
    game->val->last_row = 0;
    game->val->orientation = 0;
	game->val->height = 0;
	game->val->x = 0;
	game->val->y = 0;
}

void	set_null2(t_data *game)
{
    game->mesh->n_path = NULL;
	game->mesh->s_path = NULL;
	game->mesh->e_path = NULL;
	game->mesh->w_path = NULL;
    game->mesh->c_color = NULL;
    game->mesh->f_color = NULL;
}

t_data	*init_struct(void)
{
	t_data	*game;

	game = malloc(sizeof(t_data));
	if (!game)
		return (NULL);
	game->val = malloc(sizeof(t_player)); 
	if (!game->val)
	{
		free(game);
		return (NULL);
	}
	game->mesh = malloc(sizeof(t_texture)); 
	if (!game->mesh)
	{
		free(game);
		return (NULL);
	}
	set_null(game);
	set_null2(game);
	return (game);
}