#include "../inc/fdf.h"

void algo_draw2(t_fdf xyz, t_fdf xyz1, t_fdf *fdf)
{

	float x_step;
	float y_step;
	float max;

	set_value(&xyz, &xyz1, fdf);
	x_step = xyz1.x - xyz.x ;
	y_step = xyz1.y - xyz.y ;
	max = ft_max(mod(x_step), mod(y_step));
	x_step = x_step / max;
	y_step = y_step / max;
	color_z(fdf, xyz.z , xyz1.z);
	while ((int)(xyz.x - xyz1.x) || (int)(xyz.y - xyz1.y))
	{	
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, xyz.x, xyz.y , fdf->color);
		xyz.x = xyz.x + x_step;
		xyz.y = xyz.y + y_step;
		if (xyz.x > fdf->win_x || xyz.y > fdf->win_y || xyz.y < 0 || xyz.x < 0)
			break ;
	}
}

void draw(t_fdf **fdf)
{
	int x;
	int y;

	y = 0;
	while (fdf[y])
	{
		x = 0;
		while (1)
		{
			if(fdf[y + 1])
				algo_draw2(fdf[y][x], fdf[y + 1][x], &fdf[0][0]);
			if(!fdf[y][x].end)
				algo_draw2(fdf[y][x], fdf[y][x + 1], &fdf[0][0]);
			if(fdf[y][x].end)
				break;
			x++;
		}
		y++;
	}
}