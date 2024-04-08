/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fonction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:07:04 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/08 15:25:15 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	ft_exit(t_data *game, int nb, char *msg)
{
	printf("Error: %s\n", msg);
	ft_free(game);
	exit(nb);
}

int	close_and_free(t_data *game, char *msg)
{
	close(game->fd);
	ft_exit(game, 1, msg);
	return (0);
}

char	*cclose_and_free(t_data *game, char *msg)
{
	close(game->fd);
	ft_exit(game, 1, msg);
	return (0);
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
	if (game->mesh->c_color != NULL)
		free(game->mesh->c_color);
	if (game->mesh->f_color != NULL)
		free(game->mesh->f_color);
	if (game->mesh->n_path != NULL)
		free(game->mesh->n_path);
	if (game->mesh->e_path != NULL)
		free(game->mesh->e_path);
	if (game->mesh->s_path != NULL)
		free(game->mesh->s_path);
	if (game->mesh->w_path != NULL)
		free(game->mesh->w_path);
	if (game->val->m != NULL)
		free_map(game->val->m);
	free(game->val);
	free(game->mesh);
	free(game);
}
