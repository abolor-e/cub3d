/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmarech <olmarech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:30:03 by olmarech          #+#    #+#             */
/*   Updated: 2024/03/01 19:31:42 by olmarech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	freemaloc(char **result, int delimiter)
{
	int	i;

	i = 0;
	while (i < delimiter)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return ;
}

int	is_sep(char const c, char const sep)
{
	if (c == sep)
		return (1);
	return (0);
}

int	word_count(char const *str, char const sep)
{
	int	i;
	int	valid;
	int	count;

	i = 0;
	valid = 1;
	count = 0;
	while (str[i])
	{
		if (!is_sep(str[i], sep))
		{
			if (valid == 1)
				count++;
			valid = 0;
		}
		else
			valid = 1;
		i++;
	}
	return (count);
}

char	*ft_strdup2(char const *str, int *index, char const sep)
{
	char	*word;
	int		i[2];

	i[0] = 0;
	i[1] = *index;
	while (is_sep(str[i[1]], sep))
		i[1]++;
	*index = i[1];
	while (str[i[1]] && !is_sep(str[i[1]], sep))
	{
		i[1]++;
		i[0]++;
	}
	word = malloc(sizeof(char) * (i[0] + 1));
	if (!word)
		return (NULL);
	word[i[0]] = '\0';
	i[1] = 0;
	while (str[*index] && !is_sep(str[*index], sep))
	{
		word[i[1]] = str[*index];
		i[1]++;
		(*index)++;
	}
	return (word);
}

char	**ft_split(char const *str, char const c)
{
	char	**result;
	int		index;
	int		i;
	int		wc;

	index = 0;
	i = 0;
	wc = word_count(str, c);
	result = malloc(sizeof(char *) * (wc + 1));
	if (!result)
		return (NULL);
	result[wc] = 0;
	while (i < wc)
	{
		result[i] = ft_strdup2(str, &index, c);
		if (result[i] == NULL)
		{
			freemaloc(result, i);
			return (NULL);
		}
		i++;
	}
	return (result);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	int		index;
	char	**split;
	(void)	argc;
	split = ft_split(argv[1], argv[2]);
	index = 0;
	while (split[index])
	{
		printf("%s\n", split[index]);
		index++;
	}
}
*/