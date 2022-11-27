# Mandatory part
NAME			:= pipex
INCLUDES		:= -I includes
SOURCE			:= ./source/main.c
OBJS			:= $(SOURCE:./source/%.c=./objects/%.o)
HEADERS			:= ./includes/pipex.h ./includes/libft.h

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
				$(RM) $(OBJS)
				$(RM) objects
				make -C libft/ clean

fclean: 		clean
				$(RM) $(NAME) $(LIBFT)
				make -C libft/ fclean

re:				fclean all

test:			$(NAME)
				@echo "$(BLUE)---Starting tests---$(OFF)"
				@./$(NAME)
				@echo "$(BLUE)---Ending tests---$(OFF)"

.PHONY: 		all clean fclean re
