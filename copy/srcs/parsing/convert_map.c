/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:32:23 by anmassy           #+#    #+#             */
/*   Updated: 2024/04/03 14:33:45 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Cub3d.h"
#include <string.h>

char	*pass_blank(char *temp, int fd)
{
	while (ft_strlen(temp) < 2)
	{
		temp = get_next_line(fd);
	}
	return (temp);
}

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

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!src || !dst || n == 0)
		return (ft_strlen(src));
	while (i < n - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	len;

	len = ft_strlen(s);
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, len + 1);
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = dest;
	s = src;
	while (n--)
		*d++ = *s++;
	return (dest);
}


void	*ft_memset(void *s, int c, size_t n)
{
	long unsigned int	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if ((nmemb * size) == 0)
		return (malloc(0));
	if ((nmemb * size) < nmemb)
		return (0);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = ft_calloc(size, '1');
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}

char	**dup_map(char **map, int i)
{
	char	**tmp_map;

	tmp_map = 0;
	tmp_map = ft_realloc(map, sizeof(char *) * (i + 1));
	if (!tmp_map)
		exit (1); //exit clean
	tmp_map[i + 1] = 0;
	map = tmp_map;
	return (map);
}

void	check_char(t_player *m, char c)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != '0' && c != '1' && c != ' ' && c != '\n')
		exit (1); //wrong char clean exit
	if ((c == 'N' || c == 'S' || c == 'E' || c == 'W') && m->orientation != 0)
		exit (1); //plusieurs player
}

struct s_player	*check_start(struct s_player *m, char *s, int y)
{
	int	i;

	i = 0;
	while (s[i])
	{
		check_char(m, s[i]);
		if (s[i] == 'N' || s[i] == 'S' || s[i] == 'E' || s[i] == 'W')
		{
			m->startY = (double)y;
			m->startX = (double)i;
		}
		if (s[i] == 'N')
			m->orientation = 'N';
		if (s[i] == 'S')
			m->orientation = 'S';
		if (s[i] == 'E')
			m->orientation = 'E';
		if (s[i] == 'W')
			m->orientation = 'W';
		i++;
	}
	return (m);
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
            return (close(fd), 1);
		else
			return (close (fd), 0);
	}
	else
		return (0);
}

void	convert_map(t_data *game, char *av)
{
	int		fd;
	char	*buf;
	int		i;

	i = 0;
	fd = open(av, O_RDONLY);
	game->val->m = NULL;
	if (fd == -1)
		ft_exit(1, ERR_FILE); //exit clean + check si c'est pas un directory
	get_textures(game, fd);
	buf = get_next_line(fd);
	buf = pass_blank(buf, fd);
	while (buf != NULL)
	{
		if (ft_strlen(buf) > 1)
		{
			game->val->m = dup_map(game->val->m, i);
			game->val->m[i] = ft_strdup(buf);
			if (!game->val->m[i])
				exit (1); //exit clean
		}
		game->val = check_start(game->val, game->val->m[i], i);
		free(buf);
		buf = get_next_line(fd);
		i++;
	}
	close(fd);
}