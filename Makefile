NAME = libft.a
TARGET_EXTENSION = .out

.DEFAULT_GOAL := all

CC         = cc
CFLAGS     = -Wall -Wextra -Werror -fPIE
INCLUDES   = -I./src -I./src/ft_printf -I./include

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

PRINTF_FILES = \
	ft_printf \
	ft_pf_putchar_fd \
	ft_pf_putnbr_base_fd \
	ft_pf_putptr_fd \
	ft_pf_putstr_fd

# code
SRC_DIR        := src
PRINTF_SRC_DIR := $(SRC_DIR)/ft_printf
INCLUDE_DIR    := include
TEST_SRC_DIR   := test
UNITY_SRC_DIR  := external/unity/src
UNITY_AUTO_DIR := external/unity/auto

# build output
BUILD_DIR      := build
OBJ_DIR        := $(BUILD_DIR)/obj
SRC_OBJ_DIR    := $(OBJ_DIR)/src
PRINTF_OBJ_DIR := $(SRC_OBJ_DIR)/ft_printf
TEST_OBJ_DIR   := $(OBJ_DIR)/test
UNITY_OBJ_DIR  := $(OBJ_DIR)/unity

# build results
BIN_DIR      := $(BUILD_DIR)/bin
SRC_BIN_DIR  := $(BIN_DIR)/src
TEST_BIN_DIR := $(BIN_DIR)/test
LIB_DIR      := $(BUILD_DIR)/lib

# test runner generation
TEST_RUNNER_DIR := $(BUILD_DIR)/test/runner_src

# dist
DIST_DIR := $(BUILD_DIR)/dist

HEADER_FILES = libft

SRCS = $(FILES:%=$(SRC_DIR)/%.c)
PRINTF_SRCS = $(PRINTF_FILES:%=$(PRINTF_SRC_DIR)/%.c)
HDRS = $(HEADER_FILES:%=$(INCLUDE_DIR)/%.h)
OBJS = $(FILES:%=$(SRC_OBJ_DIR)/%.o)
PRINTF_OBJS = $(PRINTF_FILES:%=$(PRINTF_OBJ_DIR)/%.o)
ALL_OBJS = $(OBJS) $(PRINTF_OBJS)
LIB  = $(LIB_DIR)/$(NAME)

TEST_CFLAGS   = -g -Wall -Wextra
TEST_INCLUDES = $(INCLUDES) -I$(UNITY_SRC_DIR) -I$(TEST_SRC_DIR)

TEST_SRC_FILES = $(wildcard $(TEST_SRC_DIR)/test_*.c)
TEST_NAMES     = $(patsubst $(TEST_SRC_DIR)/test_%.c,%,$(TEST_SRC_FILES))
TEST_BINS      = $(addprefix $(TEST_BIN_DIR)/test_,$(addsuffix _Runner$(TARGET_EXTENSION),$(TEST_NAMES)))

DIST_FILES = Makefile README.md $(SRCS) $(HDRS)

# build
all: init $(LIB)
ifeq ($(TURNIN_RUN),true)
	cp $(LIB) $(NAME)
	cp $(HDRS) .
endif

bonus: all

$(NAME): all

# archive objects into static library
$(LIB): $(ALL_OBJS) | $(LIB_DIR)
	$(AR) $@ $(ALL_OBJS)

# compile source files to objects
$(SRC_OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(SRC_OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# compile ft_printf source files to objects
$(PRINTF_OBJ_DIR)/%.o: $(PRINTF_SRC_DIR)/%.c | $(PRINTF_OBJ_DIR)
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

$(PRINTF_OBJ_DIR): | $(SRC_OBJ_DIR)
	mkdir -p $(PRINTF_OBJ_DIR)

$(TEST_OBJ_DIR) $(UNITY_OBJ_DIR) $(TEST_RUNNER_DIR) $(TEST_BIN_DIR): | $(BUILD_DIR)
	mkdir -p $@

$(SRC_BIN_DIR): | $(BUILD_DIR)
	mkdir -p $(SRC_BIN_DIR)

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

# create a distribution tarball with the submission files
dist: stage
	tar -czf $(DIST_DIR)/$(RELEASE_NAME) -C $(DIST_DIR) $(RELEASE_BASE)

# create flat distribution environment for turnin
stage: | $(DIST_DIR)
	$(RM) $(DIST_DIR)/$(RELEASE_BASE)
	mkdir -p $(DIST_DIR)/$(RELEASE_BASE)
	cp $(DIST_FILES) $(DIST_DIR)/$(RELEASE_BASE)/
	sed -i '1i TURNIN_RUN = true' $(DIST_DIR)/$(RELEASE_BASE)/Makefile

# build all tests
test: $(TEST_BINS)

# build a single test: make test-ft_strlen, make test-ft_atoi, etc.
test-%: $(TEST_BIN_DIR)/test_%_Runner$(TARGET_EXTENSION)
	@true

.PRECIOUS: $(TEST_RUNNER_DIR)/test_%_Runner.c $(TEST_OBJ_DIR)/test_%.o $(TEST_OBJ_DIR)/test_%_Runner.o

# link test binary
$(TEST_BIN_DIR)/test_%_Runner$(TARGET_EXTENSION): $(TEST_OBJ_DIR)/test_%.o $(TEST_OBJ_DIR)/test_%_Runner.o $(UNITY_OBJ_DIR)/unity.o $(TEST_OBJ_DIR)/helpers.o $(LIB) | $(TEST_BIN_DIR)
	$(CC) $(TEST_CFLAGS) $^ -o $@

# compile test source files
$(TEST_OBJ_DIR)/test_%.o: $(TEST_SRC_DIR)/test_%.c | $(TEST_OBJ_DIR)
	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDES) -c $< -o $@

# compile test helpers
$(TEST_OBJ_DIR)/helpers.o: $(TEST_SRC_DIR)/helpers.c $(TEST_SRC_DIR)/helpers.h | $(TEST_OBJ_DIR)
	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDES) -c $< -o $@

# generate test runner source via Unity
$(TEST_RUNNER_DIR)/test_%_Runner.c: $(TEST_SRC_DIR)/test_%.c | $(TEST_RUNNER_DIR)
	ruby $(UNITY_AUTO_DIR)/generate_test_runner.rb $< $@

# compile generated test runner
$(TEST_OBJ_DIR)/test_%_Runner.o: $(TEST_RUNNER_DIR)/test_%_Runner.c | $(TEST_OBJ_DIR)
	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDES) -c $< -o $@

# compile unity
$(UNITY_OBJ_DIR)/unity.o: $(UNITY_SRC_DIR)/unity.c | $(UNITY_OBJ_DIR)
	$(CC) $(CFLAGS) -I$(UNITY_SRC_DIR) -c $< -o $@

 
# remove object files
clean:
	$(RM) $(OBJ_DIR)

# remove all build artifacts
hclean: clean
	$(RM) $(LIB) $(TEST_BIN_DIR) $(TEST_RUNNER_DIR)
	$(RM) $(NAME)
	$(RM) $(DIST_DIR)/$(RELEASE_BASE)

# flatten back to root (undo init)
fclean: hclean
	-mv $(SRC_DIR)/*.c .
	-mv $(INCLUDE_DIR)/*.h . 
ifeq ($(TURNIN_RUN),true)
	-rmdir $(SRC_DIR) $(INCLUDE_DIR) 2>/dev/null; true
endif

# full rebuild
re: hclean all

.PHONY: all bonus init dist test test-% clean fclean hclean re
