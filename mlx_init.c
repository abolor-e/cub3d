#include "cub3d.h"

void	ft_to_image(t_cub3d *cub3d, void **image, char *location)
{
	int width;
	int height;

	*image = mlx_xpm_file_to_image(cub3d->mlx_ptr, location, &width, &height);
	if (!image)
		ft_error_str("Error image creation", 11);
}

void	ft_init_sprite(t_cub3d *cub3d)
{
	ft_to_image(cub3d, &cub3d->texture_data[1], "textures/greystone.xpm");
}

void	ft_init_window(t_cub3d *cub3d)
{
	cub3d->mlx_ptr = mlx_init();
	if (!cub3d->mlx_ptr)
	{
		free(cub3d->mlx_ptr);
		ft_error_str("Error mlx_ptr", 11);
	}
	ft_init_sprite(cub3d);
	cub3d->mlx_window = mlx_new_window(cub3d->mlx_ptr, screen_w, screen_h, "cub3d");
	if (!cub3d->mlx_window)
	{
		free(cub3d->mlx_ptr);
		ft_error_str("Error mlx_window", 11);
	}
}