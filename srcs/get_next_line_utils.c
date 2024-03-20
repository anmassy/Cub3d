/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmassy <anmassy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:19:42 by anmassy           #+#    #+#             */
/*   Updated: 2024/03/20 13:25:22 by anmassy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3d.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((char)c == s[i])
			return (s + i);
		i++;
	}
	if (c == 0)
		return ((char *)(s + i));
	return (0);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*string;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	string = (char *)malloc ((i + j + 1) * sizeof(*s1));
	if (!string)
		return (free(s1), NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		string[j + i] = s2[j];
		j++;
	}
	string[j + i] = '\0';
	return (free(s1), string);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*strings;
	size_t	size;
	size_t	j;

	size = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (len < (size_t)ft_strlen(s))
		strings = (char *)malloc(sizeof(*s) * (len + 1));
	else
		strings = (char *)malloc(sizeof(*s) * (ft_strlen(s) + 1));
	if (!strings)
		return (NULL);
	while (size != start && s[size])
		size++;
	while (s[size] && j < len)
		strings[j++] = s[size++];
	if (size >= start - 1)
		free(s);
	if (j == 0)
		return (free(strings), NULL);
	strings[j] = '\0';
	return (strings);
}
