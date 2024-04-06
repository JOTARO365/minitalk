/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waon-in <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:59:47 by waon-in           #+#    #+#             */
/*   Updated: 2024/03/30 00:07:15 by waon-in          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/include/libft.h"
#include "libft/include/ft_printf.h"
#include <unistd.h>
#include <signal.h>

static void	send_to_client(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		ft_printf("send : %c\n", c);
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep (300);
		}
	}
}

static void	action(int sig, siginfo_t *info, void *context)
{
	static int				i = 0;
	static pid_t			client_pid = 0;
	static unsigned char	c = 0;

	(void)context;
	if (client_pid != info->si_pid)
	{
		client_pid = info->si_pid;
		ft_printf("\n Client PID : %d\n", client_pid);
		i = 0;
		c = 0;
	}
	c |= (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		write(1, &c, 1);
		if (c == 'Z')
			send_to_client(client_pid, "Z");
		c = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_printf("Wellcome to Minituck : %d\n", getpid());
	s_sigaction.sa_sigaction = action;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sigaction, 0);
	sigaction(SIGUSR2, &s_sigaction, 0);
	while (1)
		usleep(300);
	return (0);
}
