/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelkhiar <oelkhiar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:35:46 by oelkhiar          #+#    #+#             */
/*   Updated: 2023/05/01 14:43:02 by oelkhiar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_lennewline(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*get_stock_newline(char *str_stock)
{
	char	*temp;
	int		a;
	int		i;

	i = 0;
	while (str_stock[i] != '\n')
	{
		if (str_stock[i] == '\0')
			return (free(str_stock), NULL);
		i++;
	}
	a = i + 1;
	while (str_stock[i] != '\0')
		i++;
	temp = ft_substr(str_stock, a, i - a);
	free(str_stock);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*str_stock;
	char		*line;
	int			a;

	a = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (ft_strchr(str_stock, '\n') == 0 && a > 0)
	{
		a = read (fd, buffer, BUFFER_SIZE);
		if (a == -1)
			return (free (str_stock), free (buffer), NULL);
		buffer[a] = '\0';
		str_stock = ft_strjoin(str_stock, buffer);
	}
	free(buffer);
	line = ft_substr(str_stock, 0, ft_lennewline(str_stock) + 1);
	str_stock = get_stock_newline(str_stock);
	return (line);
}
