#include "../inc/fdf.h"

void init_value(t_fdf *fdf)
{
	
	fdf->zoom = 20;
	fdf->color = 0xfc0345;
	fdf->zoom_z = 1;
	fdf->iso_on_off = 1;
	fdf->degres_x = 0.8;
	fdf->degres_y = 0.8;
	fdf->win_x = 800;
	fdf->win_y = 400;
	fdf->shift_x = fdf->win_x / 2.5;
	fdf->shift_y = fdf->win_x / 8;
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->win_x, fdf->win_y, "FDF");
}
