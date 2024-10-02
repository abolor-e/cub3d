/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:57:02 by abolor-e          #+#    #+#             */
/*   Updated: 2024/10/02 17:23:18 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_init_sprite(t_cub3d *cub3d)
{
	int	width;
	int	height;
	int	i;

	i = -1;
	cub3d->texture[0].text = mlx_xpm_file_to_image(cub3d->mptr,
			cub3d->path_n, &width, &height);
	cub3d->texture[1].text = mlx_xpm_file_to_image(cub3d->mptr,
			cub3d->path_s, &width, &height);
	cub3d->texture[2].text = mlx_xpm_file_to_image(cub3d->mptr,
			cub3d->path_w, &width, &height);
	cub3d->texture[3].text = mlx_xpm_file_to_image(cub3d->mptr,
			cub3d->path_e, &width, &height);
	cub3d->g_t = mlx_xpm_file_to_image(cub3d->mptr,
			"texts/g.xpm", &width, &height);
	while (++i < 4)
		if (!cub3d->texture[i].text)
			msg_exit("Problem while opening texture files.");
}

void	ft_get_address(t_cub3d *cub3d)
{
	cub3d->texture[0].address = mlx_get_data_addr(cub3d->texture[0].text,
			&cub3d->texture[0].bits_per_pixel,
			&cub3d->texture[0].line_length, &cub3d->texture[0].endian);
	cub3d->texture[1].address = mlx_get_data_addr(cub3d->texture[1].text,
			&cub3d->texture[1].bits_per_pixel,
			&cub3d->texture[1].line_length, &cub3d->texture[1].endian);
	cub3d->texture[2].address = mlx_get_data_addr(cub3d->texture[2].text,
			&cub3d->texture[2].bits_per_pixel,
			&cub3d->texture[2].line_length, &cub3d->texture[2].endian);
	cub3d->texture[3].address = mlx_get_data_addr(cub3d->texture[3].text,
			&cub3d->texture[3].bits_per_pixel,
			&cub3d->texture[3].line_length, &cub3d->texture[3].endian);
}

void	ft_init_window(t_cub3d *cub3d)
{
	cub3d->mptr = mlx_init();
	// if (!cub3d->mptr)
	// {
	// 	free(cub3d->mptr);
	// 	ft_error_str("Error mlx_ptr", 11);
	// }
	cub3d->mlx_window = mlx_new_window(cub3d->mptr,
			screen_w, screen_h, "cub3d");
	cub3d->text = malloc(sizeof(t_textures));
	if (!cub3d->text)
		//free_function!
	if (!cub3d->mlx_window)
	{
		mlx_destroy_window(cub3d->mptr, cub3d->mlx_window);
		free(cub3d->mptr);
		ft_error_str("Error mlx_window", 11);
	}
	ft_init_sprite(cub3d);
	ft_get_address(cub3d);
	cub3d->text->text = NULL;
}
