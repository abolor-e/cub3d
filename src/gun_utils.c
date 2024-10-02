/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:16:20 by abolor-e          #+#    #+#             */
/*   Updated: 2024/10/02 17:23:14 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_gun_point_sideways(t_cub3d *cub3d)
{
	int	x;
	int	z;
	int	i;

	i = 0;
	x = screen_w / 2 - 10;
	z = screen_w / 2 + 10;
	while (++i < 11)
	{
		my_mlx_pixel_put(cub3d->text, x, screen_h / 2, 0x39FF14);
		my_mlx_pixel_put(cub3d->text, z, screen_h / 2, 0x39FF14);
		x--;
		z++;
	}
}

void	ft_gun_point(t_cub3d *cub3d)
{
	int	x;
	int	z;
	int	i;

	i = 0;
	x = screen_h / 2 - 10;
	z = screen_h / 2 + 10;
	while (++i < 11)
	{
		my_mlx_pixel_put(cub3d->text, screen_w / 2, x, 0x39FF14);
		my_mlx_pixel_put(cub3d->text, screen_w / 2, z, 0x39FF14);
		x--;
		z++;
	}
	ft_gun_point_sideways(cub3d);
}

void	ft_gun(t_cub3d *cub3d)
{
	mlx_put_image_to_window(cub3d->mptr, cub3d->mlx_window, cub3d->g_t, 0, 0);
}

int	ft_shoot(t_cub3d *cub3d)
{
	int	w;
	int	h;

	if (cub3d->keyp.l_click == 1)
		cub3d->keyp.l_click = shoot_utils(cub3d, 1);
	else if (cub3d->keyp.l_click == 2)
		cub3d->keyp.l_click = shoot_utils(cub3d, 2);
	else if (cub3d->keyp.l_click == 3)
		cub3d->keyp.l_click = shoot_utils(cub3d, 3);
	else
	{
		mlx_destroy_image(cub3d->mptr, cub3d->g_t);
		cub3d->g_t = mlx_xpm_file_to_image(cub3d->mptr, "texts/g.xpm", &w, &h);
	}
	return (0);
}

int	shoot_utils(t_cub3d *cub3d, int i)
{
	int	w;
	int	h;

	mlx_destroy_image(cub3d->mptr, cub3d->g_t);
	if (i == 1)
		cub3d->g_t = mlx_xpm_file_to_image(cub3d->mptr, "texts/s1.xpm", &w, &h);
	else if (i == 2)
		cub3d->g_t = mlx_xpm_file_to_image(cub3d->mptr, "texts/s1.xpm", &w, &h);
	else if (i == 3)
		cub3d->g_t = mlx_xpm_file_to_image(cub3d->mptr, "texts/s2.xpm", &w, &h);
	else if (i == 4)
		cub3d->g_t = mlx_xpm_file_to_image(cub3d->mptr, "texts/s2.xpm", &w, &h);
	else if (i == 5)
		cub3d->g_t = mlx_xpm_file_to_image(cub3d->mptr, "texts/s3.xpm", &w, &h);
	else if (i == 6)
		cub3d->g_t = mlx_xpm_file_to_image(cub3d->mptr, "texts/s3.xpm", &w, &h);
	return (i + 1);
}
