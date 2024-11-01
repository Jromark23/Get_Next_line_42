/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joroman- <joroman-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:59:46 by joroman-          #+#    #+#             */
/*   Updated: 2024/11/01 20:21:50 by joroman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Extrae hasta \n incluido”
char *extract_line(char *content)
{
    int i = 0;

    // Si es null o está vacío devolvemos null porque no hay nada que extraer
    if (!content || !*content)
        return NULL;

    // Buscamos el salto de línea o el final de la cadena
    while (content[i] && content[i] != '\n')
        i++;

    // Extraemos la línea incluyendo el salto de línea, si existe
    if (content[i] == '\n')
        return ft_substr(content, 0, i + 1); // Si hay salto de linea (i = tamaño a extraer)
    else
        return ft_substr(content, 0, i);
}

// Extrae desde \n”
char *update_resto(char *content)
{
    int i = 0;
    char *new_content;

    // Localizamos el primer salto de línea
    while (content[i] && content[i] != '\n')
        i++;

    // Si no encontramos un salto de línea, no hay "content" que mantener
    if (!content[i])
    {
        free(content);
        return NULL;
    }

    // Creamos el nuevo "content" empezando justo después del salto de línea
    new_content = ft_substr(content, (i + 1), (ft_strlen(content) - i - 1));
    free(content); // evitamos fugas 
    return new_content;
}

char *get_next_line(int fd)
{
    static char *content;
    char *buffer;
    char *temp;
    char *line;
    int bytes;
       if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
    if (!content)
        content = ft_strdup(""); // Inicializamos content en caso de que sea NULL, usamos strdup para poder liberar la memoria

    buffer = malloc(BUFFER_SIZE + 1); // Reservamos memoria para el buffer + nulo
    if (!buffer)
        return NULL; // ver si podemos meter en la misma linea que el if

    while (!ft_strchr(content, '\n')) // Mientras content no incluya salto de linea 
    {
        bytes = read(fd, buffer, BUFFER_SIZE); // En bytes calculamos cuantos bytes se han leido 
        if (bytes == -1) // Si devuelve -1 es que ha dado error, liberamos el buffer y devolvemos nulo 
        {
            free(buffer);
            return NULL;
        }
        else if (bytes == 0) // Si da cero, salimos del bucle 
            break;
        buffer[bytes] = '\0'; // Al bufer le añadimos el nulo 
        temp = ft_strjoin(content, buffer); // Usamos una variable temporal para unir lo que tenemos con el nuevo buffer 
        if (content)          // Liberamos content, y le igualamos temp para evitar sobreescribir cosas en la memoria tras content
            free(content);
        content = temp;
    }
    free(buffer); // Liberamos buffer para evitar fugas de memoria 

    // Extraemos la línea desde "content"
    line = extract_line(content);
    // Actualizamos "content" para futuras llamadas
    content = update_resto(content);
    return line;
}
