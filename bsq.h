/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 10:17:12 by cwolf             #+#    #+#             */
/*   Updated: 2025/12/16 14:11:00 by cwolf            ###   ########.fr       */
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