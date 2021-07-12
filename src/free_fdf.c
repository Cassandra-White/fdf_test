#include "../inc/fdf.h"

void free_fdf(t_fdf **fdf)
{
	int i ;
	i = 0;
	if(fdf)
		while(fdf[i] != NULL)
			free(fdf[i++]);
    free(fdf);
}