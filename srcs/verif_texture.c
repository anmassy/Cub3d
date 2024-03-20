/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:53:33 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/20 16:56:41 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

int ft_strncmp(char *s1, char *s2, size_t n)
{
	while(n--)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		if (*s1 == '\0')
			break;
		s1++;
		s2++;
	}
	return (0);
}

int texture_on_top(t_data *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->val->map[i])
	{
		j = 0;
		while (game->val->map[i][j])
		{
			while (game->val->map[i][j] == ' ')
				j++;
			if (ft_strncmp(game->val->map[i] + j, "NO", 2) &&
				ft_strncmp(game->val->map[i] + j, "SO", 2) &&
				ft_strncmp(game->val->map[i] + j, "EA", 2) &&
				ft_strncmp(game->val->map[i] + j, "WE", 2) &&
				ft_strncmp(game->val->map[i] + j, "F", 1) &&
				ft_strncmp(game->val->map[i] + j, "C", 1) &&
				ft_strncmp(game->val->map[i] + j, "\n", 1))
			{
				printf("%s\n", "les texture ne sont pas au top du fichier ou il y a des caractere genant");
				return (0);
			}
			if (i == game->val->last_row)
			{
				printf("%s\n", "les texture sont bien entreposé au top");
				return (1);	
			}
			i++;
			j = 0;
		}
	}
}

int search_texture(char* word, t_data *game)
{
	int	i;
	int	j;
	int count;

	i = 0;
	count = 0;
	while (game->val->map[i])
	{
		j = 0;
		while (game->val->map[i][j])
		{
			while (game->val->map[i][j] == ' ')
				j++;
			if (ft_strncmp(game->val->map[i] + j, word, ft_strlen(word)) == 0)
			{
				// printf("texture = %s\ni = %d\nj = %d\n", word, i, j);
				count++;
				if (i > game->val->last_row && count == 1)
					game->val->last_row = i;
			}
			if (!game->val->map[i + 1])
			{
				// printf("last_row =%d\n", game->val->last_row);
				if (count != 1)
					return (0);
				return (1);	
			}
			i++;
			j = 0;
		}
	}
	return (1);
}

int all_texture(t_data *game) 
{
	if (search_texture("NO", game) == 0 ||
		search_texture("SO", game) == 0 ||
		search_texture("EA", game) == 0 ||
		search_texture("WE", game) == 0 ||
		search_texture("F", game) == 0 ||
		search_texture("C", game) == 0)
	{
		printf("%s\n", "il manque des textures");
		return (0);
	}
	printf("%s\n", "toute les textures sont presente");
	return (1);
}

int set_first_row(t_data *game)
{
	int	i;
	int	j;

	i = game->val->last_row + 1;
	while (game->val->map[i])
	{
		j = 0;
		while (game->val->map[i][j] || game->val->map[i][j] == '\n')
		{
			if (game->val->map[i][j] != ' ' && game->val->map[i][j] != '\n')
			{
				game->val->first_row = i;
				// printf("%d\n", game->val->first_row);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int verif_texture(t_data *game)
{
	if (all_texture(game) == 0) //permet de savoir si "NO, SO, EA, WE, F, C" sont bien dans le fichier map.
		return (0);
	if (texture_on_top(game) == 0) //permet de savoir si toute les texture son au top du fichier et qu'il n'y a pas de ligne en trop ou defectueuse avec des caractere random
		return (0);
	// pas oublié de verifier si le path de chaque texture exite et est correcte !
	set_first_row(game); //permet de set la premiere ligne ou commence la map
	return (1);
}