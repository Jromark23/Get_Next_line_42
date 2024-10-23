/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joroman- <joroman-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:00:00 by joroman-          #+#    #+#             */
/*   Updated: 2024/10/22 18:00:00 by joroman-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

// Duplicates a string allocating new memory and returns a pointer to the new one.
char	*ft_strdup(const char *s)
{
	size_t		len;
	char		*aux;

	len = ft_strlen(s);
	aux = malloc(len + 1);
	if (!(aux))
		return (NULL);
	aux[len] = '\0';
	while (len--)
		aux[len] = s[len];
	return (aux);
}
// Returns the length of a string.
size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s++)
		count++;
	return (count);
}

// Finds the first occurrence of a character in a string. 
// Returns a pointer to the character or NULL if not found.
char	*ft_strchr(const char *s, int c)
{
	if ((char)c == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

// Joins two strings into a new string. Returns a pointer to the new string.
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < len1)
		result[i] = s1[i];
	while (++j < len2)
		result[i + j] = s2[j];
	result[i + j] = '\0';
	return (result);
}