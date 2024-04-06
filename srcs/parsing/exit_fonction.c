/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fonction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:07:04 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/06 14:15:16 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	ft_exit(int nb, char *msg)
{
	printf("Error: %s\n", msg);
	/*ajouter des free en plus*/
	//ft_free(game);
	exit(nb);
}

int	err(int nb, char *msg)
{
	printf("Error: %s\n", msg);
	exit(nb);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	ft_free(t_data *game)
{
	free_map(game->val->m);
	free(game->val);
	free(game->mesh);
	free(game);
}
