/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_comentado.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joroman- <joroman-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:59:46 by joroman-          #+#    #+#             */
/*   Updated: 2024/11/02 18:34:06 by joroman-         ###   ########.fr       */
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
char *update_content(char *content)
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

int	read_line(int fd, char **content, char *buffer)
{
	char	*temp;
	int		bytes;

	// Leemos hasta encontrar N
	while (!ft_strchr(*content, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);  // leemos y sacamos cuantos bytes se han leido 
		if (bytes == -1)
		{
			free(*content);
			*content = NULL;
			return (-1); // -1 error lectura, liberamos el content y devolvemos -1 
		}
		else if (bytes == 0) // Si da cero, salimos del bucle por EOF
			return (0);
		buffer[bytes] = '\0';  // Al bufer le añadimos el nulo 
		temp = ft_strjoin(*content, buffer);  // Usamos una variable temporal para unir lo que tenemos con el nuevo buffer 
		if (*content)
			free(*content); // Liberamos content, y le igualamos temp para evitar sobreescribir cosas en la memoria tras content
		*content = temp;   
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*content;
	char		*buffer;
	char		*line;
	int			status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!content)
		content = ft_strdup("");	// Inicializamos content en caso de que sea NULL, usamos strdup para poder liberar la memoria
	status = read_line(fd, &content, buffer); // leemos la linea completa y registramos si ha habido error
	free(buffer);
	if (status == -1)
		return (NULL);
	line = extract_line(content);
	content = update_content(content); // Dejamos despues de N si hay algo. 
	return (line);
}
