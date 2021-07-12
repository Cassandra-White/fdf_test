#include "../inc/fdf.h"

int stock_map2d(t_fdf **map2d, char *line, int y)
{
    char **tab_num;
    int x;

    tab_num = ft_strsplit(line, ' ');
    x = 0;
    while (tab_num[x])
    {
        map2d[y][x].z = ft_atoi(tab_num[x]);
		map2d[y][x].x = x;
		map2d[y][x].y = y;
		map2d[y][x].end = 0;
        free(tab_num[x++]);
    }
	free(tab_num);
	free(line);
	map2d[y][--x].end = 1;
	return(x);
}

int		stock_y(int x, int fd, char *line)
{
	int y;
	y = 0;
	while (get_next_line(fd, &line, 0) > 0)
	{
		if(x != ft_wdcounter(line, ' '))
		{
			get_next_line(fd, &line, 1);
			free(line);
			ft_error("Error : Map is'nt a square");
		}
		y++;
		free(line);
	}
	free(line);
	return(y);
}


t_fdf	**memory_allocete(char *file_name)
{
	t_fdf	**new;
	int		x;
	int		y;
	int		fd;
	char	*line;

	if ((fd = open(file_name, O_RDONLY, 0)) <= 0)
		ft_error("Error : file does not exist");
	get_next_line(fd, &line, 0);
	x = ft_wdcounter(line, ' ');
	free(line);
	y = stock_y(x, fd, line);
	if ((new = (t_fdf **)malloc(sizeof(t_fdf *) * (++y + 1))) == NULL)
		return(NULL);
	while (y > 0)
		if ((new[--y] = (t_fdf *)malloc(sizeof(t_fdf) * (x + 1))) == NULL)
			return(NULL);
	close(fd);
	return (new);
}

t_fdf **stock_map(char *file)
{
	t_fdf **map2d;
    int fd;
    char *line;
    int y;

	map2d = memory_allocete(file);
    fd = open(file, O_RDONLY, 0);
    y = 0;
    while (get_next_line(fd, &line, 0) > 0)
    {	
        stock_map2d(map2d, line, y++);
    }
	free(line);
	get_next_line(fd, &line, 1);
	map2d[y] = NULL;
    close(fd);
	return(map2d);
}