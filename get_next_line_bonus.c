/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:40:00 by hnaciri-          #+#    #+#             */
/*   Updated: 2021/11/16 20:01:50 by hnaciri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	if (!s)
		return (0);
	str = (char *) s;
	while (*str)
	{
		if ((char)c == *str)
			return (str);
		str++;
	}
	if (*str == (char)c)
		return (str);
	return (0);
}

char	*ft_new_stock(int fd, char *stock)
{
	char	*string;
	int		readed;

	string = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	readed = 1;
	while (!ft_strchr(stock, '\n') && readed)
	{
		readed = read (fd, string, BUFFER_SIZE);
		if (readed < 0)
		{
			free (string);
			return (stock);
		}
		string[readed] = '\0';
		stock = ft_strjoin(stock, string);
	}
	free (string);
	return (stock);
}

char	*ft_line(const char *stock)
{
	int		i;
	char	*line;

	i = 0;
	if (!stock || !stock[i])
		return (0);
	while (stock[i] && stock[i] != '\n')
		i++;
	if (!stock[i])
	{
		line = malloc (sizeof(char) * (i + 1));
		i = -1;
		while (stock[++i])
			line[i] = stock[i];
		line[i] = stock[i];
		return (line);
	}
	line = malloc (sizeof(char) * (i + 2));
	i = -1;
	while (stock[++i] != '\n')
		line[i] = stock[i];
	line[i] = stock[i];
	line[++i] = '\0';
	return (line);
}

char	*ft_move(char *stock)
{
	int		i;
	int		j;
	char	*stock_move;

	i = 0;
	j = 0;
	if (!stock)
		return (0);
	while (stock[i] != '\n' && stock[i])
		i++;
	if (!stock[i])
	{
		free (stock);
		return (0);
	}
	i++;
	stock_move = malloc (sizeof(char) * (ft_strlen(stock) - i + 2));
	if (!stock_move)
		return (0);
	while (stock[i])
		stock_move[j++] = stock[i++];
	stock_move[j] = '\0';
	free (stock);
	return (stock_move);
}

char	*get_next_line(int fd)
{
	static char	*stock[MAX_FILE];
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	if (!ft_strchr(stock[fd], '\n'))
		stock[fd] = ft_new_stock(fd, stock[fd]);
	line = ft_line(stock[fd]);
	stock[fd] = ft_move(stock[fd]);
	return (line);
}
