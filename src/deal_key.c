#include "../inc/fdf.h"

void ctrl_arrow(t_fdf **fdf, int key)
{
	if(key == 65362)
		fdf[0][0].shift_y = fdf[0][0].shift_y - 10;
	if(key == 65364)
		fdf[0][0].shift_y = fdf[0][0].shift_y + 10;
	if(key == 65361)
		fdf[0][0].shift_x = fdf[0][0].shift_x - 10;
	if(key == 65363)
		fdf[0][0].shift_x = fdf[0][0].shift_x + 10;
}

 void ctrl_zqsd(t_fdf **fdf, int key)
 {
 	if(key == 115)
 		fdf[0][0].degres_y = fdf[0][0].degres_y - 0.05;
 	if(key == 122)
 		fdf[0][0].degres_y = fdf[0][0].degres_y + 0.05;
 	if(key == 100)
 		fdf[0][0].degres_x = fdf[0][0].degres_x - 0.05;
 	if(key == 113)
 		fdf[0][0].degres_x = fdf[0][0].degres_x + 0.05;
	if(key == 97)
	{
 		fdf[0][0].degres_x = fdf[0][0].degres_x + 0.05;
		fdf[0][0].degres_y = fdf[0][0].degres_y + 0.05;
	}
	if(key == 101)
	{
 		fdf[0][0].degres_x = fdf[0][0].degres_x - 0.05;
		fdf[0][0].degres_y = fdf[0][0].degres_y - 0.05;
	}
 }

void ctrl_zoom(t_fdf **fdf, int key)
{
	if(key == 65453)
		if(fdf[0][0].zoom >= 22)
			fdf[0][0].zoom = fdf[0][0].zoom - 2;
	if(key == 65451)
		if(fdf[0][0].zoom <= 800)
			fdf[0][0].zoom = fdf[0][0].zoom + 2;

}

void ctrl_iso_on_off(t_fdf **fdf)
{
	if(fdf[0][0].iso_on_off == 1)
	 	fdf[0][0].iso_on_off = 0;
	else
		fdf[0][0].iso_on_off = 1;
}

int deal_key(int key, t_fdf **fdf)
{  
	if(key == 65307)
	{	
		mlx_destroy_window(fdf[0][0].mlx_ptr, fdf[0][0].win_ptr);
		fdf[0][0].win_ptr = NULL;
		mlx_destroy_display(fdf[0][0].mlx_ptr);
		free(fdf[0][0].mlx_ptr);
		free_fdf(fdf);
		exit(0);
		return 0;
	}
	if(key == 65362 || key == 65364 || key == 65361 || key == 65363)
	 	ctrl_arrow(fdf, key);
	 if(key >= 97 && key <= 122)
	 	ctrl_zqsd(fdf, key);
	 if(key == 65453 || key == 65451)
	 	ctrl_zoom(fdf, key);
	if(key == 178)
		ctrl_iso_on_off(fdf);
	mlx_clear_window(fdf[0][0].mlx_ptr, fdf[0][0].win_ptr);
	draw(fdf);
	return (0);
}