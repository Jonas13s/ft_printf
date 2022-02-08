# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joivanau <joivanau@hive.fi>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/08 19:01:07 by joivanau          #+#    #+#              #
#    Updated: 2022/02/07 19:37:55 by joivanau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ft_printf.c ft_args.c ft_ischeck.c ft_conv.c print_char.c print_string.c print_signedinteger.c print_hex.c print_pointer.c print_octal.c print_unsignedint.c ftoa.c
SRC += print_float.c
OBJ = $(SRC:.c=.o)
CFLAGS = -c -Wall -Werror -Wextra -g -fsanitize=address
NAME = libftprintf.a
LIBFTPATH = libft/
all: $(NAME)

# 	@ar rv libftprintf.a $(OBJ) $(LIBFTPATH)*.o #
#	L $(LIBFTPATH) -lft
$(NAME):
	@make -C $(LIBFTPATH)
	@cc -Wall -Wextra -Werror -c $(SRC) -I $(LIBFTPATH)
	@ar rv libftprintf.a $(OBJ) $(LIBFTPATH)*.o
clean:
	@rm -rf $(OBJ)
	@make -C libft/ clean
fclean: clean
	@rm -rf $(NAME)
	@make -C libft/ fclean
re: fclean all
comp:
	@cc -g -fsanitize=address $(SRC) -I $(LIBFTPATH) -L $(LIBFTPATH) -lft