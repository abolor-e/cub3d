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

// void	ft_gun(cub3d)
// {

// }

/*
- Minimap
- Ammo left
- Sprites
- Door
- Graphics (Gun movement, Enemy dying movement)
- Image to begin
*/