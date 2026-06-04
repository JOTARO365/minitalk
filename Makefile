# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wiaon-in <wiaon-in@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/04 00:00:00 by wiaon-in          #+#    #+#              #
#    Updated: 2026/06/04 00:00:00 by wiaon-in         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER		= server
CLIENT		= client
NAME		= $(SERVER) $(CLIENT)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
INC			= -I. -I$(LIBFT_DIR)

HEADER		= minitalk.h
HEADER_B	= minitalk_bonus.h

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(SERVER): server.o $(LIBFT)
	$(CC) $(CFLAGS) $(INC) -o $(SERVER) server.o $(LIBFT)

$(CLIENT): client.o $(LIBFT)
	$(CC) $(CFLAGS) $(INC) -o $(CLIENT) client.o $(LIBFT)

server.o: server.c $(HEADER)
	$(CC) $(CFLAGS) $(INC) -c server.c -o server.o

client.o: client.c $(HEADER)
	$(CC) $(CFLAGS) $(INC) -c client.c -o client.o

bonus: server_bonus client_bonus

server_bonus: server_bonus.o $(LIBFT)
	$(CC) $(CFLAGS) $(INC) -o $(SERVER) server_bonus.o $(LIBFT)

client_bonus: client_bonus.o $(LIBFT)
	$(CC) $(CFLAGS) $(INC) -o $(CLIENT) client_bonus.o $(LIBFT)

server_bonus.o: server_bonus.c $(HEADER_B)
	$(CC) $(CFLAGS) $(INC) -c server_bonus.c -o server_bonus.o

client_bonus.o: client_bonus.c $(HEADER_B)
	$(CC) $(CFLAGS) $(INC) -c client_bonus.c -o client_bonus.o

clean:
	rm -f server.o client.o server_bonus.o client_bonus.o
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(SERVER) $(CLIENT)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

norm:
	python3 -m norminette *.c *.h $(LIBFT_DIR)

.PHONY: all bonus clean fclean re norm
