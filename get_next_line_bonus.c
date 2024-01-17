/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntsvetko <ntsvetko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:53:03 by ntsvetko          #+#    #+#             */
/*   Updated: 2023/11/09 13:32:06 by ntsvetko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_line(int fd, char *str)
{
	char	*buf;
	int		bytes_read;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf);
			if (str)
				free(str);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		if (!str)
			str = ft_strdup(buf);
		else
			str = ft_strjoin(str, buf);
		if (ft_strchr(str, '\n') || bytes_read == 0)
			break ;
	}
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*tmp;
	char		*line;
	int			l;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		if (str[fd])
			free(str[fd]);
		return (0);
	}
	str[fd] = get_line(fd, str[fd]);
	if (!str[fd])
		return (0);
	l = ft_strchr(str[fd], '\n') - str[fd] + 1;
	line = ft_substr(str[fd], 0, l);
	tmp = str[fd];
	str[fd] = ft_substr(str[fd], l, (ft_strlen(str[fd]) - l));
	free(tmp);
	return (line);
}

// int main()
// {
// 	int fd1, fd2;
// 	fd1 = open("file.txt", O_RDONLY);
// 	fd2 = open("file2.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd2));
// 	printf("%s", get_next_line(fd1));
// 	printf("%s", get_next_line(fd2));
// }