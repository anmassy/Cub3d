/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fonction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:07:04 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/04 14:20:27 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	ft_exit(int nb, char *msg)
{
	printf("Error: %s\n", msg);
	//ajouter des free en plus
	exit(nb);
}

int	err(int nb, char *msg)
{
	printf("Error: %s\n", msg);
	exit(nb);
}

void	free_map(t_data *game)
{
	int	i;

	i = 0;
	while (game->val->m[i])
		free(game->val->m[i++]);
	free(game->val->m);
}

void	ft_free(t_data *game)
{
	free_map(game);
	free(game->val);
	free(game->mesh);
	free(game);
}