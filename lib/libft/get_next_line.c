/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbarrett <fbarrett@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 14:26:19 by fbarrett          #+#    #+#             */
/*   Updated: 2024/01/07 13:04:59 by fbarrett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	read_file(int fd, char *buf_static)
{
	int	read_size;
	int	return_value;

	return_value = 0;
	read_size = read(fd, buf_static, BUFFER_SIZE);
	if (read_size < 0 || buf_static[0] == '\4')
	{
		read_size = 0;
		return_value = -1;
	}
	else
		write(0, buf_static, read_size);
	while (read_size < BUFFER_SIZE)
	{
		buf_static[read_size] = 0;
		read_size++;
	}
	buf_static[read_size] = '\0';
	return (return_value);
}

static int	finish_get_line(char *temp_buf, char *temp_buf2, char **return_buf)
{
	if (!*return_buf)
	{
		*return_buf = ft_strdup(temp_buf);
		free(temp_buf);
	}
	else
	{
		*return_buf = ft_strjoin(temp_buf2, temp_buf);
		free(temp_buf2);
		free(temp_buf);
	}
	return (1);
}

static void	save_it(char *temp_buf2,
		char *buf_static_start, int a, char **return_buf)
{
	char	*temp_buf;

	if (!*return_buf)
		*return_buf = ft_strdup(buf_static_start);
	else
	{
		temp_buf = ft_substr(buf_static_start, 0, a + 1);
		*return_buf = ft_strjoin(temp_buf2, temp_buf);
		free(temp_buf2);
		free(temp_buf);
	}
}

static int	get_line(int i, char **return_buf, char *buf_static, int fd)
{
	int		a;
	char	*temp_buf;
	char	*temp_buf2;

	a = 0;
	if (*return_buf)
		temp_buf2 = *return_buf;
	while ((i + a) < BUFFER_SIZE && buf_static[i + a] 
		&& buf_static[i + a] != '\n')
		a++;
	if ((i + a) < BUFFER_SIZE || buf_static[i + a] == '\n')
		return (temp_buf = ft_substr(&buf_static[i], 0, a + 1), 
			finish_get_line(temp_buf, temp_buf2, return_buf));
	else
	{
		save_it(temp_buf2, &buf_static[i], a, return_buf);
		a = read_file(fd, buf_static);
		if (a < 0)
		{
			if (*return_buf)
				free (*return_buf);
			return (-1);
		}
		return (get_line(0, return_buf, buf_static, fd));
	}
}

char	*get_next_line(int fd)
{
	static char	buf_static[BUFFER_SIZE + 1];
	char		*return_buf;
	int			i;

	i = 0;
	return_buf = 0;
	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	while (i < BUFFER_SIZE && !buf_static[i])
		i++;
	if (i == BUFFER_SIZE)
	{
		i = read_file(fd, buf_static);
		if (!buf_static[0] || i < 0)
			return (NULL);
	}
	if (get_line(i, &return_buf, buf_static, fd) < 0)
		return (NULL);
	if (buf_static[0])
		i = 0;
	while (buf_static[i] != '\n' && i <= BUFFER_SIZE && buf_static[i])
		buf_static[i++] = 0;
	if (buf_static[i] == '\n')
		buf_static[i] = 0;
	return (return_buf);
}
