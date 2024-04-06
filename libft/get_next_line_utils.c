/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waon-in <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:47:20 by waon-in           #+#    #+#             */
/*   Updated: 2024/03/22 00:35:12 by waon-in          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/get_next_line.h"

int	len_memo(t_gnl *list)
{
	int	i;
	int	len;

	if (list == NULL)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->memo[i])
		{
			if (list->memo[i] == '\n')
			{
				++len;
				return (len);
			}
			++i;
			++len;
		}
		list = list->next;
	}
	return (len);
}

t_gnl	*find_last_node(t_gnl *list)
{
	if (list == NULL)
		return (NULL);
	while (list->next != NULL)
		list = list->next;
	return (list);
}

void	get_str(t_gnl *list, char *str)
{
	int	len;
	int	i;

	if (list == NULL)
		return ;
	len = 0;
	while (list)
	{
		i = 0;
		while (list->memo[i])
		{
			if (list->memo[i] == '\n')
			{
				str[len++] = '\n';
				str[len] = '\0';
				return ;
			}
			str[len++] = list->memo[i++];
		}
		list = list->next;
	}
	str[len] = '\0';
}

int	get_new_line(t_gnl *list)
{
	int	i;

	if (list == NULL)
		return (0);
	while (list)
	{
		i = 0;
		while (list->memo[i] && i < BUFFER_SIZE)
		{
			if (list->memo[i] == '\n')
				return (1);
			++i;
		}
		list = list->next;
	}
	return (0);
}

void	free_node(t_gnl **list, t_gnl *clean_node, char *buf)
{
	t_gnl	*tmp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		free((*list)->memo);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
	if (buf && clean_node->memo[0])
		*list = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
