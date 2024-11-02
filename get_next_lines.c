/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_lines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joroman- <joroman-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:59:46 by joroman-          #+#    #+#             */
/*   Updated: 2024/11/02 18:14:11 by joroman-         ###   ########.fr       */
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

char	*get_next_line(int fd)
{
	static char	*content;
	char		*buffer;
	char		*temp;
	char		*line;
	int			bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || !buffer)
		return (NULL);
	if (!content)
		content = ft_strdup("");
	while (!ft_strchr(content, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(content);
			content = NULL;
			return (NULL);
		}
		else if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		temp = ft_strjoin(content, buffer);
		if (content)
			free(content);
		content = temp;
	}
	free(buffer);
	line = extract_line(content);
	content = update_content(content);
	return (line);
}
