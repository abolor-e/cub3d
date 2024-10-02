/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainparsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:39:43 by olmarech          #+#    #+#             */
/*   Updated: 2024/10/02 17:44:46 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	parse_texture(t_pars *pars, char **file_content)
{
	int	i;
	int	error;

	i = -1;
	error = 0;
	while (file_content[++i])
	{
		if (!ft_strncmp(file_content[i], "NO ", 3) && !pars->path_n)
			pars->path_n = ft_strdup(file_content[i] + 3);
		else if (!ft_strncmp(file_content[i], "SO ", 3) && !pars->path_s)
			pars->path_s = ft_strdup(file_content[i] + 3);
		else if (!ft_strncmp(file_content[i], "EA ", 3) && !pars->path_e)
			pars->path_e = ft_strdup(file_content[i] + 3);
		else if (!ft_strncmp(file_content[i], "WE ", 3) && !pars->path_w)
			pars->path_w = ft_strdup(file_content[i] + 3);
		else if (check_duplicate(file_content, i, pars))
			error = 1;
		if (error == 1)
			free_exit(pars, file_content, "Duplicate texture.", 1);
	}
}

void	parse_cf_rgb(t_pars *pars, char **file_content)
{
	char	**tmp;
	int		i;

	i = -1;
	while (file_content[++i])
	{
		if (!ft_strncmp(file_content[i], "F ", 2) && pars->f_rgb[0] == -1)
		{
			tmp = ft_split(file_content[i] + 2, ',');
			if (size_tab(tmp) != 3)
				free_tmp_exit(pars, file_content, "Bad RGB info.", tmp);
			init_rgb(pars, tmp, 1, file_content);
		}
		else if (!ft_strncmp(file_content[i], "C ", 2) && pars->c_rgb[0] == -1)
		{
			tmp = ft_split(file_content[i] + 2, ',');
			if (size_tab(tmp) != 3)
				free_tmp_exit(pars, file_content, "Bad RGB info.", tmp);
			init_rgb(pars, tmp, 0, file_content);
		}
		else if ((!ft_strncmp(file_content[i], "C ", 2) && pars->c_rgb[0] != -1)
			|| (!ft_strncmp(file_content[i], "F ", 2) && pars->f_rgb[0] != -1))
			free_exit(pars, file_content, "Dupicate RGB.", 1);
	}
}

void	check_missing_info(t_pars *pars)
{
	int	i;
	int	j;

	if (!pars->path_e || !pars->path_n
		|| !pars->path_s || !pars->path_w
		|| pars->c_rgb[0] == -1 || pars->f_rgb[0] == -1)
		free_exit(pars, NULL, "Something went wrong.", 1);
	i = -1;
	while (pars->map[++i])
	{
		j = -1;
		while (pars->map[i][++j])
		{
			if (!(pars->map[i][j] == '0' || pars->map[i][j] == '1'
				|| pars->map[i][j] == '2' || pars->map[i][j] == 'W' // what is 2
				|| pars->map[i][j] == 'E' || pars->map[i][j] == 'S'
				|| pars->map[i][j] == 'N' || pars->map[i][j] == ' '))
				free_exit(pars, NULL, "Something went wrong.", 1);
			if (pars->map[i][j] == 'N' || pars->map[i][j] == 'S'
				|| pars->map[i][j] == 'E' || pars->map[i][j] == 'W')
				init_pars_orientation(pars, i, j);
		}
	}
}

void	init_map(char **file_content, t_pars *pars)
{
	int	i;

	i = -1;
	pars->map = malloc(sizeof(char *) * (size_tab(file_content) + 1));
	while (file_content[++i])
		pars->map[i] = ft_strdup(file_content[i]);
	pars->map[i] = NULL;
}

void	init_pars_all(char **file_content, t_pars *pars, char **buff)
{
	int	i;

	i = -1;
	init_file_content(buff, file_content);
	free_tab(buff);
	init_pars(pars);
	parse_texture(pars, file_content);
	parse_cf_rgb(pars, file_content);
	init_map(file_content + 6, pars);
	check_missing_info(pars);
	free_tab(file_content);
	flood_fill(pars);
}

void	parsing(t_pars *pars, char **av)
{
	int		fd;
	char	**file_content;
	char	**buff;
	int		i;

	i = 0;
	fd = open(av[1], O_RDWR, 677);
	if (fd == -1)
		msg_exit("File info corrupted.");
	buff = NULL;
	buff = malloc(sizeof(char *) * 1000);
	while (1)
	{
		buff[i] = get_next_line(fd);
		if (!buff[i])
			break ;
		i++;
	}
	file_content = malloc(sizeof(char *) * (good_size(buff) + 1));
	if (!file_content)
	{
		free_tab(buff);
		msg_exit("Cannot allocate.");
	}
	init_pars_all(file_content, pars, buff);
}
