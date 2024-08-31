#include "cub3d.h"

void	ft_sidedist(t_cub3d *cub3d)
{
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
		if (cub3d->map[cub3d->mapx][cub3d->mapy] == 1)
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
	cub3d->deltax = sqrt(1 + cub3d->raydiry * cub3d->raydiry/cub3d->raydirx * cub3d->raydirx);
	cub3d->deltay = sqrt(1 + 1/cub3d->raydiry * cub3d->raydiry/cub3d->raydirx * cub3d->raydirx);
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
}

void	ft_playerpos_int(t_cub3d *cub3d)
{
	cub3d->mapx = (int)cub3d->posx;
	cub3d->mapy = (int)cub3d->posy;
}

int	ft_raycast(t_cub3d *cub3d)
{
	int		x;
	int		texture_vertical;
	double	step;
	double	camerax; /*normalizes camera plane to numbers between 1 and -1>
					   right side being -1, center 0 and left side 1. 
					   This will ease the ray vector calculation!*/
	x = 0;
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
			while (cub3d->lower_point < cub3d->upper_point)
			{
				texture_vertical = (int)cub3d->texture_position & (texture_h - 1);//& operator (bitwise AND) is used because its faster than modulus
				cub3d->texture_position = step + cub3d->texture_position;
				uint32_t tex = texture[code][texture_h * texture_vertical + cub3d->texture_fix];
				screen[cub3d->lower_point][x] = tex;
				cub3d->lower_point++;
			}
			x++;
		}
		cub3d->done = 1;
	}
	return (SUCCESS);
}
