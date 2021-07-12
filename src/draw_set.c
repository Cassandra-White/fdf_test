#include "../inc/fdf.h"

void isometric(t_fdf *fdf, double degres_x, double degres_y)
{
	fdf->x = (fdf->x - fdf->y) * cos(degres_x);
	fdf->y = (fdf->x + fdf->y) * sin(degres_y) - fdf->z;
}

float ft_max(float a, float b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

float mod(float i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}


void set_value(t_fdf *xyz,t_fdf *xyz1, t_fdf *fdf)
{
	xyz->x = xyz->x * fdf->zoom;
	xyz->y = xyz->y * fdf->zoom;
	xyz1->x = xyz1->x * fdf->zoom;
	xyz1->y = xyz1->y * fdf->zoom;
	xyz->z = xyz->z * fdf->zoom_z;
	xyz1->z = xyz1->z * fdf->zoom_z;
	if(fdf->iso_on_off)
	{
		isometric(xyz, fdf->degres_x, fdf->degres_y );
		isometric(xyz1, fdf->degres_x, fdf->degres_y);
	}
	xyz->x += fdf->shift_x;
	xyz->y += fdf->shift_y;
	xyz1->x += fdf->shift_x;
	xyz1->y += fdf->shift_y;
}