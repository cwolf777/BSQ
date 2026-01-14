/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwolf <cwolf@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:10:38 by cwolf             #+#    #+#             */
/*   Updated: 2026/01/14 18:12:53 by cwolf            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int main (int argc, char *argv[])
{
    FILE *file;

    if (argc == 1)
    {
        if (execute(stdin) == -1)
        {
            fprintf(stderr, "map error\n");
        }
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            file = fopen(argv[i], "r");
            if (!file)
            {
                fprintf(stderr, "map error\n");
            }
            else
            {
                if (execute(file) == -1)
                {
                    fprintf(stderr, "map error\n");
                }
                fclose(file);
            }
            
            if (i < argc - 1)
            {
                fprintf(stdout, "\n");
            }
        }
    }
    return 0;
}