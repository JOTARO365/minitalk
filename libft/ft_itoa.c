/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waon-in <waon-in@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:20:16 by waon-in           #+#    #+#             */
/*   Updated: 2024/03/22 00:15:52 by waon-in          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

static int	ft_get_num(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	ft_fill_str(int n, char *str, int len)
{
	while (n)
	{
		str[--len] = (n % 10) + '0';
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_get_num(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		if (n == -2147483648)
		{
			str[1] = '2';
			n = 147483648;
		}
		else
			n = -n;
	}
	else if (n == 0)
		str[0] = '0';
	ft_fill_str(n, str, len);
	return (str);
}
