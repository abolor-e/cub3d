/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:23:28 by olmarech          #+#    #+#             */
/*   Updated: 2024/10/02 17:22:44 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	free_cub(t_cub3d *cub3d)
{
	if (cub3d->map)
		free_tab(cub3d->map);
	if (cub3d->path_n)
		free(cub3d->path_n);
	if (cub3d->path_s)
		free(cub3d->path_s);
	if (cub3d->path_e)
		free(cub3d->path_e);
	if (cub3d->path_w)
		free(cub3d->path_w);
	free(cub3d->text);
	free(cub3d);
}

void	free_pars(t_pars *pars)
{
	if (pars->map)
		free_tab(pars->map);
	if (pars->path_n)
		free(pars->path_n);
	if (pars->path_s)
		free(pars->path_s);
	if (pars->path_e)
		free(pars->path_e);
	if (pars->path_w)
		free(pars->path_w);
	free(pars);
}

int	close_free(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mptr, cub3d->text->text);
	mlx_destroy_window(cub3d->mptr, cub3d->mlx_window);
	free(cub3d->mptr);
	free_cub(cub3d);
	exit(EXIT_SUCCESS);
	return (0);
}

void	ft_error_str(char *str, int x)
{
	errno = x;
	perror(str);
	exit(ERROR);
}
