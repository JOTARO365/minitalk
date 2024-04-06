/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waon-in <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 01:41:11 by waon-in           #+#    #+#             */
/*   Updated: 2024/03/27 23:16:07 by waon-in          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"
#include "libft/include/ft_printf.h"
#include <unistd.h>
#include <signal.h>

static void	action(int pid)
{
	if (SIGUSR2 == pid)
		ft_printf("received input to server.\n");
}

static void	send_to_server(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
			{
				if (kill(pid, SIGUSR2) == -1)
					exit (1);
			}
			else
			{
				if (kill(pid, SIGUSR1) == -1)
					exit (1);
			}
			usleep (300);
		}
	}
	exit (0);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3 || !ft_strlen(argv[2]))
		handle_errors(" please input argument\n");
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]))
			handle_errors("input is not digit\n");
		i++;
	}
	ft_printf("Client PID : %d\n", getpid());
	signal(SIGUSR2, action);
	signal(SIGUSR1, action);
	send_to_server(ft_atoi(argv[1]), argv[2]);
	while (1)
		usleep(300);
	return (0);
}
