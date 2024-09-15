/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmarech <olmarech@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:46:02 by olmarech          #+#    #+#             */
/*   Updated: 2023/11/20 14:46:04 by olmarech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_fullstr(int fd, char *str)
{
	char	newstr[BUFFER_SIZE + 1];
	int		rd_bytes;

	rd_bytes = 1;
	while (!ft_strchr(str, '\n') && rd_bytes > 0)
	{
		rd_bytes = read(fd, newstr, BUFFER_SIZE);
		if (rd_bytes < 0)
		{
			free(str);
			return (NULL);
		}
		newstr[rd_bytes] = '\0';
		str = ft_strjoin(str, newstr);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	*get_the_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		line = malloc((i + 2) * sizeof(char));
	else
		line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*clear_old_str(char *str)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str || !str[i])
	{
		free(str);
		return (NULL);
	}
	newstr = malloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!newstr)
	{
		free(str);
		return (NULL);
	}
	j = 0;
	i++;
	while (str[i])
		newstr[j++] = str[i++];
	newstr[j] = '\0';
	free(str);
	return (newstr);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = ft_fullstr(fd, str);
	if (!str)
		return (NULL);
	line = get_the_line(str);
	if (!line)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	if (!line[0])
	{
		free(str);
		free(line);
		str = NULL;
		return (NULL);
	}
	str = clear_old_str(str);
	return (line);
}
