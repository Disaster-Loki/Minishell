# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
<<<<<<< HEAD
#    By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 11:52:18 by sde-carv          #+#    #+#              #
#    Updated: 2024/11/06 14:03:08 by ptchipoc         ###   ########.fr        #
=======
#    By: kali <kali@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 11:52:18 by sde-carv          #+#    #+#              #
#    Updated: 2024/11/07 14:50:53 by kali             ###   ########.fr        #
>>>>>>> 877010519f4eef948940c9e54b7256d20ef20fb1
#                                                                              #
# **************************************************************************** #

NAME		= minishell
 
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
L_DIR		= ./libft	
LIBFT		= -L$(L_DIR) -lft

RESET		= \033[0m
RED			= \033[31m
BLUE		= \033[34m
YELLOW		= \033[33m
ORANGE		= \033[38;5;208m
GREEN		= \033[32m

S_FILES		= ./src/main.c     			\
			  ./src/command.c 			\
			  ./src/read_line.c 		\
			  ./src/signals.c 			\
			  ./src/utils.c 			\
			  ./src/var_env.c 			\
			  ./src/cmd_export.c		\
			  ./src/cmd_export2.c		\
<<<<<<< HEAD
			  ./src/letf_ope.c
=======
			  ./src/left_ope.c		\
>>>>>>> 877010519f4eef948940c9e54b7256d20ef20fb1

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
