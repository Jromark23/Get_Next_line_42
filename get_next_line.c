/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joroman- <joroman-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:59:46 by joroman-          #+#    #+#             */
/*   Updated: 2024/11/05 12:47:16 by joroman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *content)
{
	int	i;

	i = 0;
	if (!content || !*content)
		return (NULL);
	while (content[i] && content[i] != '\n')
		i++;
	if (content[i] == '\n')
		return (ft_substr(content, 0, i + 1));
	else
		return (ft_substr(content, 0, i));
}

char	*update_content(char *content)
{
	int		i;
	char	*new_content;

	i = 0;
	while (content[i] && content[i] != '\n')
		i++;
	if (!content[i])
	{
		free(content);
		return (NULL);
	}
	new_content = ft_substr(content, (i + 1), (ft_strlen(content) - i - 1));
	free(content);
	return (new_content);
}

int	read_line(int fd, char **content, char *buffer)
{
	char	*temp;
	int		bytes;

	while (!ft_strchr(*content, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(*content);
			*content = NULL;
			return (-1);
		}
		else if (bytes == 0)
			return (0);
		buffer[bytes] = '\0';
		temp = ft_strjoin(*content, buffer);
		if (*content)
			free(*content);
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
		content = ft_strdup("");
	status = read_line(fd, &content, buffer);
	free(buffer);
	if (status == -1)
		return (NULL);
	line = extract_line(content);
	content = update_content(content);
	return (line);
}
