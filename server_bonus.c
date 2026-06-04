/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiaon-in <wiaon-in@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:00:00 by wiaon-in          #+#    #+#             */
/*   Updated: 2026/06/04 00:00:00 by wiaon-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/*
** print_byte — ครบ 8 bit แล้ว print และ ack กลับไปหา client.
** ตัวสุดท้ายของ message ('\0') ตอบกลับด้วย SIGUSR2 เพื่อบอกว่า "จบแล้ว",
** bit อื่นตอบกลับด้วย SIGUSR1.
*/
static void	print_byte(unsigned char c, pid_t client)
{
	if (c == '\0')
	{
		ft_printf("\n");
		kill(client, SIGUSR2);
	}
	else
	{
		ft_printf("%c", c);
		kill(client, SIGUSR1);
	}
}

/*
** handle_signal — รับ siginfo เพื่อรู้ PID ของ client (si_pid)
** ประกอบ byte ทีละ bit ด้วย static local แล้ว ack ทุก bit.
*/
static void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	c = 0;
	static int				bits = 0;

	(void)ucontext;
	c = c << 1;
	if (sig == SIGUSR2)
		c = c | 1;
	bits++;
	if (bits == 8)
	{
		print_byte(c, info->si_pid);
		c = 0;
		bits = 0;
	}
	else
		kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = &handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	while (1)
		pause();
	return (0);
}
