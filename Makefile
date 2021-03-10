NAME = main

CC = clang++

CFLAGS = -Wall -Wextra -Werror -std=c++98

SRC = other_test.cpp

OBJ = $(SRC:.cpp=.o)

all: $(NAME) clean
	./main

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean