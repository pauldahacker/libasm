NAME		= libasm.a
TEST_NAME	= test_libasm

BLUE 		= \033[0;34m
GREEN 		= \033[0;32m
RED 		= \033[0;31m
ORANGE		= \033[38;5;209m
YELLOW		= \033[0;93m
BROWN 		= \033[38;2;184;143;29m
RESET 		= \033[0m

SRC_DIR		= ./src/
TEST_DIR	= ./test/

SRC_LS		= ft_strlen.s \
			ft_strcpy.s \
			ft_strcmp.s \
			ft_write.s \
			ft_read.s \
			ft_strdup.s

TEST_LS		= test.c

SRC			= $(addprefix $(SRC_DIR), $(SRC_LS))
OBJ			= $(SRC:.s=.o)
TEST_SRC	= $(TEST_DIR)$(TEST_LS)
TEST_OBJ	= $(TEST_SRC:.c=.o)


CC			= gcc
CFLAGS  	= -Wall -Wextra -Werror

AS			= nasm
ASFLAGS		= -f elf64

AR			= ar rcs
RM			= rm -rf

all: $(NAME)

$(SRC_DIR)%.o: $(SRC_DIR)%.s
	@echo "$(BROWN)Compiling  $(BLUE)→  $(YELLOW)$< $(RESET)"
	@$(AS) $(ASFLAGS) $< -o $@

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "\n$(GREEN)Created $(NAME) ✓ $(RESET)\n"

$(TEST_DIR)%.o: $(TEST_DIR)%.c
	@echo "$(BROWN)Compiling  $(BLUE)→  $(YELLOW)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_NAME): $(TEST_OBJ) $(NAME)
	$(CC) $(TEST_OBJ) -L. -lasm -o $(TEST_NAME)
	@echo "\n$(GREEN)Created $(TEST_NAME) ✓$(RESET)\n"

test: $(TEST_NAME)
	@echo "$(BROWN)Running tests...$(RESET)"
	@./$(TEST_NAME)

clean:
	@$(RM) $(OBJ) $(TEST_OBJ)
	@echo "\n$(GREEN)Objects cleaned successfully $(RESET)\n"

fclean: clean
	@$(RM) $(NAME) $(TEST_NAME)
	@echo "\n$(GREEN)Executables cleaned successfully $(RESET)\n"

re: fclean all

.PHONY: all test clean fclean re
