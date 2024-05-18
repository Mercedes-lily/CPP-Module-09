NAME = RPN

CC = c++
CFLAGS = -Wall -Werror -Wextra -std=c++98 #-fsanitize=address

OBJ_DIR = obj/

SRCS =	btc.cpp \

VPATH = $(OBJ_DIR)

OBJS = $(SRCS:%.cpp=%.o)
OBJ_PRE = $(addprefix $(OBJ_DIR), $(OBJS))

DEP =	Bitcoin.hpp \

all: $(NAME)

$(OBJ_DIR)%.o: %.cpp $(DEP_PRE)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ_PRE)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re debug fclean clean all