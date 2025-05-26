NAME := philo

CC := gcc
CFLAGS := -Wall -Wextra -Werror -MMD -MP -g3 -fsanitize=thread
INC := -Iinclude

SRC := main.c ft_atol.c ft_exit.c ft_strlen.c \
		check_args.c ft_isspace.c threads_mutex_error.c ft_gettimeofday.c

SRC_DIR := src
OBJ_DIR := obj

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP := $(OBJ:.o=.d)

VPATH := $(SRC_DIR) $(SRC_DIR)/utils

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $@ $^

# Compile object files
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

.PHONY: all clean fclean re run

-include $(DEP)