/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:16:55 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/28 13:34:31 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

void	display_map(t_data *game)
{
	int	j;
	int	i;

	i = 0;
	while (game->val->map[i])
	{
		j = 0;
		while (game->val->map[i][j])
		{
			printf("%c ", game->val->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

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
	display_map(game); //affiche la map
	// create_window(game);
	return (0);
}

