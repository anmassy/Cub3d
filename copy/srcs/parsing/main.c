/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:16:55 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/03 15:05:05 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	display_map(t_data *game)
{
	int	j;
	int	i;

	i = 0;
	while (game->val->m[i])
	{
		j = 0;
		while (game->val->m[i][j])
		{
			printf("%c", game->val->m[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

#include <string.h>
#include <errno.h>

int main(int ac, char **av)
{
	t_data *game;

	if (ac != 2)
		return (0);
	//check si le fichier exist et si il a le bon nom (.cub)
	if (check_file(av[1]) == 0 || file_exist(av[1]) == 0)
		return (0);
	game = init_struct();
	//convertie la map du fichier .cub et effectue les verif nessessaire avant de passer a l'exec
	convert_map(game, av[1]); 
	if (verif_map(game) == 0)
		return (0);
	display_map(game); //affiche la map
	start_game(game);
	return (0);
}

