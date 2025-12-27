/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:50:27 by cwolf             #+#    #+#             */
/*   Updated: 2025/12/27 11:14:02 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

// void free_map(char **grid)
// {
//     if (grid)
//     {
//         for (int i = 0; grid[i] != NULL; i++)
//         {
//             if (grid[i])
//                 free(grid[i]);
//         }
//     }
//     free(grid);
// }

char *ft_strdup(char* buf, int len)
{
    char *copy = NULL;
    copy = (char*)malloc(sizeof(char) * len);
    if (!copy)
        return NULL;
    for(int i = 0; i < len; i++)
    {
        copy[i] = buf[i];
    }
    return copy;
}

int check_elements(char** grid, t_elements *elements)
{
    for (int i = 0; grid[i] != NULL; i++)
    {
        for (int j = 0; grid[i][j] != '\0'; j++)
        {
            if (grid[i][j] != elements->empty && grid[i][j] != elements->obst)
                return -1;
        }
    }
    return 0;
}

void print_map(char** grid)
{
    for (int i = 0; grid[i] != NULL; i++)
    {
        for (int j = 0; grid[i][j] != '\0'; j++)
        {
            fprintf(stdout, "%c", grid[i][j]);
        }
        fprintf(stdout, "\n");
    }
}

int is_square(t_map *map, t_elements *elements, int pos_y, int pos_x, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(map->grid[pos_y + i][pos_x + j] != elements->empty)
            {
                return 0;
            }
        }
    }
    return 1;
}

void print_square(t_map* map, t_found *found, t_elements *elements)
{
    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            if(i >= found->y_pos && i < found->y_pos + found->best_size && j >= found->x_pos && j < found->x_pos + found->best_size)
            {
                map->grid[i][j] = elements->full;
            }
        }
    }
    
    print_map(map->grid);
}