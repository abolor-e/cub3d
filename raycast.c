#include "cub3d.h"

void	ft_sidedist(t_cub3d *cub3d)
{
	int	map_width;
	int	map_height;

	map_height = 14;
	map_width = 33;
	while (cub3d->hit == 0)
	{
		if (cub3d->sidex < cub3d->sidey)//This means if sidex is lower the ray will vertical grid
		{
			cub3d->sidex = cub3d->sidex + cub3d->deltax;//the next x coordinate to hit vertical grid
			cub3d->mapx = cub3d->mapx + cub3d->stepx;
			cub3d->side = 0;//meaning that it hit a vertical grid
		}
		else
		{
			cub3d->sidey = cub3d->sidey + cub3d->deltay;
			cub3d->mapy = cub3d->mapy + cub3d->stepy;//To move the grid to the block where the ray hit
			cub3d->side = 1;//meaning that it hit a horizontal grid
		}
		// printf("mapx: %d, mapy: %d, sidex: %f, sidey: %f, hit: %d, side: %d, deltax: %f, deltay: %f\n", cub3d->mapx, cub3d->mapy, cub3d->sidex, cub3d->sidey, cub3d->hit, cub3d->side, cub3d->deltax, cub3d->deltay);
		if (cub3d->map[cub3d->mapy][cub3d->mapx] == '1')
			cub3d->hit = 1;
	}
}

void	ft_fill_heightpixel(t_cub3d *cub3d)
{
	cub3d->lower_point = -cub3d->column_height / 2 + screen_h / 2 + cub3d->camera_height;
	if (cub3d->lower_point < 0)
		cub3d->lower_point = 0;
	cub3d->upper_point = cub3d->column_height / 2 + screen_h / 2 + cub3d->camera_height;
	if (cub3d->upper_point >= screen_h)
		cub3d->upper_point = screen_h - 1;
}

void	ft_hit_location(t_cub3d *cub3d)
{
	if (cub3d->side == 0)
		cub3d->hit_location = cub3d->posy + cub3d->wall_dist * cub3d->raydiry;
	else
		cub3d->hit_location = cub3d->posx + cub3d->wall_dist * cub3d->raydirx;
	cub3d->hit_location = cub3d->hit_location - floor(cub3d->hit_location);
	/*hit_location after substracting its floor value will exactly
	  be the point the ray hits the grid (block)*/
}

void	ft_hit_loc_texturefix(t_cub3d *cub3d)
{
	cub3d->texture_fix = (int)(cub3d->hit_location * (double)texture_w);
	if (cub3d->side == 0 && cub3d->raydirx > 0)
		cub3d->texture_fix = texture_w - cub3d->texture_fix - 1;
	if (cub3d->side == 1 && cub3d->raydiry < 0)
		cub3d->texture_fix = texture_w - cub3d->texture_fix - 1;
	/*since the graph is reversed when certain rays hits the wall
	  need to check if it hit from the right or left side or from top or down*/
}

void	ft_column_height(t_cub3d *cub3d)
{
	if (cub3d->side == 0)
		cub3d->wall_dist = cub3d->sidex - cub3d->deltax;
	else
		cub3d->wall_dist = cub3d->sidey - cub3d->deltay;
	cub3d->column_height = (int)(screen_h / cub3d->wall_dist);/*if wall distance is far away 
	(high number) column height is low*/
}

double	ft_digital_differential_analysis(t_cub3d *cub3d)
{
	double	step;

	ft_sidedist(cub3d);
	
	ft_column_height(cub3d);
	ft_fill_heightpixel(cub3d);
	ft_hit_location(cub3d);
	ft_hit_loc_texturefix(cub3d);
	step = 1.0 * texture_h / cub3d->column_height;//This will tell how much to increase texture per pixel
	cub3d->texture_position = (cub3d->lower_point - cub3d->camera_height - screen_h / 2 + cub3d->column_height / 2) * step;
	//previous calculation finds exact starting pixel to draw from the texture
	return (step);
}

void	ft_distance(t_cub3d *cub3d)
{
	cub3d->deltax = sqrt(1 + (cub3d->raydiry / cub3d->raydirx) * (cub3d->raydiry / cub3d->raydirx));
	cub3d->deltay = sqrt(1 + (cub3d->raydirx / cub3d->raydiry) * (cub3d->raydirx / cub3d->raydiry));
	/*deltax is calculated taking into account that x unit equals 1 using pythagorean theorem
	  and using slope rise/run equation*/
	if (cub3d->raydirx < 0)
	{
		cub3d->stepx = -1;
		cub3d->sidex = (cub3d->posx - cub3d->mapx) * cub3d->deltax;
	}
	else if (cub3d->raydirx >= 0)
	{
		cub3d->stepx = 1;
		cub3d->sidex = (cub3d->mapx + 1 - cub3d->posx) * cub3d->deltax;
	}
	if (cub3d->raydiry < 0)
	{
		cub3d->stepy = -1;
		cub3d->sidey = (cub3d->posy - cub3d->mapy) * cub3d->deltay;
	}
	else if (cub3d->raydiry >= 0)
	{
		cub3d->stepy = 1;
		cub3d->sidey = (cub3d->mapy + 1 - cub3d->posy) * cub3d->deltay;
	}
	// printf("mapx: %d, mapy: %d, sidex: %f, sidey: %f, hit: %d, side: %d, deltax: %f, deltay: %f\n",
    //    cub3d->mapx, cub3d->mapy, cub3d->sidex, cub3d->sidey, cub3d->hit, cub3d->side, cub3d->deltax, cub3d->deltay);
}

void	ft_playerpos_int(t_cub3d *cub3d)
{
	cub3d->mapx = (int)cub3d->posx;
	cub3d->mapy = (int)cub3d->posy;
}


void	my_mlx_pixel_put(t_textures *text, int x, int y, int color)
{
	char	*dst;

	dst = text->address + (y * text->line_length + x * (text->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_color_get(t_cub3d *cub3d)
{
	int				pix_index;
	unsigned char	*pixel;
	uint32_t		color;

	pix_index = (texture_h * cub3d->texture_vertical + cub3d->texture_fix) * (cub3d->texture[cub3d->side].bits_per_pixel / 8);
	pixel = (unsigned char *)&cub3d->texture[cub3d->side].address[pix_index];
	color = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
	return (color);
}

void	draw_cross(t_cub3d *cub3d)
{
	int	x;
	int	y;

	x = screen_w / 2 - 11;
	y = screen_h / 2 - 11;
	// if (x < 0 || y < 0)
		// free_all(cub3d, "Screen too small", 1);
	while (++x <= screen_w / 2 + 10)
		my_mlx_pixel_put(cub3d->text, x, screen_h / 2, 0x00FFFFFF);
	while (++y <= screen_h / 2 + 10)
		my_mlx_pixel_put(cub3d->text, screen_w / 2, y, 0x00FFFFFF);
}

void	ft_raycast(t_cub3d *cub3d)
{
	int		x;
	//char	*tex;
	int		code;
	double	step;
	int		color;
	double	camerax; /*normalizes camera plane to numbers between 1 and -1>
					   right side being -1, center 0 and left side 1. 
					   This will ease the ray vector calculation!*/
	int	i;

	i = 0;
	x = 0;
	cub3d->text->text = mlx_new_image(cub3d->mlx_ptr, screen_w, screen_h);
	if (!cub3d->text->text)
		ft_error_str("raycast text->text mlx_new_image error", 12);//free_everything! Have to change this!!!!!!!
	cub3d->text->address = mlx_get_data_addr(cub3d->text->text, &cub3d->text->bits_per_pixel, &cub3d->text->line_length, &cub3d->text->endian);
	while (cub3d->done != 1)
	{
		while (x < screen_w)
		{
			camerax = 2 * x / (double)screen_w - 1;//becomes coordinate in the camera plane
			cub3d->raydirx = cub3d->dirx + cub3d->planex * camerax;//in the first loop camerax = -1;
			cub3d->raydiry = cub3d->diry + cub3d->planey * camerax;
			
			ft_playerpos_int(cub3d);
			ft_distance(cub3d);
			step = ft_digital_differential_analysis(cub3d);
			code = cub3d->map[cub3d->mapy][cub3d->mapx] - '0';

			i = 0;
			while (i < cub3d->lower_point)
			{
				my_mlx_pixel_put(cub3d->text, x, i, 0x00FF0000);
				i++;
			}
			while (cub3d->lower_point <= cub3d->upper_point)
			{	
				cub3d->texture_vertical = (int)cub3d->texture_position & (texture_h - 1);//& operator (bitwise AND) is used because its faster than modulus
				cub3d->texture_position = step + cub3d->texture_position;
				color = ft_color_get(cub3d);
				my_mlx_pixel_put(cub3d->text, x, cub3d->lower_point, color);
				// if (cub3d->side == 1)
				// 	color = (color >> 1) & 0x7F7F7F;
				mlx_pixel_put(cub3d->mlx_ptr, cub3d->mlx_window, x, cub3d->lower_point, color);
				cub3d->lower_point++;
			}
			i = cub3d->upper_point;
			while (++i < screen_h)
				my_mlx_pixel_put(cub3d->text, x, i, 0x00FF0000);
			draw_cross(cub3d);
			x++;
		}
		mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->mlx_window, cub3d->text->text, 0, 0);
		// cub3d->done = 1;
	}
}
