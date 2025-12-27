/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:10:38 by cwolf             #+#    #+#             */
/*   Updated: 2025/12/27 10:52:19 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int main (int argc, char *argv[])
{
    FILE *file;
    
    if (argc == 2)
    {
        file = fopen(argv[1], "r");
        if (!file)
        {
            fprintf(stderr, "map error\n");
            return -1;
        }
        if (execute(file)  == -1)
        {
            fprintf(stderr, "map error\n");
            return -1;
        }
    }
    else if (argc == 1)
    {
        file = stdin;
        if (execute(file) == -1)
        {
            fprintf(stderr, "map error\n");
        }
    }
    if (file)
        fclose(file); 
    return 0;
}