/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelkhiar <oelkhiar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:23:26 by oelkhiar          #+#    #+#             */
/*   Updated: 2023/04/23 14:23:27 by oelkhiar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char staticFunc()
{
    static int count = 0;
    printf("count :%d \n",count);
    count++;
}

int main()
{
    staticFunc();
    staticFunc();
    staticFunc();
    staticFunc();
}