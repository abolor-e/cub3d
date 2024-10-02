/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 18:36:50 by olmarech          #+#    #+#             */
/*   Updated: 2024/10/02 17:23:16 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_keypress(int keycode, t_cub3d *cub3d)
{
	if (keycode == KEY_A)
		cub3d->keyp.left = 1;
	else if (keycode == KEY_D)
		cub3d->keyp.right = 1;
	else if (keycode == KEY_S)
		cub3d->keyp.backwards = 1;
	else if (keycode == KEY_W)
		cub3d->keyp.forward = 1;
	else if (keycode == KEY_ESC)
		close_free(cub3d);
	else if (keycode == ARROW_L)
		cub3d->keyp.rot_l = 1;
	else if (keycode == ARROW_R)
		cub3d->keyp.rot_r = 1;
	else if (keycode == MOUSE)
		cub3d->keyp.mouse = 1;
	else if (keycode == LEFTCLICK)
		cub3d->keyp.l_click = 1;
	return (0);
}

int	ft_keyrelease(int keycode, t_cub3d *cub3d)
{
	if (keycode == KEY_A)
		cub3d->keyp.left = 0;
	else if (keycode == KEY_D)
		cub3d->keyp.right = 0;
	else if (keycode == KEY_S)
		cub3d->keyp.backwards = 0;
	else if (keycode == KEY_W)
		cub3d->keyp.forward = 0;
	else if (keycode == KEY_ESC)
		close_free(cub3d);
	else if (keycode == ARROW_L)
		cub3d->keyp.rot_l = 0;
	else if (keycode == ARROW_R)
		cub3d->keyp.rot_r = 0;
	else if (keycode == MOUSE)
		cub3d->keyp.mouse = 0;
	return (0);
}

int	ft_render_next_frame_bymove(t_cub3d *cub3d)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	cub3d->time.prev = cub3d->time.pres;
	cub3d->time.pres = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	cub3d->time.frame = (cub3d->time.pres - cub3d->time.prev) / 1000;
	ft_move_check(cub3d);
	mlx_destroy_image(cub3d->mptr, cub3d->text->text);
	ft_mouse(cub3d);
	ft_shoot(cub3d);
	ft_raycast(cub3d);
	return (0);
}
