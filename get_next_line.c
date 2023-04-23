/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelkhiar <oelkhiar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 18:35:46 by oelkhiar          #+#    #+#             */
/*   Updated: 2022/12/12 18:20:29 by oelkhiar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h";
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 42

int ft_lennewline(char *str)
{
    int i;

    i = 0;
    if(str == 0)
        return (0);
    while(str[i] != '\0')
    {
        if(str[i] == '\n')
            return (i);
        i++;
    }
    write(1, &i, 1);
    return (i);
}

char *get_next_line(int fd)
{
    char        *buffer;
    static char *str_stock;
    char        *line;
    int         a;

    if (fd < 0 || BUFFER_SIZE < 1)
        return(0);
    buffer = malloc(BUFFER_SIZE + 1);
    if(!buffer)
        return (0);
    while (ft_strchr(str_stock ,'\n') == 0 ,a > 0)
    {
        a = read(fd, buffer, BUFFER_SIZE);
        if (a < 0)
            return(free(buffer), 0);
        buffer[a] = '\0';
        str_stock = ft_strjoin(str_stock,buffer);

    };
    free(buffer);
    line = ft_substr(str_stock,0, ft_lennewline(str_stock) + 1);
    return (line);
}


int main()
{
    int fd = open("testing.txt", O_RDONLY);
    printf("%s",get_next_line(fd));
    printf("%s",get_next_line(fd));
    close(fd);
}