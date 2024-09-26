#include "cub3d.h"

void	ft_sidedist(t_cub3d *cub3d)
{
	while (cub3d->hit == 0)
	{
		if (cub3d->sidex < cub3d->sidey)//This means if sidex is lower the ray will hit vertical grid
		{
			cub3d->side = 3;
			if (cub3d->raydirx < 0)
				cub3d->side = 2;
			cub3d->sidex = cub3d->sidex + cub3d->deltax;//the next x coordinate to hit vertical grid
			cub3d->mapx = cub3d->mapx + cub3d->stepx;
		}
		else
		{
			cub3d->side = 1;
			if (cub3d->raydiry < 0)
				cub3d->side = 0;
			cub3d->sidey = cub3d->sidey + cub3d->deltay;
			cub3d->mapy = cub3d->mapy + cub3d->stepy;//To move the grid to the block where the ray hit
		}
		if (cub3d->map[cub3d->mapy][cub3d->mapx] == '1')
			cub3d->hit = 1;
	}
}

void	ft_fill_heightpixel(t_cub3d *cub3d)
{
	cub3d->lower_point = -cub3d->column_height / 2 + screen_h / 2 - 1;
	if (cub3d->lower_point < 0)
		cub3d->lower_point = 0;
	cub3d->upper_point = cub3d->column_height / 2 + screen_h / 2;
	if (cub3d->upper_point >= screen_h)
		cub3d->upper_point = screen_h - 1;
}

void	ft_hit_location(t_cub3d *cub3d)
{
	if (cub3d->side == 2 || cub3d->side == 3)
		cub3d->hit_location = cub3d->posy + cub3d->wall_dist * cub3d->raydiry;
	else
		cub3d->hit_location = cub3d->posx + cub3d->wall_dist * cub3d->raydirx;
	cub3d->hit_location -= floor(cub3d->hit_location);
	/*hit_location after substracting its floor value will exactly
	  be the point the ray hits the grid (block)*/
}

void	ft_hit_loc_texturefix(t_cub3d *cub3d)
{
	cub3d->texture_fix = (int)(cub3d->hit_location * (double)texture_w);
	if ((cub3d->side == 2 && cub3d->raydirx < 0) || (cub3d->side == 1 && cub3d->raydiry > 0))
		cub3d->texture_fix = texture_w - cub3d->texture_fix - 1;
	else if ((cub3d->side == 0 && cub3d->raydiry < 0) || (cub3d->side == 3 && cub3d->raydirx > 0))
		cub3d->texture_fix = texture_w - cub3d->texture_fix - 1;
	/*since the graph is reversed when certain rays hits the wall
	  need to check if it hit from the right or left side or from top or down*/
}

void	ft_column_height(t_cub3d *cub3d)
{
	if (cub3d->side == 2 || cub3d->side == 3)
		cub3d->wall_dist = cub3d->sidex - cub3d->deltax;
	else
		cub3d->wall_dist = cub3d->sidey - cub3d->deltay;
	cub3d->column_height = (int)(screen_h / cub3d->wall_dist);/*if wall distance is far away
	(high number) column height is low*/
}

void	ft_digital_differential_analysis(t_cub3d *cub3d)
{
	ft_sidedist(cub3d);

	ft_column_height(cub3d);
	ft_fill_heightpixel(cub3d);
	ft_hit_location(cub3d);
	ft_hit_loc_texturefix(cub3d);
	cub3d->step = 1.0 * texture_h / cub3d->column_height;//This will tell how much to increase texture per pixel
	cub3d->texture_position = (cub3d->lower_point - (screen_h / 2) + (cub3d->column_height / 2)) * cub3d->step;
	//previous calculation finds exact starting pixel to draw from the texture
}

void	ft_distance(t_cub3d *cub3d)
{
	if (cub3d->raydirx == 0)
		cub3d->deltax = 1e30;
	else
		cub3d->deltax = fabs(1 / cub3d->raydirx);
		//cub3d->deltax = sqrt(1 + (cub3d->raydiry / cub3d->raydirx) * (cub3d->raydiry / cub3d->raydirx));
	if (cub3d->raydiry == 0)
		cub3d->deltay = 1e30;
	else
		cub3d->deltay = fabs(1 / cub3d->raydiry);
		//cub3d->deltay = sqrt(1 + (cub3d->raydirx / cub3d->raydiry) * (cub3d->raydirx / cub3d->raydiry));
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
		cub3d->sidex = (cub3d->mapx + 1.0 - cub3d->posx) * cub3d->deltax;
	}
	if (cub3d->raydiry < 0)
	{
		cub3d->stepy = -1;
		cub3d->sidey = (cub3d->posy - cub3d->mapy) * cub3d->deltay;
	}
	else if (cub3d->raydiry >= 0)
	{
		cub3d->stepy = 1;
		cub3d->sidey = (cub3d->mapy + 1.0 - cub3d->posy) * cub3d->deltay;
	}
}

void	ft_playerpos_int(t_cub3d *cub3d)
{
	cub3d->mapx = (int)cub3d->posx;
	cub3d->mapy = (int)cub3d->posy;
}


void	my_mlx_pixel_put(t_textures *text, int x, int y, int color)
{
	// if (x > 0 && x < screen_w && y > 0 && y < screen_h)  // Check bounds
	// {
		char	*dst;

		dst = text->address + (y * text->line_length + x * (text->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	// }
	// else
	// 	ft_error_str("something is wrong", 11);
}


uint32_t	ft_color_get(t_cub3d *cub3d)
{
	int				pix_index;
	unsigned char	*pixel;
	uint32_t		color;

	// Ensure texture coordinates are within bounds
	// if (cub3d->texture_vertical >= texture_h || cub3d->texture_fix >= texture_w)
	// 	return 0xFFFFFF;  // Return white or any error color if out of bounds

	pix_index = (texture_h * cub3d->texture_vertical + cub3d->texture_fix) *
	            (cub3d->texture[cub3d->side].bits_per_pixel / 8);

	pixel = (unsigned char *)&cub3d->texture[cub3d->side].address[pix_index];
	color = (pixel[2] << 16) | (pixel[1] << 8) | pixel[0];
	return color;
}

void	ft_draw_text(t_cub3d *cub3d, int x)
{
	uint32_t	color;
	int			i;

	i = 0;
	while (i < cub3d->lower_point)
	{
		my_mlx_pixel_put(cub3d->text, x, i, cub3d->c_rgb);
		i++;
	}
	while (cub3d->lower_point <= cub3d->upper_point)
	{
		cub3d->texture_vertical = (int)cub3d->texture_position & (texture_h - 1);//& operator (bitwise AND) is used because its faster than modulus
		cub3d->texture_position += cub3d->step;
		color = ft_color_get(cub3d);
		my_mlx_pixel_put(cub3d->text, x, cub3d->lower_point, color);
		cub3d->lower_point++;
	}
	i = cub3d->upper_point;
	while (++i < screen_h)
		my_mlx_pixel_put(cub3d->text, x, i, cub3d->f_rgb);
}

void	ft_gun_point_sideways(t_cub3d *cub3d)
{
	int	x;
	int z;
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
	int z;
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

void ft_draw_orientation_triangle(t_cub3d *data) 
{
    int line_length = 90;  // You can increase this for a longer triangle
    double angle_offset = 0.6;  // Adjust this for wider or narrower triangle (in radians)

    // Convert player angle to radians if it's in degrees
    double angle = data->angle;

    // Calculate the direction for the left and right lines
    double left_dir_x = cos(angle - angle_offset);
    double left_dir_y = sin(angle - angle_offset);
    double right_dir_x = cos(angle + angle_offset);
    double right_dir_y = sin(angle + angle_offset);

    // Draw the left line by placing pixels from player position outward
    for (int i = 0; i < line_length; i++) {
        int left_x = 120 + (int)(left_dir_x * i);
        int left_y = 120 + (int)(left_dir_y * i);
        my_mlx_pixel_put(data->text, left_x, left_y, 0xFFFFFF);  // White color for the left line
    }

    // Draw the right line by placing pixels from player position outward
    for (int i = 0; i < line_length; i++) {
        int right_x = 120 + (int)(right_dir_x * i);
        int right_y = 120 + (int)(right_dir_y * i);
        my_mlx_pixel_put(data->text, right_x, right_y, 0xFFFFFF);  // White color for the right line
    }
}

void	ft_draw_minimap_pixel(t_cub3d *cub3d, int x, int y, int radius, int color)
{
	int center_x = 120;
	int center_y = 120;
	int dist = sqrt((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y));

	// Only draw pixels inside the circle
	if (dist <= radius)
	{
		my_mlx_pixel_put(cub3d->text, x, y, color);
		my_mlx_pixel_put(cub3d->text, x + 1, y + 1, color);
	}
}

void	ft_draw_minimap(t_cub3d *cub3d, int radius)
{
	int	map_x, map_y;
	int	pixel_x, pixel_y;
	int scale = 10;  // Adjust scale to fit your map
	double dist_to_player;

	for (map_y = (int)(cub3d->posy - 4.5); map_y <= (int)(cub3d->posy + 4.5); map_y++)
	{
		for (map_x = (int)(cub3d->posx - 4.5); map_x <= (int)(cub3d->posx + 4.5); map_x++)
		{
			// Check if the map coordinates are within bounds
			if (map_x >= 0 && map_x < 33 && map_y >= 0 && map_y < 14)
			{
				// Calculate distance to player
				dist_to_player = sqrt((map_x - cub3d->posx) * (map_x - cub3d->posx) + (map_y - cub3d->posy) * (map_y - cub3d->posy));
				
				// Only draw if within 4.5 units
				if (dist_to_player <= 4.5)
				{
					// Translate map position to minimap coordinates
					pixel_x = 120 + (map_x - cub3d->posx) * scale;
					pixel_y = 120 + (map_y - cub3d->posy) * scale;

					// Draw the map tile inside the circle
					if (cub3d->map[map_y][map_x] == '1')  // Assuming '1' is a wall in the map
						ft_draw_minimap_pixel(cub3d, pixel_x, pixel_y, radius, 0x39FF14);  // Wall color
					else
						ft_draw_minimap_pixel(cub3d, pixel_x, pixel_y, radius, 0x808080);  // Floor color
				}
			}
		}
	}

	// Draw the player position
	ft_draw_minimap_pixel(cub3d, 120, 120, radius, 0xFF0000);  // Red for player
}

void	ft_draw_circle(t_cub3d *cub3d, int x0, int y0, int radius, int color)
{
    int x;
	int	y;
	int	d;

    x = 0;
    y = radius;
    d = 3 - 2 * radius;
	my_mlx_pixel_put(cub3d->text, x0 + 1, y0, 0x000080);
	my_mlx_pixel_put(cub3d->text, x0 - 1, y0, 0x000080);
	my_mlx_pixel_put(cub3d->text, x0, y0, 0x000080);
	my_mlx_pixel_put(cub3d->text, x0, y0 + 1, 0x000080);
	my_mlx_pixel_put(cub3d->text, x0, y0 - 1, 0x000080);
    while (x++ <= y)
    {
        my_mlx_pixel_put(cub3d->text, x0 + x, y0 + y, color);
        my_mlx_pixel_put(cub3d->text, x0 + y, y0 + x, color);
        my_mlx_pixel_put(cub3d->text, x0 - x, y0 + y, color);
        my_mlx_pixel_put(cub3d->text, x0 - y, y0 + x, color);
        my_mlx_pixel_put(cub3d->text, x0 + x, y0 - y, color);
        my_mlx_pixel_put(cub3d->text, x0 + y, y0 - x, color);
        my_mlx_pixel_put(cub3d->text, x0 - x, y0 - y, color);
        my_mlx_pixel_put(cub3d->text, x0 - y, y0 - x, color);

        if (d < 0)
            d += 4 * x + 6;
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
    }
}

void	ft_minimap(t_cub3d *cub3d)
{
	int radius = 90;  // Same radius as your circle

	// Draw circle outline
	ft_draw_circle(cub3d, 120, 120, radius, 0x000000);
	
	// Draw minimap inside the circle
	ft_draw_minimap(cub3d, radius);
	mlx_hook(cub3d->mlx_window, 6, 0, &ft_handle_mouse_move, cub3d);
	ft_draw_orientation_triangle(cub3d);
}

void	ft_raycast(t_cub3d *cub3d)
{
	int		x;
	double	camerax; /*normalizes camera plane to numbers between 1 and -1>
					   right side being -1, center 0 and left side 1.
					   This will ease the ray vector calculation!*/
	x = 0;
	cub3d->text->text = mlx_new_image(cub3d->mlx_ptr, screen_w, screen_h);
	if (!cub3d->text->text)
		ft_error_str("raycast text->text mlx_new_image error", 12);//free_everything! Have to change this!!!!!!!
	cub3d->text->address = mlx_get_data_addr(cub3d->text->text, &cub3d->text->bits_per_pixel, &cub3d->text->line_length, &cub3d->text->endian);
	x = -1;
	while (++x < screen_w)
	{
		cub3d->hit = 0;
		camerax = 2 * x / (double)screen_w - 1;//becomes coordinate in the camera plane
		cub3d->raydirx = cub3d->dirx + cub3d->planex * camerax;//in the first loop camerax = -1;
		cub3d->raydiry = cub3d->diry + cub3d->planey * camerax;

		ft_playerpos_int(cub3d);
		ft_distance(cub3d);
		ft_digital_differential_analysis(cub3d);
		ft_draw_text(cub3d, x);
	}
	ft_gun_point(cub3d);
	ft_minimap(cub3d);
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->mlx_window, cub3d->text->text, 0, 0);
	ft_gun(cub3d);
}