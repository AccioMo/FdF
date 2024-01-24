/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzeggaf <mzeggaf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 00:38:05 by mzeggaf           #+#    #+#             */
/*   Updated: 2024/01/11 22:49:16 by mzeggaf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strncpy(char *dest, char *src, int n)
{
	while (n > 0 && *src)
	{
		*dest = *src;
		dest++;
		src++;
		n--;
	}
	*dest = '\0';
	return (dest);
}

static char	*ft_realloc_n(char *src, char *buffer, int n)
{
	char	*str;
	int		l_src;

	if (n < 0)
		return (src);
	l_src = ft_strlen(src);
	str = (char *)malloc(sizeof(char) * (l_src + n + 1));
	if (!str)
		return (free(src), NULL);
	ft_strncpy(ft_strncpy(str, src, l_src), buffer, n);
	if (src)
		free(src);
	return (str);
}

char	*ft_fopen(int fd)
{
	int		rd;
	char	*buffer;
	char	*contents;

	rd = 1;
	contents = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (close(fd), NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (close(fd), NULL);
	buffer[BUFFER_SIZE] = '\0';
	while (rd > 0)
	{
		rd = read(fd, buffer, BUFFER_SIZE);
		contents = ft_realloc_n(contents, buffer, rd);
		if (!contents)
			return (close(fd), free(buffer), NULL);
	}
	close(fd);
	free(buffer);
	return (contents);
}
