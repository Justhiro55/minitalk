/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 14:47:23 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/08/05 20:23:42 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
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
	ft_putchar_fd(c, 0);
}

void	signal_handle(int sig)
{
	static int	*bin;

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
		free(bin);
		bin = NULL;
	}
	g_i++;
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = signal_handle;
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	g_i = 0;
	// ft_putstr_fd("--Server started--\n", 0);
	// ft_printf("PID: %d\n", getpid());
	// ft_putstr_fd("Waiting for signal...\n", 0);
	while (1)
	{
		if (g_i == 8)
			g_i = 0;
		pause();
	}
	return (0);
}
