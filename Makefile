# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/07 18:43:07 by youngcho          #+#    #+#              #
#    Updated: 2022/08/07 19:15:20 by youngcho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS_DIR = ./srcs/
OBJS_DIR = ./objs/
INCS_DIR = ./incs/

CC = cc
CFLAGS = -Wall -Werror -Wextra
INCS_FLAGS = -I $(INCS_DIR)

SRCS_NAME = main.c \
			set_args.c
			
OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_NAME))
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))

.PHONY: all clean fclean re
all: $(NAME)
clean :
	rm -rf $(OBJS_DIR)
fclean : clean
	rm -f $(NAME)
re : fclean
	make all

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCS_FLAGS) -c $< -o $@

$(OBJS_DIR) :
	mkdir $(OBJS_DIR)