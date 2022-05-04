NAME = push_swap
CC = gcc
CFLAG = -Wall -Werror -Wextra

SRC = binary_search.c \
	  circular_buffer.c \
	  indexing.c \
	  insertion_sort.c \
	  lics.c \
	  moves.c \
	  sort_three_or_less.c

OBJ = $(SRC:.c=.o)

$(NAME) : push_swap.c $(OBJ)
	$(CC) $(CFLAG) -o $@ $< $(OBJ)

%.o : %.c %.h
	$(CC) $(CFLAG) -c -o $@ $<

all : $(NAME)

clean:
	-rm -f $(OBJ)

fclean : clean
	-rm -f $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re
