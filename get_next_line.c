/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemenet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 10:34:57 by jdemenet          #+#    #+#             */
/*   Updated: 2020/12/09 10:35:02 by jdemenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char				*ft_read_and_join(char *str, int fd, int *ret)
{
	char			buff[BUFFER_SIZE + 1];
	char			*tmp;

	while ((*ret = read(fd, &buff, BUFFER_SIZE)) > 0)
	{
		// if (*ret == -1)
		// 	return (str);
		buff[*ret] = 0;
		if (str)
		{
			tmp = ft_strjoin(str, buff);
			free(str);
			str = ft_strdup(tmp);
			free(tmp);
		}
		else
			str = ft_strdup(buff);
	}
	return (str);
}

char				*ft_write_line(char *str, char **line, int ret)
{
	unsigned int	i;
	char			*tmp;

	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (i < ft_strlen(str))
	{
		*line = ft_substr(str, 0, i);
		tmp = ft_substr(str, i + 1, ft_strlen(str));
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
	}
	else if (ret == 0)
	{
		*line = str;
		str = NULL;
	}
	return (str);
}

int					get_next_line(int fd, char **line)
{
	static char		*str;
	int				ret;

	if (fd < 0 || !line || BUFFER_SIZE < 1)
		return (-1);
	str = ft_read_and_join(str, fd, &ret);
	if (ret == -1)
		return (-1);
	if (ret == 0 && !str)
	{
		*line = ft_strdup("");
		return (0);
	}
	str = ft_write_line(str, line, ret);
	if (ret == 0 && !str)
		return (0);
	return (1);
}
