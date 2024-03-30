/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:32:23 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/30 17:14:10 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"

int	len_doc(char *av)
{
	int		len;
	char	c;
	int		fd;

	len = 1;
	fd = open (av, O_RDONLY);
	while (read (fd, &c, 1) > 0)
	{
		if (c == '\n')
			len++;
	}
	close(fd);
	return (len);
}

int	count_line(char *av, t_data *game)
{
	char	c;
	int		fd;

	fd = open (av, O_RDONLY);
	while (read (fd, &c, 1) > 0)
	{
		if (c == '\n')
			game->val->height++;
	}
	close(fd);
	return (game->val->height);
}

void	convert_map(t_data *game, char *av)
{
	int		fd;
	// char	*line;
	int		i;

	i = 0;
	// len = len_doc(av);
	// count_line(av, game);
	// game->val->map = malloc((len + 1) * sizeof(char *));
	// if (!game->val->map)
		// return ;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		exit(0); //exit clean + check si c'est pas un directory
	get_textures(game, fd);
	// line = get_next_line(fd);
// 	while (line)
	// {
		// game->val->map[i] = line;
		// game->val->map[i][ft_strlen(line)] = '\0';
		// i++;
		// line = get_next_line(fd);
	// }
	// game->val->map[i-1] = ft_strjoin(game->val->map[i - 1], "\n");
	// game->val->map[i] = NULL;
	close(fd);
}

#include <string.h>

/*void catch_map(t_data *game)
{
	int i = game->val->first_row;
	int j;
	int k;

	k = 0;
	game->val->m = malloc(sizeof(char *) * game->val->y + 2);
	if (!game->val->m)
		exit (0);
	while (game->val->map[i])
	{
		j = 0;
		printf("%d %p\n", k, game->val->m[k]);
		game->val->m[k] = malloc(sizeof(char) * ft_strlen(game->val->map[i] + 2));
		while(game->val->map[i][j] != '\0')
		{
			game->val->m[k][j] = game->val->map[i][j];
			j++;
		}
		game->val->m[k][j] = '\0';
		k++;
		i++;
	}
}*/

/*char    **dup_map(char **map, int i)
{
    char    **tmp_map;

    tmp_map = realloc(map, sizeof(char *) * (i + 2));
    if (!tmp_map)
    {
        printf("ERRORALLOC");
        return (NULL);
    }
    tmp_map[i + 1] = 0;
    map = tmp_map;
    return (map);
}

struct s_map    *store_map(int fd)
{
    struct s_map    *m;
    int                i;
    char            *temp;

    i = 0;
    m = init_map();
    m = get_textures(m, fd);
    temp = ft_get_next_line(fd);
    if (!m || all_textures(m) != true)
        return (ft_printf(2, "ERROR : textures\n"), NULL);
    temp = pass_blank(temp, fd);
    while (1)
    {
        if (temp == NULL)
            break ;
        if (ft_strlen(temp) > 1)
        {
            m->map = dup_map(m->map, i);
            m->map[i] = ft_strdup(temp);
            if (!m->map[i])
                return (free_map(m->map), NULL);
        }
        m = check_start(m, m->map[i], i);
        free(temp);
        temp = ft_get_next_line(fd);
        i++;
    }
    return (m);
}*/

int	check_file(char *av)
{
	char	s[4];
	int		i;
	int		j;

	i = ft_strlen(av) - 4;
	j = 0;
	while (av[i])
		s[j++] = av[i++];
	if (ft_strncmp(s, ".cub", 4) == 0)
		return (1);
	printf("the file must be a .cub\n");
	return (0);
}

int file_exist(char *path)
{
    int fd;
    char buffer;
	ssize_t bytes_read;

    fd = open(path , O_RDONLY);
    if (fd != -1)
	{
        bytes_read = read(fd, &buffer, 1);
        if (bytes_read > 0)
		{
            close(fd);
            return (1);
        }
		else
		{
			printf("the file is empty\n");
            close(fd);
            return (0);
        }
    }
	else
	{
		printf("invalid path\n");
    	return (0);
	}
}