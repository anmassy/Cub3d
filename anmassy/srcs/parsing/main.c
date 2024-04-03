/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarchai <lmarchai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:16:55 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/03 05:26:52 by lmarchai         ###   ########.fr       */
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
	if (check_file(av[1]) == 0 || file_exist(av[1]) == 0) //check si le fichier exist et si il a le bon nom
		return (0);
	game = init_struct();
	
	convert_map(game, av[1]); //converti la map du fichier .cub dans un buffer 
	if (verif_texture(game) == 0 || verif_map(game) == 0) //effectue les verif nessessaire avant de passer a l'exec
		return (0);
	else
		printf("bravodo\n");
	// for(int i=0; game->val->map[i]; i++)
	// 	free(game->val->map[i]);
	// free(game->val->map);
	// catch_map(game);
	display_map(game); //affiche la map
	start_game(game);
	return (0);
}

