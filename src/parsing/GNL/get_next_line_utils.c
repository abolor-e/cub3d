/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmarech <olmarech@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:47:47 by olmarech          #+#    #+#             */
/*   Updated: 2023/11/20 14:46:51 by olmarech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *str, char *newstr)
{
	char	*result;
	int		i;
	int		j;

	result = malloc((ft_strlen(str) + ft_strlen(newstr) + 1) * sizeof(char));
	if (!result)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (str && str[i] != '\0')
	{
		result[i] = str[i];
		i++;
	}
	while (newstr[j] != '\0')
		result[i++] = newstr[j++];
	result[ft_strlen(str) + ft_strlen(newstr)] = '\0';
	free(str);
	return (result);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (0);
}
