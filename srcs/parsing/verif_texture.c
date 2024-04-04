/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:49:17 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/04 15:06:53 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	path_xpm(char *path)
{
	char	s[4];
	int		i;
	int		j;

	i = ft_strlen(path) - 4;
	j = 0;
	while (path[i])
		s[j++] = path[i++];
	if (ft_strncmp(s, ".xpm", 4) == 0)
		return (1);
	return (0);
}

int	all_textures(t_data *game)
{
	if (game->mesh->n_path == NULL)
		return (1);
	if (game->mesh->s_path == NULL)
		return (1);
	if (game->mesh->e_path == NULL)
		return (1);
	if (game->mesh->w_path == NULL)
		return (1);
	if (game->mesh->c_color == NULL)
		return (1);
	if (game->mesh->f_color == NULL)
		return (1);
	return (0);
}

int	cut_path(t_data *game, char *line, int count)
{
	int		j;
	int		element;
	char	*path;
	char	*elements[6] = {"NO", "SO", "EA", "WE", "F", "C"};

	element = find_elements(line);
	j = ft_strstr(line, elements[element]);
	if (line[j] != '\n' && line[j] != '\0' && j == 0)
		ft_exit(1, ERR_ELEMENT);
	path = get_path(line, j);
	if (path != NULL)
	{
		if ((element >= 0 && element <= 3) && (path_xpm(path) == 0
				|| file_exist(path) == 0))
			ft_exit(1, ERR_PATH);
		else if (element >= 4 && valid_color(path) == 0)
			ft_exit(1, ERR_COLOR);
		set_path(game, path, elements[element]);
		count++;
	}
	free(path);
	return (count);
}

void	get_textures(t_data *game, int fd)
{
	char	*temp;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (all_textures(game) != 0)
	{
		temp = get_next_line(fd);
		count = cut_path(game, temp, count);
		free(temp);
		if (count > 6)
			ft_exit(1, ERR_ELEMENT);
		i++;
	}
}
