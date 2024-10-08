/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abolor-e <abolor-e@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:45:21 by abolor-e          #+#    #+#             */
/*   Updated: 2024/10/02 17:23:28 by abolor-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_move_check(t_cub3d *cub3d)
{
	if (cub3d->keyp.left == 1)
		ft_movement(cub3d, KEY_A);
	else if (cub3d->keyp.right == 1)
		ft_movement(cub3d, KEY_D);
	else if (cub3d->keyp.forward == 1)
		ft_movement(cub3d, KEY_W);
	else if (cub3d->keyp.backwards == 1)
		ft_movement(cub3d, KEY_S);
	else if (cub3d->keyp.rot_l == 1)
		ft_rot_movement(cub3d, ARROW_L, 0);
	else if (cub3d->keyp.rot_r == 1)
		ft_rot_movement(cub3d, ARROW_R, 0);
}

void	ft_movement(t_cub3d *cub3d, int i)
{
	if (i == KEY_A)
	{
		cub3d->ch_posx = cub3d->posx + (cub3d->diry * cub3d->time.frame * 2);
		cub3d->ch_posy = cub3d->posy - (cub3d->dirx * cub3d->time.frame * 2);
	}
	if (i == KEY_D)
	{
		cub3d->ch_posx = cub3d->posx - (cub3d->diry * cub3d->time.frame * 2);
		cub3d->ch_posy = cub3d->posy + (cub3d->dirx * cub3d->time.frame * 2);
	}
	if (i == KEY_W)
	{
		cub3d->ch_posx = cub3d->posx + (cub3d->dirx * cub3d->time.frame * 5);
		cub3d->ch_posy = cub3d->posy + (cub3d->diry * cub3d->time.frame * 5);
	}
	if (i == KEY_S)
	{
		cub3d->ch_posx = cub3d->posx - (cub3d->dirx * cub3d->time.frame * 5);
		cub3d->ch_posy = cub3d->posy - (cub3d->diry * cub3d->time.frame * 5);
	}
	ft_movement_change(cub3d);
}

void	ft_rot_movement(t_cub3d *cub3d, int i, double x)
{
	double	rot_sp;
	double	prev_dirx;
	double	prev_cpx;

	if (x == 0)
		rot_sp = cub3d->time.frame * 3;
	else if (i == 0)
		rot_sp = x;
	if (i == ARROW_L)
		rot_sp = -rot_sp;
	prev_dirx = cub3d->dirx;
	cub3d->dirx = cub3d->dirx * cos(rot_sp) - cub3d->diry * sin(rot_sp);
	cub3d->diry = prev_dirx * sin(rot_sp) + cub3d->diry * cos(rot_sp);
	prev_cpx = cub3d->planex;
	cub3d->planex = cub3d->planex * cos(rot_sp) - cub3d->planey * sin(rot_sp);
	cub3d->planey = prev_cpx * sin(rot_sp) + cub3d->planey * cos(rot_sp);
}

void	ft_movement_change(t_cub3d *cub3d)
{
	double	gr_posx;
	double	gr_posy;

	if (cub3d->ch_posx > cub3d->posx)
		gr_posx = cub3d->ch_posx + 0.125;
	else
		gr_posx = cub3d->ch_posx - 0.125;
	if (cub3d->ch_posy > cub3d->posy)
		gr_posy = cub3d->ch_posy + 0.125;
	else
		gr_posy = cub3d->ch_posy - 0.125;
	if (cub3d->map[(int)gr_posy][(int)cub3d->posx] != '1')
		cub3d->posy = cub3d->ch_posy;
	if (cub3d->map[(int)cub3d->posy][(int)gr_posx] != '1')
		cub3d->posx = cub3d->ch_posx;
}
