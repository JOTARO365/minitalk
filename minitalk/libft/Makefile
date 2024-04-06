# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waon-in <waon-in@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/16 19:50:19 by waon-in           #+#    #+#              #
#    Updated: 2024/03/29 23:32:17 by waon-in          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c
SRCS += ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c
SRCS += ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c
SRCS += ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c
SRCS += ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c
SRCS += ft_strtrim.c ft_strmapi.c ft_striteri.c ft_itoa.c ft_putchar_fd.c
SRCS += ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c
SRCS += ft_printf.c ft_printf_utils.c get_next_line.c get_next_line_utils.c
SRCS += handle_errors.c

SRCS_BONUS = $(SRCS) ft_lstnew.c ft_lstadd_front.c  ft_lstsize.c ft_lstlast.c
SRCS_BONUS += ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

$(NAME) : $(OBJS_BONUS) include/libft.h include/get_next_line.h include/ft_printf.h
	ar rcs $(NAME) $(OBJS)

%.o : %.c 
	$(CC) $(CFLAGS) -c $^ -o $@

all : $(NAME)

clean : 
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean : clean
	rm -rf $(NAME)

re :
	make fclean
	make

bonus: all
	ar rcs $(NAME) $(OBJS_BONUS)

.PHONY : all clean fclean re bonus
