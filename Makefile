# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/07 18:43:07 by youngcho          #+#    #+#              #
#    Updated: 2022/08/20 11:35:49 by youngcho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRCS_DIR = ./srcs/
OBJS_DIR = ./objs/
INCS_DIR = ./incs/

LIBFT_DIR = ./libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)$(LIBFT_NAME)
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
INCS_FLAGS = -I $(INCS_DIR) -I $(LIBFT_DIR)incs/

SRCS_NAME = pipex.c \
			redirect.c \
			execute_command.c \
			error.c
			
OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_NAME))
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))

.PHONY: all clean fclean re
all: $(NAME)
clean :
	make clean -C $(LIBFT_DIR)
	rm -rf $(OBJS_DIR)
fclean : clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
re : fclean
	make all

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(OBJS) -o $@

$(LIBFT) :
	make all -C $(LIBFT_DIR)
	
$(OBJS_DIR)%.o : $(SRCS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCS_FLAGS) -c $< -o $@

$(OBJS_DIR) :
	mkdir $(OBJS_DIR)