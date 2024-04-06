/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waon-in <waon-in@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:01:18 by waon-in           #+#    #+#             */
/*   Updated: 2024/03/22 00:16:14 by waon-in          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*new_lst;

	if (*lst)
	{
		new_lst = ft_lstlast(*lst);
		new_lst->next = new;
	}
	else
		*lst = new;
}
