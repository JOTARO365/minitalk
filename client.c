/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiaon-in <wiaon-in@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:00:00 by wiaon-in          #+#    #+#             */
/*   Updated: 2026/06/04 00:00:00 by wiaon-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
** send_byte — ส่ง 1 byte ทีละ bit (MSB-first) ไปยัง server ผ่าน kill().
** bit 1 → SIGUSR2, bit 0 → SIGUSR1. usleep ให้ server ทันประมวลผล
** เนื่องจาก mandatory ไม่มี ack กลับมา.
*/
static void	send_byte(int pid, unsigned char c)
{
	int	bit;

	bit = 8;
	while (bit > 0)
	{
		bit--;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(400);
	}
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
	i = 0;
	while (argv[2][i])
		send_byte(pid, argv[2][i++]);
	send_byte(pid, '\0');
	return (0);
}
