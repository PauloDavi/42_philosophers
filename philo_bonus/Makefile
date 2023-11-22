vpath %.c src src/lib

NAME := philo_bonus
CFLAGS := -Wextra -Wall -Werror
CFLAGS += -g3 -O3
JOBS := -j50

YELLOW := $(shell tput setaf 3)
GREEN := $(shell tput setaf 2)
RESET := $(shell tput sgr0)

CC := cc
RM := rm -rf

OBJ_DIR := build
INCLUDE_DIR_BONUS := include
INCLUDES := -I$(INCLUDE_DIR_BONUS)

SRCS_BONUS := utils_bonus.c exit_bonus.c ft_atoi_bonus.c ft_isspace_bonus.c
SRCS_BONUS += ft_memset_bonus.c ft_isdigit_bonus.c main_bonus.c
SRCS_BONUS += philosophers_bonus.c init_bonus.c
OBJS_BONUS := $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))

all: $(NAME)

print_start:
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): print_start $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBS) $(INCLUDES) $(CFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME)_bonus compiled!$(RESET)"

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all print_start clean fclean re
