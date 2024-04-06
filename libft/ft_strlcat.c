/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waon-in <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:47:03 by waon-in           #+#    #+#             */
/*   Updated: 2024/03/22 00:24:34 by waon-in          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	i = 0;
	j = dst_len;
	while (src[i] != '\0' && j + 1 < dstsize)
		dst[j++] = src[i++];
	dst[j] = '\0';
	return (ft_strlen(dst) + ft_strlen(src + i));
}
