#include "cub3d.h"

void	ft_init_sprite(t_cub3d *cub3d)
{
	int width;
	int height;
	int	i;

	i = -1;
	cub3d->texture[0].text = mlx_xpm_file_to_image(cub3d->mlx_ptr, cub3d->path_n, &width, &height);
	cub3d->texture[1].text = mlx_xpm_file_to_image(cub3d->mlx_ptr, cub3d->path_s, &width, &height);
	cub3d->texture[2].text = mlx_xpm_file_to_image(cub3d->mlx_ptr, cub3d->path_w, &width, &height);
	cub3d->texture[3].text = mlx_xpm_file_to_image(cub3d->mlx_ptr, cub3d->path_e, &width, &height);
	cub3d->gun_text = mlx_xpm_file_to_image(cub3d->mlx_ptr, "textures/gun.xpm", &width, &height);
	while (++i < 4)
		if (!cub3d->texture[i].text)
			msg_exit("Problem while opening texture files.");
}

void	ft_get_address(t_cub3d *cub3d)
{

	cub3d->texture[0].address = mlx_get_data_addr(cub3d->texture[0].text, &cub3d->texture[0].bits_per_pixel, &cub3d->texture[0].line_length, &cub3d->texture[0].endian);
	cub3d->texture[1].address = mlx_get_data_addr(cub3d->texture[1].text, &cub3d->texture[1].bits_per_pixel, &cub3d->texture[1].line_length, &cub3d->texture[1].endian);
	cub3d->texture[2].address = mlx_get_data_addr(cub3d->texture[2].text, &cub3d->texture[2].bits_per_pixel, &cub3d->texture[2].line_length, &cub3d->texture[2].endian);
	cub3d->texture[3].address = mlx_get_data_addr(cub3d->texture[3].text, &cub3d->texture[3].bits_per_pixel, &cub3d->texture[3].line_length, &cub3d->texture[3].endian);
}

void	ft_init_window(t_cub3d *cub3d)
{
	cub3d->mlx_ptr = mlx_init();
	cub3d->mlx_window = mlx_new_window(cub3d->mlx_ptr, screen_w, screen_h, "cub3d");
	cub3d->text = malloc(sizeof(t_textures));
	if (!cub3d->text)
		//free_function!
	// if (!cub3d->mlx_ptr) Add protection for
	// {
	// 	free(cub3d->mlx_ptr);
	// 	ft_error_str("Error mlx_ptr", 11);
	// }
	// cub3d->text->text = mlx_new_image(cub3d->mlx_ptr, screen_w, screen_h);
	// if (!cub3d->text->text)
	// {
	// 	// Handle error for failed image creation
	// 	mlx_destroy_window(cub3d->mlx_ptr, cub3d->mlx_window);
	// 	free(cub3d->mlx_ptr);
	// 	ft_error_str("Error creating image", 11);
	// }
	if (!cub3d->mlx_window)
	{
		mlx_destroy_window(cub3d->mlx_ptr, cub3d->mlx_window);
		free(cub3d->mlx_ptr);
		ft_error_str("Error mlx_window", 11);
	}
	ft_init_sprite(cub3d);
	ft_get_address(cub3d);
	// cub3d->begin_image->text = NULL;
	// cub3d->begin_image->text = mlx_new_image(cub3d->mlx_ptr, screen_w, screen_h);
	// if (!cub3d->text->text)
	// 	ft_error_str("mlx_init begin_image->text mlx_new_image error", 12);
	// cub3d->begin_image->address = mlx_get_data_addr(cub3d->begin_image->text, &cub3d->begin_image->bits_per_pixel, &cub3d->begin_image->line_length, &cub3d->begin_image->endian);
	// mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->mlx_window, cub3d->begin_image->text, 0, 0);
	cub3d->text->text = NULL;
}