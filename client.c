/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:47:17 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/08/05 20:26:36 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
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
			bin[7 - i] = 0;
		else
			bin[7 - i] = 1;
		i++;
	}
	return (bin);
}

void	send_string(int pid, int len, char *str)
{
	int	i;
	int	j;
	int	*bin;

	i = 0;
	j = 0;
	bin = (int *)malloc(sizeof(int) * 8);
	if (bin == NULL)
		return ;
	while (j < len + 1)
	{
		if (str[j] == '\0')
			str[j] = '\n';
		bin = char_to_bin(str[j]);
		while (i < 8)
		{
			if (bin[i] == 0)
				kill((pid_t)pid, SIGUSR1);
			else if (bin[i] == 1)
				kill((pid_t)pid, SIGUSR2);
			i++;
			usleep(100);
		}
		i = 0;
		j++;
	}
}

int	check_error(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 3 || !av[2])
	{
		ft_printf("Error\n");
		return (1);
	}
	if ((pid_t)atoi(av[1]) < 100 || 99999 <= (pid_t)atoi(av[1]))
		return (1);
	while (av[1][i] != '\0')
	{
		if (!('0' <= av[1][i] && av[1][i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (check_error(ac, av))
		return (1);
	send_string((pid_t)atoi(av[1]), strlen(av[2]), av[2]);
	return (0);
}
