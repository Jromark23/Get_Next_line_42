/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joroman- <joroman-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:07:21 by joroman-          #+#    #+#             */
/*   Updated: 2024/11/05 12:36:22 by joroman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h> 
#include "get_next_line.h"


// valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file=valgrind_log.txt ./NOMBRE ARCHIVO A USAR

int main(int argc, char **argv)
{
    int fd;
    char *line;
	int i;

	i = 0;
    if (argc == 2)
    {
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
        {
            printf("Error en el open\n");
            return 1;
        }
    }
    else
    {
        fd = 0; 
        printf("Leyendo stdin: \n");
    }
    line = get_next_line(fd);
    while (line != NULL)
    {
        printf("Línea %d. %s", ++i, line);
        free(line);
        line = get_next_line(fd); 
    }
	printf("\n");
    if (fd != 0)
        close(fd);
    return (0);
}

// int    main(void)
// {
//     int     fpointer;
//     char    *singleLine = malloc(1 * sizeof(char));

//     fpointer = open("test.txt", 256);
//     while(singleLine != NULL)
//     {
//         free(singleLine);
//         singleLine = get_next_line(fpointer);
//         printf("%s", singleLine);
//     }
//     return (0);
// }