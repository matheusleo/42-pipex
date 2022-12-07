# Mandatory and Bonus part
NAME			:= pipex
INCLUDES		:= -I includes
SOURCE			:= ./source/main.c ./source/validate.c \
					./source/parser.c ./source/errors.c \
					./source/pipex.c ./source/utils.c \
					./source/masks.c ./source/here_doc.c
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
				@echo "$(GREEN)All object files for $(NAME) were created!$(OFF)"
				@cp ./libft/$(LIBFT) .
				@$(CC) $(C_FLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT)
				@echo "$(GREEN)$(NAME) files were sucessfully linked!$(OFF)"

./libft/$(LIBFT):
				@make -C libft/
				@make -C libft/ bonus

./objects/%.o:	./source/%.c
				@mkdir -p objects
				@$(CC) $(C_FLAGS) -c $(INCLUDES) -o $@ $<

clean:
				@$(RM) $(OBJS)
				@$(RM) objects
				@echo "$(RED)The object files from $(NAME) were sucessfully removed!$(OFF)"
				@make -C libft/ clean

fclean: 		clean
				@$(RM) $(NAME) $(LIBFT)
				@make -C libft/ fclean
				@echo "$(RED)The $(NAME) was removed!$(OFF)"

re:				fclean all

test:			$(NAME)
				@echo "$(BLUE)---Starting tests---$(OFF)"
				@./$(NAME)
				@echo "$(BLUE)---Ending tests---$(OFF)"

demo:			$(NAME)
				@echo "$(BLUE)---Starting demo---$(OFF)"
				@./$(NAME) in.txt "ping -c 5 google.com" "grep rtt" out.txt
				@echo "$(BLUE)---Ending demo---$(OFF)"

demo_bonus:		$(NAME)
				@echo "$(BLUE)---Starting bonus demo---$(OFF)"
				@./$(NAME) in.txt "sort" "uniq -d" "wc" "wc" out.txt
				@echo "$(BLUE)---Ending bonus demo---$(OFF)"

demo_here_doc:	$(NAME)
				@echo "$(BLUE)---Starting here_doc demo---$(OFF)"
				@./$(NAME) here_doc eof "cat" "base64 -d" out.txt
				@echo "$(BLUE)---Ending here_doc demo---$(OFF)"

.PHONY: 		all clean fclean re
