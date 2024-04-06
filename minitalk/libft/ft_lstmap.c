/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waon-in <waon-in@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:26:37 by waon-in           #+#    #+#             */
/*   Updated: 2024/03/22 00:17:41 by waon-in          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f) (void *), void (*del)(void *))
{
	t_list	*tmplst;
	t_list	*new_lst;
	void	*tmpcontent;

	new_lst = NULL;
	while (lst)
	{
		tmpcontent = f(lst->content);
		tmplst = ft_lstnew(tmpcontent);
		if (!tmplst)
		{
			del(tmpcontent);
			if (new_lst)
				ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, tmplst);
		lst = lst->next;
	}
	return (new_lst);
}
