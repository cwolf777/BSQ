/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:35:38 by cwolf             #+#    #+#             */
/*   Updated: 2025/12/17 14:14:10 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int execute(FILE* file)
{
    //load elemets
    t_elements elements;
    // printf("Error code: %d\n", load_elements(file, &elements));
    if (load_elements(file, &elements) < 0)
    {
        return -1;
    }

    //load map
    t_map map;
    if (load_map(file, &elements, &map) < 0)
    {
        return -1;
    }
    // print_map(map.grid);
    //algo
    t_found found;
    bsq(&map, &elements, &found);
    
    //print map
    print_square(&map, &found, &elements);
    return 0;
}

int load_elements(FILE *file, t_elements *elements)
{
    int re;
    re = fscanf(file, "%d %c %c %c", &(elements->num_lines), &(elements->empty), &(elements->obst), &(elements->full));
    if (re != 4)
        return -1;
    
    if (elements->num_lines <= 0)
        return -2;
    if(elements->empty == elements->obst || elements->empty == elements->full || elements->full == elements->obst)
        return -3;
    if(elements->empty < 32 || elements->empty > 126)
        return -4;
    if(elements->obst < 32 || elements->obst > 126)
        return -5;
    if(elements->full < 32 || elements->full > 126)
        return -6;
    return 0;
}

int load_map(FILE *file, t_elements *elements, t_map *map)
{
    map->height = elements->num_lines;
    map->grid = (char**)malloc((map->height + 1) * sizeof(char*));
    if (!map->grid)
        return -1;
    map->grid[map->height] = NULL;
    
    size_t len = 0;
    char* buf = NULL;
    
    int read = getline(&buf, &len, file);
    if (read == -1)
    {
        free(buf);
        free_map(map->grid);
        return -2;
    }
    //input string 00100\n\0  read = 6 -> read = 5 00100\0
    for (int i = 0; i < map->height; i++)
    {
        // printf("i: %d\n", i);
        read = getline(&buf, &len, file);
        if (read == -1)
        {
            free(buf);
            free_map(map->grid);
            return -3;
        }
        read--;
        if (buf[read] == '\n')
        {
            buf[read] = '\0';
        }
        else
        {
            free(buf);
            free_map(map->grid);
            return -4; 
        }
        map->grid[i] = ft_strdup(buf, read);
        if (!map->grid[i])
        {
            free(buf);
            free_map(map->grid);
            return -5;
        }
        
        if (i == 0)
        {
            map->width = read;
        }
        else if (map->width != read)
        {
            free(buf);
            free_map(map->grid);
            return -6;
        }
    }
    
    if (check_elements(map->grid, elements) == -1)
    {
        free(buf);
        free_map(map->grid);
        return -6;
    }
    
    free(buf);
    return 0;
}

//0

void bsq(t_map *map, t_elements *elements, t_found *found)
{
    found->best_size = 0;
    found->x_pos = -1;
    found->y_pos = -1;
    
    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            int curr_size = 1;
            while (i + curr_size <= map->height && j + curr_size <= map->width)
            {
                if (is_square(map, elements, i, j, curr_size))
                {
                    if (curr_size > found->best_size)
                    {
                        found->best_size = curr_size;
                        found->x_pos = j;
                        found->y_pos = i;
                    }
                }
                else
                {
                    break;
                }
                curr_size++;
            }
        }
    }
}