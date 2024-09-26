/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olmarech <olmarech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 13:16:00 by olmarech          #+#    #+#             */
/*   Updated: 2024/09/26 16:12:16 by olmarech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	msg_exit(char *error)
{
	int	i;

	i = -1;
	write(1, "\033[1;31mERROR :\033[0m ", 20);
	while (error[++i])
		write(1, &error[i], 1);
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}

int	size_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_exit(t_pars *pars, char **file_content, char *error_msg, int op)
{
	free_pars(pars);
	free_tab(file_content);
	if (op)
		msg_exit(error_msg);
}

void	free_tmp_exit(t_pars *pars, char **file, char *error_msg, char **t)
{
	free_tab(t);
	free(t);
	free_exit(pars, file, error_msg, 1);
}

int	check_duplicate(char **file_content, int i, t_pars *pars)
{
	if ((!ft_strncmp(file_content[i], "NO ", 3) && pars->path_n)
		|| (!ft_strncmp(file_content[i], "SO ", 3) && pars->path_s)
		|| (!ft_strncmp(file_content[i], "EA ", 3) && pars->path_e)
		|| (!ft_strncmp(file_content[i], "WE ", 3) && pars->path_w))
		return (1);
	return (0);
}
