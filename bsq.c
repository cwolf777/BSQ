/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:22:34 by cwolf             #+#    #+#             */
/*   Updated: 2025/12/16 14:32:15 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int load_elements(FILE *file, t_elements *elements);
int load_map(FILE *file, t_elements* elements, t_map* map);
void free_map(char** grid);
int control_elements(char **grid, char c1, char c2);
char *ft_strdup(char * buf, int len);
void print_map(char** grid);
int bsq(t_elements* elements, t_map* map, t_found* found);
int is_square(t_map *map, t_elements *elements, int pos_x, int pos_y, int size);
void print_square(t_map* map, t_found *found, t_elements *elements);

int execute(FILE* file)
{
    //load elements
    t_elements elements;
    if (load_elements(file, &elements) == -1)
        return -1;
    
    //load map
    t_map map;
    
    if (load_map(file, &elements, &map) < 0)
    {
        return -1;
    }
    
    // print_map(map.grid);
    
    //find biggest square
    t_found found;
    bsq(&elements, &map, &found);
    
    printf("Found x: %d, Found y: %d, Size: %d\n", found.x_pos, found.y_pos, found.best_size);
    //print square
    print_square(&map, &found, &elements);
    return 0;
}

int load_elements(FILE *file, t_elements* elements)
{
    int re = fscanf(file, "%d %c %c %c", &(elements->num_lines), &(elements->empty), &(elements->obst), &(elements->full));
    
    if (re != 4)
        return (-1);
    
    if (elements->num_lines <= 0)
        return -1;
    if (elements->empty == elements->obst || elements->empty == elements->full || elements->obst == elements->full)
    {
        return -1;
    }
    if (elements->empty < 32 || elements->empty > 126)
        return -1;
    if(elements->obst < 32 || elements->obst > 126)
        return -1;
    if(elements->full < 32 || elements->full > 126)
        return -1;
    
    return 0;
}

int load_map(FILE *file, t_elements* elements, t_map* map)
{
    map->height = elements->num_lines;
    map->grid = (char**)malloc((map->height + 1) * sizeof(char *));
    map->grid[map->height] = NULL;
    
    size_t len = 0;
    char* buf = NULL;
    
    if (getline(&buf, &len, file) < 0)
    {
        free_map(map->grid);
        return -1;
    }
    //00100\n\0 read = 6    new read = 5 00100\0
    for (int i = 0; i < map->height; i++)
    {
        int read = getline(&buf, &len, file);
        if (read < 0)
        {
            free_map(map->grid);
            free(buf);
            return -2;
        }
        if (buf[read - 1] != '\n')
        {
            free_map(map->grid);
            free(buf);
            return -3;
        }
        else
        {
            read--;
        }
        // buf[read] = '\0';
        map->grid[i] = ft_strdup(buf, read);
        if (!map->grid[i])
        {
            free_map(map->grid);
            free(buf);
            return -4;
        }
        
        if (i == 0)
        {
            map->width = read;
        }
        else if (map->width != read)
        {
            free_map(map->grid);
            free(buf);
            return -5;
        }
    }

    if (control_elements(map->grid, elements->empty, elements->obst) == -1)
    {
        free_map(map->grid);
        free(buf);
        return -6;
    }    
    free(buf);

    return 0;
}

void free_map(char** grid)
{
    int i = 0;
    if (grid)
    {
        while (grid[i] != NULL)
        {
            if (grid[i])
                free(grid[i]);
            i++;
        }
    }
    free(grid);
}

char *ft_strdup(char * buf, int len)
{
    char* copy;
    copy = (char *)malloc(sizeof(char) * (len + 1));
    if (!copy)
        return NULL;
    copy[len] = '\0';
    for (int i =0; i < len; i++)
    {
        copy[i] = buf[i];
    }
    return copy;
}

int control_elements(char **grid, char c1, char c2)
{
    for (int i = 0; grid[i] != NULL; i++)
    {
        for (int j = 0; grid[i][j] != '\0'; j++)
        {
            if (grid[i][j] != c1 && grid[i][j] != c2)
            {
                return -1;
            }
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

int is_square(t_map *map, t_elements *elements, int pos_x, int pos_y, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(map->grid[pos_x + i][pos_y + j] != elements->empty)
            {
                return 0;
            }
        }
    }
    return 1;
}


int bsq(t_elements* elements, t_map* map, t_found* found)
{
    found->x_pos = 0;
    found->y_pos = 0;
    found->best_size = 1;
    
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
                        found->x_pos = i;
                        found->y_pos = j;
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

void print_square(t_map* map, t_found *found, t_elements *elements)
{
    for (int i = 0; i < map->height; i++)
    {
        for (int j = 0; j < map->width; j++)
        {
            if(i >= found->x_pos && i < found->x_pos + found->best_size && j >= found->y_pos && j < found->y_pos + found->best_size)
            {
                map->grid[i][j] = elements->full;
            }
        }
    }
    
    print_map(map->grid);
}