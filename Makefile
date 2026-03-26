NAME = libft.a
TEST_NAME = runner

.DEFAULT_GOAL := all

CC         = cc
CFLAGS     = -Wall -Wextra -Werror -fPIE
TEST_CFLAGS = $(CFLAGS)
INCLUDES   = -I./src -I./include

AR = ar -rcs

RM = rm -rf

RELEASE_TAG  ?=
RELEASE_NAME = libft_turnin_$(RELEASE_TAG).tar.gz
RELEASE_BASE = $(basename $(basename $(RELEASE_NAME)))


FILES = \
	ft_isalpha \
	ft_isdigit \
	ft_isalnum \
	ft_isascii \
	ft_isprint \
	ft_strlen \
	ft_strlcat \
	ft_strlcpy \
	ft_strncmp \
	ft_atoi \
	ft_memcmp \
	ft_memcpy \
	ft_memset \
	ft_memchr \
	ft_memmove \
	ft_strchr \
	ft_bzero \
	ft_strnstr \
	ft_toupper \
	ft_tolower \
	ft_strrchr \
	ft_calloc \
	ft_strdup \
	ft_substr \
	ft_strjoin \
	ft_strtrim \
	ft_split \
	ft_itoa \
	ft_strmapi \
	ft_striteri \
	ft_putchar_fd \
	ft_putstr_fd \
	ft_putendl_fd \
	ft_putnbr_fd \
	ft_lstnew \
	ft_lstadd_front \
	ft_lstsize \
	ft_lstlast \
	ft_lstadd_back \
	ft_lstdelone \
	ft_lstclear \
	ft_lstiter \
	ft_lstmap


ROOT_DIR  := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# code
SRC_DIR     := $(ROOT_DIR)/src
INCLUDE_DIR := $(ROOT_DIR)/include
TEST_SRC_DIR := $(ROOT_DIR)/test

# build output
BUILD_DIR   := $(ROOT_DIR)/build
OBJ_DIR     := $(BUILD_DIR)/obj
SRC_OBJ_DIR := $(OBJ_DIR)/src
TEST_OBJ_DIR := $(OBJ_DIR)/test

# build results
BIN_DIR      := $(BUILD_DIR)/bin
SRC_BIN_DIR  := $(BIN_DIR)/src
TEST_BIN_DIR := $(BIN_DIR)/test
LIB_DIR      := $(BUILD_DIR)/lib

# dist
DIST_DIR := $(BUILD_DIR)/dist

HEADER_FILES = libft

TEST_FILES = main

SRCS = $(FILES:%=$(SRC_DIR)/%.c)
HDRS = $(HEADER_FILES:%=$(INCLUDE_DIR)/%.h)
OBJS = $(FILES:%=$(SRC_OBJ_DIR)/%.o)
LIB  = $(LIB_DIR)/$(NAME)
TEST_SRCS = $(TEST_FILES:%=$(TEST_SRC_DIR)/%.c)
TEST_OBJS = $(TEST_FILES:%=$(TEST_OBJ_DIR)/%.o)

DIST_FILES = Makefile README.md $(SRCS) $(HDRS)

# build
all: $(LIB)
ifeq ($(TURNIN_RUN),true)
	cp $(LIB) $(ROOT_DIR)/$(NAME)
endif

bonus: all

# archive objects into static library
$(LIB): $(OBJS) | $(LIB_DIR)
	$(AR) $@ $(OBJS)

# compile source files to objects
$(SRC_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(SRC_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# move flat source files into src/ if they exist in root
$(SRC_DIR)/%.c: %.c | $(SRC_DIR)
	mv $< $@

# move flat headers into include/ if they exist in root
$(INCLUDE_DIR)/%.h: %.h | $(INCLUDE_DIR)
	mv $< $@

# create directories
$(SRC_OBJ_DIR): | $(BUILD_DIR)
	mkdir -p $(SRC_OBJ_DIR)

$(TEST_OBJ_DIR): | $(BUILD_DIR)
	mkdir -p $(TEST_OBJ_DIR)

$(SRC_BIN_DIR): | $(BUILD_DIR)
	mkdir -p $(SRC_BIN_DIR)

$(TEST_BIN_DIR): | $(BUILD_DIR)
	mkdir -p $(TEST_BIN_DIR)

$(LIB_DIR): | $(BUILD_DIR)
	mkdir -p $(LIB_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(SRC_DIR):
	mkdir -p $(SRC_DIR)

$(INCLUDE_DIR):
	mkdir -p $(INCLUDE_DIR)

$(DIST_DIR): | $(BUILD_DIR)
	mkdir -p $(DIST_DIR)

# initialize project structure from flat layout
init: $(SRCS) $(HDRS)

# create flat distribution tarball for turnin
dist: | $(DIST_DIR)
	$(RM) $(DIST_DIR)/$(RELEASE_BASE)
	mkdir -p $(DIST_DIR)/$(RELEASE_BASE)
	cp $(DIST_FILES) $(DIST_DIR)/$(RELEASE_BASE)/
	sed -i '1i TURNIN_RUN = true' $(DIST_DIR)/$(RELEASE_BASE)/Makefile
	tar -czf $(DIST_DIR)/$(RELEASE_NAME) -C $(DIST_DIR) $(RELEASE_BASE)
	$(RM) $(DIST_DIR)/$(RELEASE_BASE)

# build and run tests
test: $(TEST_NAME)

# link test runner
$(TEST_NAME): $(LIB) $(TEST_OBJS) | $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIB) -o $(TEST_BIN_DIR)/$(TEST_NAME)

# compile test files to objects
$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.c | $(TEST_OBJ_DIR)
	$(CC) $(TEST_CFLAGS) $(INCLUDES) -c $< -o $@

# remove object files
clean:
	$(RM) $(OBJ_DIR)

# remove all build artifacts
fclean: clean
	$(RM) $(LIB) $(TEST_BIN_DIR)/$(TEST_NAME)
	$(RM) $(ROOT_DIR)/$(NAME)

# full rebuild
re: fclean all

.PHONY: all bonus init dist test clean fclean re
