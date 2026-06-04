/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiaon-in <wiaon-in@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:00:00 by wiaon-in          #+#    #+#             */
/*   Updated: 2026/06/04 00:00:00 by wiaon-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** minitalk.h — Header สำหรับ client/server (mandatory)
**
** Protocol: ส่งทีละ bit ผ่าน 2 signal เท่านั้น
**   SIGUSR1 = bit 0
**   SIGUSR2 = bit 1
** ส่งแบบ MSB-first ครบ 8 bit ได้ 1 byte. client ปิดท้ายด้วย '\0'
** เพื่อบอก server ว่าจบ message.
*/

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/ft_printf.h"

#endif
