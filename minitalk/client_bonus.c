/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waon-in <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 00:33:37 by waon-in           #+#    #+#             */
/*   Updated: 2024/03/30 00:23:10 by waon-in          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"
#include "libft/include/ft_printf.h"
#include <unistd.h>
#include <signal.h>

static void	action(int sig)
{
	static int				i = 0;
	static unsigned char	c = 0;

	c |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		ft_printf("Resevied %c\n", c);
		exit (0);
		c = 0;
	}
	else
		c <<= 1;
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
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(300);
		}
	}
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3 || !ft_strlen(argv[2]))
		handle_errors("Usered : ./ Client Server PID massage");
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i]))
			handle_errors("input is not digit\n");
		i++;
	}
	ft_printf("Cleint PID :%d\n", getpid());
	signal(SIGUSR1, action);
	signal(SIGUSR2, action);
	send_to_server(ft_atoi(argv[1]), argv[2]);
	while (1)
		usleep(300);
	return (0);
}
