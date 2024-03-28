/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:32:23 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/28 13:32:52 by anmassy          ###   ########.fr       */
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
	char	*line;
	int		len;
	int		i;

	i = 0;
	len = len_doc(av);
	count_line(av, game);
	game->val->map = (char **)malloc((len + 1) * sizeof(char *));
	if (!game->val->map)
		return ;
	fd = open(av, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		game->val->map[i] = line;
		i++;
		line = get_next_line(fd);
	}
	game->val->map[i] = NULL;
	close(fd);
}

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