/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:06:37 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/04 15:08:53 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	search_texture(char *word, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strncmp(line + i, word, ft_strlen(word)) == 0)
		return (0);
	return (1);
}

int	find_elements(char *line)
{
	if (search_texture("NO", line) == 0)
		return (NO);
	else if (search_texture("SO", line) == 0)
		return (SO);
	else if (search_texture("EA", line) == 0)
		return (EA);
	else if (search_texture("WE", line) == 0)
		return (WE);
	else if (search_texture("F", line) == 0)
		return (F);
	else if (search_texture("C", line) == 0)
		return (C);
	return (0);
}

int	lenght(char *line, int j)
{
	int	count;

	count = 0;
	while (line[j] != '\n')
	{
		while (line[j] == ' ')
			j++;
		while (line[j] != '\n' && line[j] != ' ')
		{
			count++;
			j++;
		}
		return (count);
	}
	return (0);
}

char	*get_path(char *line, int j)
{
	int		i;
	int		len_path;
	char	*path;

	i = 0;
	len_path = lenght(line, j);
	if (j && len_path == 0)
		ft_exit(1, EMPTY_LINE);
	path = malloc(sizeof(char) * len_path + 2);
	if (!path)
		return (NULL);
	while (line[j] != '\n')
	{
		while (line[j] == ' ')
			j++;
		while (line[j] != '\n' && line[j] != ' ')
			path[i++] = line[j++];
		path[i] = '\0';
		while (line[j] != '\n')
		{
			if (line[j] != ' ')
				ft_exit(1, ERR_PATH);
			j++;
		}
		return (path);
	}
	return (free(path), NULL);
}

void	set_path(t_data *game, char *line, char *element)
{
	if (ft_strncmp(element, "NO", 2) == 0)
		game->mesh->n_path = line;
	else if (ft_strncmp(element, "SO", 2) == 0)
		game->mesh->s_path = line;
	else if (ft_strncmp(element, "EA", 2) == 0)
		game->mesh->e_path = line;
	else if (ft_strncmp(element, "WE", 2) == 0)
		game->mesh->w_path = line;
	else if (ft_strncmp(element, "F", 1) == 0)
		game->mesh->f_color = line;
	else if (ft_strncmp(element, "C", 1) == 0)
		game->mesh->c_color = line;
}
