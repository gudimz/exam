/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agigi <agigi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 19:33:36 by agigi             #+#    #+#             */
/*   Updated: 2021/04/30 21:49:36 by agigi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_map
{
	int	with;
	int height;
	char background;
}				t_map;

typedef struct	s_shape
{
	char type;
	float xx;
	float yy;
	float width;
	float height;
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
	if(g_drawing)
		free(g_drawing);
	if (g_file)
		fclose(g_file);
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
	if(!(g_drawing = (char *)malloc(sizeof(char *) * (map->with * map->height))))
		ft_error_message("Error: Malloc\n");
	while(i < (map->with * map->height))
	{
		g_drawing[i] = map->background;
		i++;
	}
}

void ft_init_map(t_map *map)
{
	int ret;

	ret = fscanf(g_file, "%d %d %c\n", &map->with, &map->height, &map->background);
	if(ret != 3)
		ft_error_message("Error: Operation file corrupted\n");
	if(map->with <= 0 || map->with > 300)
		ft_error_message("Error: Operation file corrupted\n");
	if(map->height <= 0 || map->height > 300)
		ft_error_message("Error: Operation file corrupted\n");
	ft_paint_background(map);
}

int ft_check_coord(int x, int y, t_shape *shape)
{
	if(x < shape->xx || x > (shape->xx + shape->width) || \
		y < shape->yy || y > (shape->yy + shape->height))
		return (0);
	if(x - shape->xx < 1.0 || (shape->xx + shape->width) - x < 1.0 || \
		y - shape->yy < 1.0 || (shape->yy + shape->height) - y < 1.0)
		return (2);
	return (1);
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
		while(x < map->with)
		{
			ret = ft_check_coord(x, y, shape);
			if((shape->type == 'r' && ret == 2) || (shape->type == 'R' && ret))
				g_drawing[(map->with * y + x)] = shape->color;
			x++;
		}
		y++;
	}
}

void ft_init_shape(t_map *map)
{
	int ret;
	t_shape shape;

	while((ret = fscanf(g_file, "%c %f %f %f %f %c\n", &shape.type, &shape.xx, &shape.yy, \
			&shape.width, &shape.height, &shape.color)) == 6)
	{
		if(shape.width <= 0.0 || shape.height <= 0.0)
			ft_error_message("Error: Operation file corrupted\n");
		if(shape.type != 'r' && shape.type != 'R')
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
		write(1, g_drawing + (i * map->with), map->with);
		write(1, "\n", 1);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_map map;

	g_file = NULL;
	g_drawing = NULL;

	if (argc != 2)
		ft_error_message("Error: argument\n");
	if (!(g_file = fopen(argv[1], "r")))
		ft_error_message("Error: Operation file corrupted\n");
	ft_init_map(&map);
	ft_init_shape(&map);
	ft_drawing(&map);
	ft_clear();
	return (0);
}
