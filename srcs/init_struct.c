/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:16:08 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/20 17:53:21 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

void	set_null(t_data *game)
{
	game->val->map = NULL;
    game->val->first_row = 0;
    game->val->last_row = 0;
    // game->val->orientation = NULL;
	game->val->height = 0;   
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
	set_null(game);
	return (game);
}