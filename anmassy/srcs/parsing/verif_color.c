/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:06:11 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/30 17:48:09 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

// char	*cut_color(t_data *game, int line, char *element)
// {
// 	char *path;
// 	int i;
// 	int j;
// 	int len;

// 	i = 0;
// 	j = ft_strstr(game->val->map[line], element);
// 	len = lenght(game, line, j);
// 	path = malloc(sizeof(char) * len + 2);
// 	while (game->val->map[line][j] != '\n')
// 	{
// 		while (game->val->map[line][j] == ' ')
// 			j++;
// 		while (game->val->map[line][j] != '\n' && game->val->map[line][j] != ' ')
// 			path[i++] = game->val->map[line][j++];
// 		while (game->val->map[line][j] != '\n')
// 		{
// 			if (game->val->map[line][j] != ' ')
// 				return("INVALID LINE");
// 			j++;
// 		}
// 		path[i] = '\0';
// 		return (path);
// 	}
// 	return (NULL);
// }
			
int color_lenght(char *line, int pos)
{
	int i;

	i = 0;
	while (line[pos] != ',' && line[pos] != '\0')
	{
		if ((line[pos] >= '0' && line[pos] <= '9') || line[i] == '-')
			i++;
		pos++;
	}
	return (i);
}

int range_color(int nb)
{
	if (nb == -2147483648)
		return (0);
	else if (nb >= 0 && nb <= 255)
		return (1);
	printf("out of range\n");
	return (0);
}

int comma(char *line)
{
	int i;

	i = 0;
	if (line[0] == ',' || line[ft_strlen(line) - 1] == ',')
	{
		printf("comma at beginning or end of line\n");
		return(0);
	}
	while (line[i])
	{
		if (line[i] == ',' && line[i + 1] == ',')
		{
			printf("error, consecutive commas\n");
			return(0);
		}
		i++;
	}
	return (1);
}

int	ft_atoi(char *nptr)
{
	int	sign;
	int	nb;
	int	i;

	sign = 1;
	nb = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (sign * nb);
}

int	valid_color(char *line) //la fonction qui sert a egardr si on est bien entre 0 et 255
{
	char *temp;
	int number_of_number;
	int i;
	int j;

	number_of_number = 0;
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		j = 0;
		temp = malloc(sizeof(char) * color_lenght(line, i) + 2);
		if (comma(line) == 0)
			return (0);
		while (line[i] != '\0' && line[i] != ',')
		{
			if ((line[i] >= '0' && line[i] <= '9') || line[i] == '-')
			{
				temp[j++] = line[i++];
			}
			else
			{
				printf("there are indesirable characters\n");
				return (0);
			}
		}
		temp[j] = '\0';
		number_of_number++;
		j = ft_atoi(temp);
		if (range_color(j) == 0)
			return (0);
		free(temp);
		if (number_of_number == 3)
			return (1);
	   	i++;
	}
	return (0);
}

// int verif_color(t_data *game)
// {
// 	game->mesh->floor_pigmentation = cut_color(game, game->mesh->floor_line, "F");
// 	game->mesh->ceiling_pigmentation = cut_color(game, game->mesh->ceiling_line, "C");
// 	if (valid_color(game->mesh->ceiling_pigmentation) == 0 ||
// 		valid_color(game->mesh->floor_pigmentation) == 0)
// 		return (0);
// 	return (1);
// }
