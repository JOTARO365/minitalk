/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiaon-in <wiaon-in@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:00:00 by wiaon-in          #+#    #+#             */
/*   Updated: 2026/06/04 00:00:00 by wiaon-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

/*
** g_ack — global เดียวที่ใช้ใน client (subject อนุญาต 1 ตัว).
** จำเป็นเพราะ handler ต้องสื่อสารกับ loop หลักว่า server ack มาแล้ว.
**   0 = กำลังรอ ack, 1 = ได้รับ ack ของ bit, 2 = ได้รับ ack จบ message.
*/
volatile sig_atomic_t	g_ack = 0;

static void	ack_handler(int sig)
{
	if (sig == SIGUSR2)
		g_ack = 2;
	else
		g_ack = 1;
}

/*
** send_byte — ส่งทีละ bit แล้วรอ ack จาก server ก่อนส่ง bit ถัดไป.
** ทำให้เร็วและไม่หลุด signal เพราะ sync กันแบบ lock-step.
*/
static void	send_byte(int pid, unsigned char c)
{
	int	bit;

	bit = 8;
	while (bit > 0)
	{
		bit--;
		g_ack = 0;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		while (g_ack == 0)
			usleep(1);
	}
}

static void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc != 3)
	{
		ft_printf("Usage: %s <server_pid> <message>\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_printf("Error: invalid PID\n");
		return (1);
	}
	setup_signals();
	i = 0;
	while (argv[2][i])
		send_byte(pid, argv[2][i++]);
	send_byte(pid, '\0');
	ft_printf("Message delivered!\n");
	return (0);
}
