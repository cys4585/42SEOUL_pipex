# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youngcho <youngcho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 17:37:39 by youngcho          #+#    #+#              #
#    Updated: 2022/08/19 12:56:30 by youngcho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC_DIR = srcs/
OBJ_DIR = objs/
SRCS_NAME = ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_free_splited_arr.c

SRCS = $(addprefix $(SRC_DIR), $(SRCS_NAME))
OBJS = $(addprefix $(OBJ_DIR), $(SRCS_NAME:.c=.o))

BON_SRCS_NAME = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c
BON_SRCS = $(addprefix $(SRC_DIR), $(SRCS_NAME))
BON_OBJS = $(addprefix $(OBJ_DIR), $(BON_SRCS_NAME:.c=.o))

INC = incs/
echo :
	@echo $(SRCS)
	@echo $(OBJS)
	@echo $(BON_SRCS)
	@echo $(BON_OBJS)
	
AR = ar
ARFLAGS = rcsu
CC = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY : all clean fclean re bonus
all : $(NAME)
clean :
	rm -rf $(OBJ_DIR)
fclean : clean
	rm -f $(NAME)
re : fclean all
bonus : all $(OBJ_DIR) $(BON_OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(BON_OBJS)

$(NAME) : $(OBJ_DIR) $(OBJS)
	$(AR) $(ARFLAGS) $@ $(OBJS)

$(OBJ_DIR) :
	mkdir objs
	
$(OBJ_DIR)%.o : $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

export BON_OBJS