/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:17:12 by cwolf             #+#    #+#             */
/*   Updated: 2025/12/17 13:57:40 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct s_map
{
    int height;
    int width;
    char **grid;
} t_map;

typedef struct s_elements
{
    int num_lines;
    char empty;
    char obst;
    char full;
} t_elements;


typedef struct s_found
{
    int x_pos;
    int y_pos;
    int best_size;
} t_found;
//found map oder so

int execute(FILE* file);

//load elements
int load_elements(FILE *file, t_elements *elements);

//load map
int load_map(FILE *file, t_elements *elements, t_map *map);
void free_map(char **grid);
char *ft_strdup(char* buf, int len);
int check_elements(char** grid, t_elements *elements);
void print_map(char** grid);

//bsq
void bsq(t_map *map, t_elements *elements, t_found *found);
int is_square(t_map *map, t_elements *elements, int pos_y, int pos_x, int size);
void print_square(t_map *map, t_found *found, t_elements *elements);