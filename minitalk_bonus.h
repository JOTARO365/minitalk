/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiaon-in <wiaon-in@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:00:00 by wiaon-in          #+#    #+#             */
/*   Updated: 2026/06/04 00:00:00 by wiaon-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** minitalk_bonus.h — Header สำหรับ client/server (bonus)
**
** เพิ่มจาก mandatory:
**   - Acknowledgement: server ส่ง signal กลับทุก bit ที่รับ
**     SIGUSR1 = ack ปกติ, SIGUSR2 = ack ตัวสุดท้าย (จบ message)
**   - Unicode: ส่งทีละ byte ของ string จึงรองรับ multi-byte UTF-8
**     โดยอัตโนมัติ (เช่น ภาษาไทย, emoji)
*/

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/ft_printf.h"

#endif
