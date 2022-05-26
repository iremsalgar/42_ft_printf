NAME 		= libftprintf.a

SRCS	 	=	ft_printf.c 

OBJS 		= $(SRCS:.c=.o)

CFLAGS 		= -Wall -Werror -Wextra

$(NAME):	$(OBJS)
			ar -rc $(NAME) $(OBJS) 

.o:			.c ft_printf.h
			gcc $(CFLAGS) -o $@ -c $<

all: 		$(NAME)

clean:
			rm -rf $(OBJS)

fclean:		clean
			rm -rf $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re bonus
