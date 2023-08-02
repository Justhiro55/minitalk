/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:47:17 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/08/02 19:24:24 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	*char_to_bin(char c)
{
	int				*bin;
	int				i;
	unsigned int	bit;

	i = 0;
	bin = (int *)malloc(sizeof(int) * 8);
	if (bin == NULL)
		return (NULL);
	while (i < 8)
	{
		bit = (unsigned int)1 << i;
		if ((c & bit) == 0)
			bin[7-i] = 0;
		else
			bin[7-i] = 1;
		i++;
	}
	return (bin);
}

int	main(int ac, char **av)
{
	int	i;
	int	*bin;

	i = 0;
	bin = (int *)malloc(sizeof(int) * 8);
	if (bin == NULL)
		return (0);
	bin = char_to_bin(av[2][0]);
	(void)ac;
	while (i < 8)
	{
		printf("%d\n", bin[i]);
		if (bin[i] == 0)
			kill((pid_t)atoi(av[1]), SIGUSR1);
		else if (bin[i] == 1)
			kill((pid_t)atoi(av[1]), SIGUSR2);
		i++;
		usleep(100);
	}
	return (0);
}
