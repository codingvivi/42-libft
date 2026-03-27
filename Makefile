NAME = libftprintf.a
TEST-NAME = test/runner.out

.DEFAULT_GOAL := all

CC         = cc
CFLAGS     = -Wall -Wextra -Werror -fPIE
TEST_CFLAGS = $(CFLAGS) -Wno-nonnull -Wno-format-security -Wno-format-overflow
INCLUDES   = -I./src

AR = ar -rcs

RM = rm -rf


FILES = ft_printf \
		ft_pf_putchar_fd \
		ft_pf_putstr_fd \
		ft_pf_putptr_fd \
		ft_pf_putnbr_base_fd

SRC_DIR  = src
OBJ_DIR  = obj
TEST_DIR = test

TEST_FILES = main

SRCS = $(FILES:%=$(SRC_DIR)/%.c)
OBJS = $(FILES:%=$(OBJ_DIR)/%.o)

TEST_SRCS = $(TEST_FILES:%=$(TEST_DIR)/%.c)
TEST_OBJS = $(TEST_FILES:%=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# tests
test: $(TEST-NAME)

$(TEST-NAME): $(NAME) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(NAME) -o $(TEST-NAME)

$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(TEST_CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) $(TEST-NAME)

re: fclean all

.PHONY: all test clean fclean re
