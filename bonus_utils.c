#include "cub3d.h"

void	ft_mouse(t_cub3d *cub3d)
{
	int	x;
	int	y;
	mlx_mouse_show();
	if (cub3d->keyp.mouse == 0)
	{
		mlx_mouse_hide();
		mlx_mouse_get_pos(cub3d->mlx_window, &x, &y);
		if (x != (screen_w / 2))
			ft_rot_movement(cub3d, 0, cub3d->time.frame * (x - screen_w / 2) / 4);
		mlx_mouse_move(cub3d->mlx_window, screen_w / 2, screen_h / 2);
	}
}

void	ft_gun(t_cub3d *cub3d)
{
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->mlx_window, cub3d->gun_text, 0, 0);
}

int	ft_handle_mouse_move(int x, int y, t_cub3d *cub3d)
{
	int cx;
	int	mov;

	(void)y;
	cx = screen_w / 2;
	mov = x - cx;
	//printf("mov : %d\n", mov);

	// printf("pos mouse : %d, %d\n", z, i);
	cub3d->angle += mov * MOUSE_S;
	if (cub3d->angle < 0)
		cub3d->angle += 2 * M_PI;
	if (cub3d->angle >= 2 * M_PI)
		cub3d->angle -= 2 * M_PI;
	return (0);
}

/*
- Minimap
- Ammo left
- Sprites
- Door
- Graphics (Gun movement, Enemy dying movement)
- Image to begin
*/