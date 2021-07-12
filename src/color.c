#include "../inc/fdf.h"


void color_z_hot(t_fdf *fdf, int z , int z1)
{
	if((z > 0 && z <= 3) || (z1 > 0 && z <= 3))
		fdf->color = 0xf48e8e;
	else if((z > 3 && z <= 5) || (z1 > 3 && z <= 5))
		fdf->color = 0xe16464;
	else if((z > 5 && z <= 8 ) || (z1 > 5 && z <= 8))
		fdf->color = 0xf05f5f;
	else if((z > 8 && z <= 10) || (z1 > 8 && z <= 10))
		fdf->color = 0xdf3838;
	else if((z > 10 && z <= 15) || (z1 > 10 && z <= 15))
		fdf->color = 0xd81c1c;
	else if(z > 15 || z1 > 15 )
		fdf->color = 0xd20000;
}

void color_z_frost(t_fdf *fdf, int z  ,int z1)
{
	if((z < 0 && z > -3)  || (z1 < 0 && z > -3))
		fdf->color = 0x8f83f7;
	else if((z < -3 && z > -5)  || (z1 < -3 && z > -5))
		fdf->color = 0x695af0;
	else if((z < -5 && z > -8 ) || (z1 < -5 && z > -8))
		fdf->color = 0x4d3ed5;
	else if((z < -8 && z > -10)  || (z1 < -8 && z > -10))
		fdf->color = 0x3324b8;
	else if((z < -10 && z > -15)  || (z1 < -10 && z > -15))
		fdf->color = 0x2010b7;
	else if(z < -15  || z1 < -15 )
		fdf->color = 0x1100b8;
}

void color_z(t_fdf *fdf, float z , float z1)
{
	if(z  || z1)
	{
		if(z > 0  || z1 > 0)
			color_z_hot(fdf, z , z1);
		if(z < 0  || z1 < 0)
			color_z_frost(fdf, z, z1);
	}
	else
		fdf->color = 0xffffff;
}
