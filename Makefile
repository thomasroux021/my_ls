##
## EPITECH PROJECT, 2018
## Makeile
## File description:
## main Makefile
##

CC	=	gcc

RM	=	rm -f

NAME	=	my_ls

CFLAGS	=	-I./include -I$(LIB_PATH)

SRCS	=	./src/main.c \
		src/disp_stdarg.c \
		src/function.c \
		src/my_concat_list.c \
		src/my_delete_nodes.c \
		src/my_function.c \
		src/my_list_size.c \
		src/my_params_to_list.c \
		src/my_pointer.c \
		src/my_printf.c \
		src/my_print_list.c \
		src/my_rev_list.c \
		src/sum_stdarg.c \
		src/print.c \
		src/sticky_bit.c \
		src/file.c \
		src/parser.c \
		src/my_ls.c

LIB_PATH=	src/lib/my/

OBJS	=	$(SRCS:.c=.o)

CFLAGS  +=      -W -Wall -Wextra

all	:	make_lib $(NAME)

make_lib:
		make -C $(LIB_PATH)

$(NAME)	:	$(OBJS)
	 $(CC) $(OBJS) -lm -o $(NAME) -I./include -L$(LIB_PATH) -lmy $(CFLAGS)

valgrind:	make_lib $(OBJS)
	 $(CC) -g $(SRCS) -lm -o $(NAME) -I./include -L$(LIB_PATH) -lmy $(CFLAGS)

clean	:
	$(RM) $(OBJS)
	make fclean -C $(LIB_PATH)

fclean	: clean
	$(RM) $(NAME)

re	: fclean all

.PHONY	: all clean fclean re
