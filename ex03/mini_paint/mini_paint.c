/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agigi <agigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 23:09:21 by agigi             #+#    #+#             */
/*   Updated: 2021/05/06 11:33:56 by agigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

typedef struct	s_map
{
	int width;
	int height;
	char background;
}				t_map;

typedef struct	s_shape
{
	char type;
	float xx;
	float yy;
	float radius;
	char color;
}				t_shape;

FILE *g_file;
char *g_drawing;


size_t ft_strlen(char *str)
{
	size_t count;

	count = 0;
	while(str[count])
		count++;
	return (count);
}
void ft_clear(void)
{
	if(g_file)
		fclose(g_file);
	if(g_drawing)
		free(g_drawing);
}

void ft_error_message(char *message)
{
	write(1, message, ft_strlen(message));
	ft_clear();
	exit(1);
}

void ft_paint_background(t_map *map)
{
	int i;

	i = 0;
	if(!(g_drawing = (char *) malloc((map->width * map->height) * sizeof(char *))))
		ft_error_message("Error: malloc\n");
	while(i < (map->width * map->height))
		g_drawing[i++] = map->background;
}

void ft_init_map(t_map *map)
{
	int ret;

	ret = fscanf(g_file, "%i %i %c\n", &map->width, &map->height, &map->background);
	if(ret != 3)
		ft_error_message("Error: Operation file corrupted\n");
	if(map->width <= 0 || map->width > 300)
		ft_error_message("Error: Operation file corrupted\n");
	if(map->height <= 0 || map->height > 300)
		ft_error_message("Error: Operation file corrupted\n");
	ft_paint_background(map);
}

int ft_check_coord(float x, float y, t_shape *shape)
{
	float distance;

	distance = sqrtf(powf(x - shape->xx, 2) + powf(y - shape->yy, 2));
	if(distance <= shape->radius)
	{
		if((shape->radius - distance) < 1.0)
			return (2);
		return (1);
	}
	return (0);
}

void ft_paint_shape(t_map *map, t_shape *shape)
{
	int x;
	int y;
	int ret;

	y = 0;
	while(y < map->height)
	{
		x = 0;
		while(x < map->width)
		{
			ret = ft_check_coord((float)x, (float)y, shape);
			if((shape->type == 'c' && ret == 2) || (shape->type == 'C' && ret))
				g_drawing[y * map->width + x] = shape->color;
			x++;
		}
		y++;
	}
}

void ft_init_shape(t_map *map)
{
	t_shape shape;
	int ret;

	while((ret = fscanf(g_file, "%c %f %f %f %c\n", &shape.type, &shape.xx, &shape.yy, &shape.radius, &shape.color)) == 5)
	{
		if(shape.radius <= 0.0)
			ft_error_message("Error: Operation file corrupted\n");
		if(shape.type != 'c' && shape.type != 'C')
			ft_error_message("Error: Operation file corrupted\n");
		ft_paint_shape(map, &shape);
	}
	if(ret != -1)
		ft_error_message("Error: Operation file corrupted\n");
}

void ft_drawing(t_map *map)
{
	int i;

	i = 0;
	while(i < map->height)
	{
		write(1, g_drawing + i * map->width, map->width);
		write(1, "\n", 1);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_map map;

	g_file = NULL;
	g_drawing = NULL;
	if(argc != 2)
		ft_error_message("Error: argument\n");
	if(!(g_file = fopen(argv[1], "r")))
		ft_error_message("Error: Operation file corrupted\n");
	ft_init_map(&map);
	ft_init_shape(&map);
	ft_drawing(&map);
	ft_clear();
	return (0);
}