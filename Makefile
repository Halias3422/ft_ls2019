# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/02 14:34:41 by vde-sain     #+#   ##    ##    #+#        #
#    Updated: 2019/02/11 13:51:50 by vde-sain    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = ft_ls

SRC = ft_ls_srcs/main.c \
	  ft_ls_srcs/check_params.c

OBJ = $(SRC:.c=.o)

OBJ_DIR = ft_ls_srcs/

CC = gcc

FLAGS = -Wall -Werror -Wextra

LIBFT = ./libft/

HEADER = includes/ft_ls.h

LIBFT.A = ./libft/libft.a

all: libs $(NAME)

$(NAME): $(SRC) $(LIBFT.A) $(HEADER)
		@$(CC) -o $(NAME) $(FLAGS) $(SRC) -I./includes $(LIBFT.A)
		@echo "\033[1;32mFT_LS									OK\033[0m"
libs:
		@(cd $(LIBFT) && $(MAKE))

#$(OBJ_DIR)%.o: %.c
#		@$(CC) $(FLAGS) $(SRC) -I./includes

clean:
		@rm -f $(OBJ)
		@rm -f *.gch
		@(cd $(LIBFT) && $(MAKE) $@)
		@echo "\033[1;31mCLEAN FT_LS								OK\033[0m"

fclean: clean
		@rm -f $(NAME)
		@(cd $(LIBFT) && $(MAKE) $@)
		@echo "\033[1;31mFCLEAN FT_LS								OK\033[0m"

re: fclean all

.PHONY : all clean fclean re