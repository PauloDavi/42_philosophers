vpath %.c src src/lib

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

SRCS := philosophers.c ft_atoi.c init.c utils.c exit.c main.c ft_isdigit.c
SRCS += ft_isspace.c ft_memset.c
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

print_start:
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): print_start $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(INCLUDES) $(CFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled!$(RESET)"

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all print_start clean fclean re
