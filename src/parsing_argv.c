#include "../inc/fdf.h"

void ft_is_directory(char *file)
{
	int fd;
	fd = open(file, O_DIRECTORY, 0);
    if (fd != -1)
        ft_error("Error : Directory is invalid !\n");
}


void parsing_argv(int argc, char *file)
{
	int i;
	int stop;
    
    i = 0;
	if (argc != 2)
		ft_error("Error: ARGS ./fdf map.fdf");
    while (file[i] != '\0')
        i++;
    while (file[i] != '.')
        i--;
	stop = i;
	while(file[i] != '\0')
	{
    	if (file[i] != '.' && file[i] != 'f' && file[i] != 'd')
				ft_error("Error: FILE exemple: map.fdf");
		i++;
	}
	if (i != stop + 4)
		ft_error("Error: FILE exemple: map.fdf");
	ft_is_directory(file);
}