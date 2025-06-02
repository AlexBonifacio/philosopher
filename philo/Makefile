NAME := philo

CC := cc
CFLAGS := -Wall -Wextra -Werror -MMD -MP -O3 # -g3 -fsanitize=thread
INC := -Iinclude

SRC := main.c ft_atol.c ft_error.c ft_strlen.c wait_for_start.c ft_times.c \
		check_args.c ft_isspace.c mutex_safe.c thread_safe.c ft_gettimeofday.c \
		lock_unlock.c init_philos.c routine.c monitor.c one_philo.c

SRC_DIR := src
OBJ_DIR := obj

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP := $(OBJ:.o=.d)

VPATH := $(SRC_DIR) $(SRC_DIR)/utils

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $@ $^

$(OBJ_DIR)/%.o: %.c Makefile | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)