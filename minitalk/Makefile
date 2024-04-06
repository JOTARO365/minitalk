# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waon-in <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/22 00:36:13 by waon-in           #+#    #+#              #
#    Updated: 2024/03/30 00:54:09 by waon-in          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server
NAME_CLIENT = client
NAME_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus

OBJ_DIR = bin
CC = cc
CFLAGS = -Wall -Werror -Wextra
RM = rm

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_FILE = server
SRC_CLIENT_FILE = client
SRC_FILE_BONUS = server_bonus
SRC_CLIENT_FILE_BONUS = client_bonus

SRC = $($(addsuffix .c, $(SRC_FILE)))
SRC_CLIENT = $($(addsuffix .c, $(SRC_CLIENT_FILE)))
SRC_BONUS = $($(addsuffix .c, $(SRC_FILE_BONUS)))
SRC_CLIENT_BONUS = $($(addsuffix .c, $(SRC_CLIENT_FILE_BONUS)))

OBJ = $(addprefix $(OBJ_DIR)/server/, $(addsuffix .o, $(SRC_FILE)))
OBJ_CLIENT = $(addprefix $(OBJ_DIR)/client/, $(addsuffix .o, $(SRC_CLIENT_FILE)))
OBJ_BONUS = $(addprefix $(OBJ_DIR)/server_bonus/, $(addsuffix .o, $(SRC_FILE_BONUS)))
OBJ_CLIENT_BONUS = $(addprefix $(OBJ_DIR)/client_bonus/, $(addsuffix .o, $(SRC_CLIENT_FILE_BONUS)))

$(OBJ_DIR)/server/%.o: %.c
	@mkdir -p $(OBJ_DIR)/server
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/client/%.o: %.c
	@mkdir -p $(OBJ_DIR)/client
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/server_bonus/%.o: %.c
	@mkdir -p $(OBJ_DIR)/server_bonus
	$(CC) $(CFAGS) -c $< -o $@

$(OBJ_DIR)/client_bonus/%.o: %.c
	@mkdir -p $(OBJ_DIR)/client_bonus
	$(CC) $(CFAGS) -c $< -o $@

all:	$(NAME) $(NAME_CLIENT)

bonus:	$(NAME_BONUS) $(NAME_CLIENT_BONUS)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

$(NAME_BONUS): $(OBJ_BONUS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) -o $(NAME_BONUS)

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) $(LIBFT) -o $(NAME_CLIENT_BONUS)

clean:
	$(RM) -rf $(OBJ_DIR)
	$(RM) -f $(NAME) $(NAME_CLIENT)
	$(RM) -f $(NAME_BONUS) $(NAME_CLIENT_BONUS)
	$(RM) -f $(LIBFT_DIR)libft.a
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) clean

re: fclean all

.PHONY: all bonus  clean fclean re 
