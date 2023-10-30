vpath %.c src/mandatory

vpath %.c src/bonus

NAME := philo
CFLAGS := -Wextra -Wall -Werror
CFLAGS += -g3 -O3
JOBS := -j50

YELLOW := $(shell tput setaf 3)
GREEN := $(shell tput setaf 2)
RESET := $(shell tput sgr0)

CC := cc
RM := rm -rf

OBJ_DIR := build
INCLUDE_DIR := include
INCLUDES := -I$(INCLUDE_DIR)

SRCS := philo.c
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

SRCS_BONUS := philo_bonus.c
OBJS_BONUS := $(addprefix $(OBJ_DIR)/, $(SRCS_BONUS:.c=.o))

all: $(NAME)

bonus: $(NAME)_bonus

print_start:
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): print_start $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(INCLUDES) $(CFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled!$(RESET)"

$(NAME)_bonus: print_start $(OBJS_BONUS)
	@$(CC) $(OBJS_BONUS) $(LIBS) $(INCLUDES) $(CFLAGS) -o $(NAME)_bonus
	@echo "$(GREEN)$(NAME)_bonus compiled!$(RESET)"

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes --trace-children-skip='*/bin/*,*/sbin/*' -q ./$(NAME)

bval: bonus
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes --trace-children-skip='*/bin/*,*/sbin/*' -q ./$(NAME)_bonus

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME) $(NAME)_bonus

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus val bval
