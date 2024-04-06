/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waon-in <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:14:04 by waon-in           #+#    #+#             */
/*   Updated: 2024/03/22 00:28:03 by waon-in          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	const char	*strn1;
	const char	*strn2;
	char		*str;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	strn1 = s1;
	strn2 = s1 + ft_strlen(s1);
	while (strn2 > strn1 && ft_strchr(set, *(strn2 - 1)))
		strn2--;
	i = strn2 - strn1;
	if (i == 0)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, strn1, i + 1);
	return (str);
}
