# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/07 18:43:07 by youngcho          #+#    #+#              #
#    Updated: 2022/08/20 13:07:52 by youngcho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Werror -Wextra -g

LIBFT_DIR = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_DIR)$(LIBFT_NAME)
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

ifeq ($(findstring bonus, $(MAKECMDGOALS)), bonus)
	PART = bonus/
	SRCS_NAME = pipex.c \
			redirect.c \
			execute_command.c \
			error.c
else
	PART = mandatory/
	SRCS_NAME = pipex.c \
			redirect.c \
			execute_command.c \
			error.c
endif

INCS_DIR = $(PART)incs/
INCS_FLAGS = -I $(INCS_DIR) -I $(LIBFT_DIR)incs/

SRCS_DIR = $(PART)srcs/
OBJS_DIR = $(PART)objs/

OBJS_NAME = $(SRCS_NAME:.c=.o)

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_NAME))
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))

.PHONY: all clean fclean re bonus bonus_clean bonus_fclean bonus_re
all : $(NAME)
clean :
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJS_DIR)
fclean : clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
re : fclean
	$(MAKE) all
bonus : $(NAME)
bonus_clean :
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJS_DIR)
bonus_fclean : bonus_clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)
bonus_re : bonus_fclean
	$(MAKE) all
	
$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT_FLAGS) $(OBJS) -o $@

$(LIBFT) :
	$(MAKE) all -C $(LIBFT_DIR)
	
$(OBJS_DIR)%.o : $(SRCS_DIR)%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCS_FLAGS) -c $< -o $@

$(OBJS_DIR) :
	mkdir $(OBJS_DIR)