/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waon-in <waon-in@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:20:28 by waon-in           #+#    #+#             */
/*   Updated: 2024/03/22 00:23:20 by waon-in          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/libft.h"

static char	**ft_allocate_res(char const *s, char c, size_t *word_count)
{
	int		count;
	int		in_word;
	char	**res;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c && in_word)
			in_word = 0;
		s++;
	}
	res = (char **)malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (NULL);
	*word_count = count;
	return (res);
}

static char	*ft_get_next_word(const char *s, char c, size_t *len)
{
	const char	*start;
	const char	*end;

	while (*s && *s == c)
		s++;
	start = s;
	while (*s && *s != c)
		s++;
	end = s;
	*len = end - start;
	return ((char *)start);
}

static char	**ft_free_mem(char **arr, int words)
{
	int	i;

	i = 0;
	while (i < words && arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char			**res;
	size_t			words;
	size_t			len;
	size_t			i;

	len = 0;
	if (!s)
		return (NULL);
	res = ft_allocate_res(s, c, &words);
	if (!res)
		return (NULL);
	i = 0;
	while (i < words)
	{
		s = ft_get_next_word(s, c, &len);
		res[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!res[i])
			return (ft_free_mem(res, i));
		ft_strlcpy(res[i], s, len + 1);
		res[i][len] = '\0';
		s += len;
		i++;
	}
	res[words] = NULL;
	return (res);
}
