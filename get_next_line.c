/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelkhiar <oelkhiar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:35:46 by oelkhiar          #+#    #+#             */
/*   Updated: 2023/04/25 15:36:09 by oelkhiar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_lennewline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while(str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*get_after_newline(char *str_stock)
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
	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	buffer = malloc(BUFFER_SIZE + 1);
	if(!buffer)
		return (0);
	while (ft_strchr(str_stock, '\n') == 0, a > 0)
	{
		a = read(fd, buffer, BUFFER_SIZE);
		if (a == -1)
			return (free(buffer), free(str_stock), 0);
		buffer[a] = '\0';
		str_stock = ft_strjoin(str_stock, buffer);
		printf("\n|%s|\n", "ok");
	}
	free(buffer);
	line = ft_substr(str_stock, 0, ft_lennewline(str_stock) + 1);
	printf("\n|%s|\n", str_stock);
	str_stock = get_after_newline(str_stock);
	return (line);
}
int	main(void)
{
	int fd = open("testing.txt", O_RDONLY);

	char *s = get_next_line(fd);
	printf("%s",s);
	
}