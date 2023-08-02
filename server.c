/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:47:23 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/08/02 19:34:34 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int		g_i;

int	binary_to_decimal(int *bin)
{
	int	decimal;
	int	i;

	decimal = 0;
	i = 0;
	while (i < 8)
	{
		decimal = decimal * 2 + bin[i];
		i++;
	}
	return (decimal);
}

void	bin_to_char(int *bin)
{
	int				i;
	unsigned int	c;

	i = 0;
	c = 0;
	c = binary_to_decimal(bin);
	printf("char:%c\n", c);
}

void	signal_handle(int sig)
{
	int	*bin;

	if (bin == NULL)
		bin = (int *)malloc(sizeof(int) * 8);
	if (bin == NULL)
		return ;
	if (sig == SIGUSR1)
		bin[g_i] = 0;
	else if (sig == SIGUSR2)
		bin[g_i] = 1;
	if (g_i == 7)
	{
		bin_to_char(bin);
	}
	g_i++;
}

int	main(void)
{
	g_i = 0;
	printf("--Server started--\n");
	printf("PID: %d\n", getpid());
	signal(SIGUSR1, signal_handle);
	signal(SIGUSR2, signal_handle);
	printf("Waiting for signal...\n");
	while (1)
	{
		pause();
		if (g_i == 8)
			g_i = 0;
	}
	return (0);
}
