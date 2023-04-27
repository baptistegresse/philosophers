NAME		   :=   philo

INC            :=   philosophers.h
INC_DIR        :=   includes/

HEADERS        := $(addprefix $(INC_DIR), $(INC))

SRC_DIR        :=   sources/
SRC            :=	checker_functions.c destroy_functions.c init_functions.c \
					main.c thread_functions.c time_functions.c utils_functions.c

OBJ_DIR        :=    build/
OBJ            :=    $(SRC:%.c=$(OBJ_DIR)%.o)

# Compiler options
CC            :=    cc
CC_FLAGS      :=    -Wextra -Werror -Wall

all: $(NAME)

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS)
	@mkdir -p $(@D)
	@echo "compiling: $<"
	@$(CC) $(CC_FLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJ) $(INC_DIR)/$(INC) Makefile
	@$(CC) $(CC_FLAGS) $(OBJ) -lreadline -o $@
	@echo "> philo Done! <"

# clean commands
clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "remove $(NAME)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re