#include "../inc/fdf.h"


int		main(int argc, char **argv)
{
    t_fdf **fdf;
    if (argc != 2)
       return(-1);
	parsing_argv(argc, argv[1]);
    fdf = stock_map(argv[1]);
	init_value(&fdf[0][0]);	
	draw(fdf);
	mlx_key_hook(fdf[0][0].win_ptr, deal_key, fdf);
	mlx_loop(fdf[0][0].mlx_ptr);
    return (0);
}