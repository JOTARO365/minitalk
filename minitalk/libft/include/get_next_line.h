/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waon-in <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:08:39 by waon-in           #+#    #+#             */
/*   Updated: 2024/03/29 23:34:25 by waon-in          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42

# endif

typedef struct s_gnl
{
	char			*memo;
	struct s_gnl	*next;
}	t_gnl;

char		*get_next_line(int fd);
char		*ft_next_line(t_gnl *list);
int			len_memo(t_gnl *list);

t_gnl		*find_last_node(t_gnl *list);
int			get_new_line(t_gnl *list);

void		get_str(t_gnl *list, char *str);
char		create_list(t_gnl **list, int fd);
void		ft_append(t_gnl **list, char *buf);
void		free_node(t_gnl **list, t_gnl *clean_node, char *buf);
void		list_check(t_gnl **list);

#endif
