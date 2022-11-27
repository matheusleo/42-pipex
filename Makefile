# Mandatory part
NAME			:= pipex
INCLUDES		:= -I includes
SOURCE			:= ./source/main.c ./source/validate.c \
					./source/parser.c ./source/errors.c \
					./source/pipex.c ./source/utils.c
OBJS			:= $(SOURCE:./source/%.c=./objects/%.o)
HEADERS			:= ./includes/pipex.h ./includes/libft.h

# Bonus part
BONUS_NAME			:= $(NAME)_bonus
BONUS_SOURCE	:= ./source/main_bonus.c ./source/validate_bonus.c \
					./source/parser_bonus.c ./source/errors_bonus.c \
					./source/pipex_bonus.c ./source/utils_bonus.c
BONUS_OBJS		:= $(BONUS_SOURCE:./source/%.c=./objects/%.o)

# General purpose
LIBFT			:= libft.a
CC				:= gcc
C_FLAGS			:= -Wall -Werror -Wextra
VALGRIND_FLAGS	:= --leak-check=full
AR				:= ar
AR_FLAGS		:= -rcs
RM				:= rm -rf

# Colors
OFF				:= \033[0m
RED				:= \033[0;31m
GREEN			:= \033[0;32m
BLUE			:= \033[0;34m

# Rules

all:			$(NAME)

$(NAME):		./libft/$(LIBFT) $(OBJS) $(HEADERS)
				cp ./libft/$(LIBFT) .
				$(CC) $(C_FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT)

./libft/$(LIBFT):
				make -C libft/
				make -C libft/ bonus

./objects/%.o:	./source/%.c
				mkdir -p objects
				$(CC) $(C_FLAGS) -c $(INCLUDES) -o $@ $<

clean:
				$(RM) $(OBJS) $(BONUS_OBJS)
				$(RM) objects
				make -C libft/ clean

fclean: 		clean
				$(RM) $(NAME) $(BONUS_NAME) $(LIBFT)
				make -C libft/ fclean

re:				fclean all

bonus:			$(BONUS_NAME)

$(BONUS_NAME):	./libft/$(LIBFT) $(BONUS_OBJS) $(HEADERS)
				cp ./libft/$(LIBFT) .
				$(CC) $(C_FLAGS) $(INCLUDES) -o $(BONUS_NAME) $(BONUS_OBJS) $(LIBFT)
				cp $(BONUS_NAME) $(NAME)

test:			$(NAME)
				@echo "$(BLUE)---Starting tests---$(OFF)"
				@./$(NAME)
				@echo "$(BLUE)---Ending tests---$(OFF)"

demo:			$(NAME)
				@echo "$(BLUE)---Starting demo---$(OFF)"
				@./$(NAME) in.txt "ping -c 5 google.com" "grep rtt" out.txt
				@echo "$(BLUE)---Ending demo---$(OFF)"

.PHONY: 		all clean fclean re
