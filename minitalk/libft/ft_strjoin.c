/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waon-in <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:43:42 by waon-in           #+#    #+#             */
/*   Updated: 2024/03/22 00:24:19 by waon-in          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	char		*str;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(len + 1 * sizeof(char));
	if (!s1 || !s2 || !str)
		return (NULL);
	ft_strlcpy(str, s1, len + 1);
	ft_strlcat(str, s2, len + 1);
	return (str);
}
