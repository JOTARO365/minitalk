/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiaon-in <wiaon-in@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:00:00 by wiaon-in          #+#    #+#             */
/*   Updated: 2026/06/04 00:00:00 by wiaon-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
** handle_signal — ประกอบ byte ทีละ bit (MSB-first)
** ใช้ static local เก็บ state ระหว่างการเรียก handler หลายครั้ง
** จึงไม่ต้องใช้ global variable.
** ครบ 8 bit: ถ้าเป็น '\0' = จบ message → ขึ้นบรรทัดใหม่, ไม่งั้น print char.
*/
static void	handle_signal(int sig)
{
	static unsigned char	c = 0;
	static int				bits = 0;

	c = c << 1;
	if (sig == SIGUSR2)
		c = c | 1;
	bits++;
	if (bits == 8)
	{
		if (c == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", c);
		c = 0;
		bits = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_handler = &handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	while (1)
		pause();
	return (0);
}
