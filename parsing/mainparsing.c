#include "../cub3d.h"

void	parse_texture(t_pars *pars, char **file_content)
{
	int	i;

	i = -1;
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
		else if (!ft_strncmp(file_content[i], "NO ", 3) && pars->path_n)
		{
			free_pars(pars);
			free_tab(file_content);
			msg_exit("Duplicate \"NO\" texture.");
		}
		else if (!ft_strncmp(file_content[i], "SO ", 3) && pars->path_s)
		{
			free_pars(pars);
			free_tab(file_content);
			msg_exit("Duplicate \"SO\" texture.");
		}
		else if (!ft_strncmp(file_content[i], "EA ", 3) && pars->path_e)
		{
			free_pars(pars);
			free_tab(file_content);
			msg_exit("Duplicate \"EA\" texture.");
		}
		else if (!ft_strncmp(file_content[i], "WE ", 3) && pars->path_w)
		{
			free_pars(pars);
			free_tab(file_content);
			msg_exit("Duplicate \"WE\" texture.");
		}
	}
}

void	check_tmp(char **tmp, t_pars *pars, char **file_content)
{
	int	i;
	int	j;

	i = -1;
	while (tmp[++i])
	{
		j = -1;
		while (tmp[i][++j])
		{
			if (!(tmp[i][j] >= '0' && tmp[i][j] <= '9'))
			{
				free_pars(pars);
				free_tab(file_content);
				msg_exit("Bad RGB info.");
			}
		}
		if (ft_atoi(tmp[i]) > 255 || ft_atoi(tmp[i]) < 0)
		{

			free_pars(pars);
			free_tab(file_content);
			msg_exit("RGB values should be between 0-255.");
		}
	}
	if (i == 3)
		return ;
	else
	{
		free_pars(pars);
		free_tab(file_content);
		msg_exit("Bad RGB info.");
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
			check_tmp(tmp, pars, file_content);
			pars->f_rgb[0] = ft_atoi(tmp[0]);
			pars->f_rgb[1] = ft_atoi(tmp[1]);
			pars->f_rgb[2] = ft_atoi(tmp[2]);
			free_tab(tmp);
			free(tmp);
		}
		else if (!ft_strncmp(file_content[i], "C ", 2) && pars->c_rgb[0] == -1)
		{
			tmp = ft_split(file_content[i] + 2, ',');
			check_tmp(tmp, pars, file_content);
			pars->c_rgb[0] = ft_atoi(tmp[0]);
			pars->c_rgb[1] = ft_atoi(tmp[1]);
			pars->c_rgb[2] = ft_atoi(tmp[2]);
			free_tab(tmp);
			free (tmp);
		}
		else if (!ft_strncmp(file_content[i], "C ", 2) && pars->c_rgb[0] != -1)
		{
			free_pars(pars);
			free_tab(file_content);
			msg_exit("Duplicate \"C\" RGB.");
			free_tab(tmp);
			free(tmp);
		}
		else if (!ft_strncmp(file_content[i], "F ", 2) && pars->f_rgb[0] != -1)
		{
			free_pars(pars);
			free_tab(file_content);
			msg_exit("Duplicate \"C\" RGB.");
			free_tab(tmp);
			free(tmp);
		}
	}
}

void	init_pars(t_pars *pars)
{
	int	i;

	i = 0;
	while (i <= 3)
	{
		pars->c_rgb[i] = -1;
		pars->f_rgb[i] = -1;
		i++;
	}
	pars->map = NULL;
	pars->path_n = NULL;
	pars->path_s = NULL;
	pars->path_w = NULL;
	pars->path_e = NULL;
}

void	check_missing_info(t_pars *pars, char **file_content)
{
	int	i;
	int	j;

	i = -1;
	if (!pars->path_e || !pars->path_n || !pars->path_s || !pars->path_w || pars->c_rgb[0] == -1 || pars->f_rgb[0] == -1)
	{
		free_pars(pars);
		free_tab(file_content);
		msg_exit("Missing info.");
	}
	while (file_content[++i])
	{
		j = -1;
		while (file_content[i][++j])
		{
			if (!(file_content[i][j] == '0' || file_content[i][j] == '1' || file_content[i][j] == '2' || file_content[i][j] == 'W' || file_content[i][j] == 'E' || file_content[i][j] == 'S' || file_content[i][j] == 'N' || file_content[i][j] == ' '))
			{
				free_pars(pars);
				free_tab(file_content);
				msg_exit("Map is wrong.");
			}
			if (file_content[i][j] == 'N' || file_content[i][j] == 'S' || file_content[i][j] == 'E' || file_content[i][j] == 'W')
			{
				pars->orientation = file_content[i][j];
				pars->posx = j;
				pars->posy = i;
			}
		}
	}

}

void	parsing(t_pars *pars, char **av)
{
	int		fd;
	char	**file_content;
	char	**buff;
	int		i;
	int		j;

	i = 0;
	fd = open(av[1], O_RDWR, 677);
	if (fd == -1)
		msg_exit("File doesn't exist.");
	buff = malloc(sizeof(char *) * 9999999999);
	while ((buff[i] = get_next_line(fd)))
		i++;
	i = 0;
	j = 0;
	while (buff[i])
	{
		if ((buff[i][0] >= 9 && buff[i][0] <= 13))
			i++;
		else
		{
			i++;
			j++;
		}
	}
	file_content = malloc(sizeof(char *) * (j + 1));
	if (!file_content)
	{
		free_tab(buff);
		free(buff);
		msg_exit("Cannot allocate.");
	}
	i = 0;
	j = 0;
	while (buff[i])
	{
		if ((buff[i][0] >= 9 && buff[i][0] <= 13))
			i++;
		else
		{
			file_content[j] = ft_strdup(buff[i]);
			j++;
			i++;
		}
	}
	free_tab(buff);
	free(buff);
	file_content[j] = NULL;
 	init_pars(pars);
	parse_texture(pars, file_content);
	printf("n : %s\ns : %s\nw : %s\ne : %s\n", pars->path_n, pars->path_s, pars->path_e, pars->path_w);
	parse_cf_rgb(pars, file_content);
	printf("c-R : %d  c-G : %d  c-B : %d\nf-R : %d  f-G : %d  f-B : %d\n", pars->c_rgb[0], pars->c_rgb[1], pars->c_rgb[2], pars->f_rgb[0], pars->f_rgb[1], pars->f_rgb[2]);
	pars->map = file_content + 6;
	check_missing_info(pars, file_content + 6);
	for (int i = 0; i < 6; i++)
		free(file_content[i]);
	printf("Player orientation : %c\nPlayer postion-x : %d\nPlayer position-y : %d\n", pars->orientation, pars->posx, pars->posy);
	flood_fill(pars->map);
}