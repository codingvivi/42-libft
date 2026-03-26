CC = cc
CFLAGS = -g -Werror -Wall -Wextra

NAME = libft.a

SRCS = \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_strlcat.c \
	ft_atoi.c 


OBJS = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)
	
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -rf $(NAME)

re: fclean all
