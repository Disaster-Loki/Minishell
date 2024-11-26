# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 11:52:18 by sde-carv          #+#    #+#              #
#    Updated: 2024/11/20 14:11:57 by ptchipoc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
 
CC			= cc
CFLAGS		= -g -Wall -Wextra -Werror
L_DIR		= ./libft	
LIBFT		= -L$(L_DIR) -lft

RESET		= \033[0m
RED			= \033[31m
BLUE		= \033[34m
YELLOW		= \033[33m
ORANGE		= \033[38;5;208m
GREEN		= \033[32m

S_FILES		= ./src/controller/main.c     			\
			  ./src/builtins/cd.c     				\
			  ./src/controller/signals.c   			\
			  ./src/builtins/echo.c   				\
			  ./src/controller/read_line.c  		\
			  ./src/processing/tokenize.c   		\
			  ./src/controller/utils.c   			\
			  ./src/expansion/expansion.c   		\
			  ./src/controller/exec_cmd.c   		\
			  ./src/pipeline/pipetting.c   			\
			  ./src/expansion/expand_utils.c 		\
			  ./src/builtins/export.c 				\
			  ./src/builtins/export_add.c 			\
			  ./src/builtins/export_utils.c			\
			  ./src/builtins/unset.c 				\
			  ./src/builtins/exit.c 				\
			  ./src/builtins/env.c 					\
			  ./src/builtins/pwd.c 					\

S_OBJ		= $(S_FILES:.c=.o)

all:	$(NAME)

$(NAME): $(S_OBJ)
		 $(MAKE) -C $(L_DIR)
		 $(CC) $(CFLAGS) -o $(NAME) $(S_OBJ) $(LIBFT) -lreadline
		 clear
		 @echo "$(GREEN) MANDATORY - COMPILATION COMPLETE$(RESET)"	

clean:
		@$(MAKE) clean -C $(L_DIR)
		rm -f $(S_OBJ)
		clear
		@echo "$(ORANGE) CLEANING THE OBJECTS$(RESET)"

fclean: clean
		@$(MAKE) fclean -C $(L_DIR)
		rm -f $(NAME)
		clear
		@echo "$(RED) CLEARING ALL FILES$(RESET)"

re: fclean all
