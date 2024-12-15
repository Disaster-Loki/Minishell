# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ptchipoc <ptchipoc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/16 11:52:18 by sde-carv          #+#    #+#              #
#    Updated: 2024/12/15 20:40:02 by ptchipoc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -g -Wall -Wextra -Werror
L_DIR       = ./libft
LIBFT       = -L$(L_DIR) -lft
RL_LIB      = -lreadline

RESET       = \033[0m
RED         = \033[31m
BLUE        = \033[34m
YELLOW      = \033[33m
ORANGE      = \033[38;5;208m
GREEN       = \033[32m

CONTROLLER_FILES = main.c 			\
				   signals.c 			\
				   read_line.c 		\
                   exec_cmd.c 		\
                   exec_utils.c 		\
                   exec_utils2.c 		\
				   ft_strtoll.c 		\
				   frees.c 			\
				   utils.c 			\
				   utils2.c

BUILTINS_FILES   = cd.c 				\
				   env.c 				\
				   pwd.c 				\
				   echo.c 				\
				   exit.c 				\
                   unset.c 				\
                   export.c 			\
				   export_add.c 		\
				   export_utils.c		\
				   export_utills2.c		\

PROCESSING_FILES = tokenize.c 		\
				   p_utils.c 			\
                   redir.c 			\
				   r_utils.c 			\
				   valid_input.c 		\
				   valid_error.c 		\
                   v_utils.c 			\
				   invalid_rdir.c

EXPANSION_FILES  = expansion.c 		\
				   gets.c 				\
				   e_utils.c

PIPELINE_FILES   = Init_vars.c 			\
				   full_split.c 		\
				   pipetting.c

REDIRECTS_FILES  = redirects.c 		\
				   utills.c 			\
				   right_utills.c			\
				   right_utills2.c			\
				   double_left.c			\
				   double_left_utills.c		\
				   left_utills.c			\
				   left_redir.c			\
				   right_redir.c			\
				   left_utills2.c			\
				   double_left_utills2.c		\
				   doc_utill1.c				\
				   doc_first_position.c			\
				   doc_utill2.c				\
				   doc_other_position.c			\

SRC_FILES = $(CONTROLLER_FILES) 					\
			$(BUILTINS_FILES) 						\
			$(PROCESSING_FILES) 					\
			$(EXPANSION_FILES) 						\
            $(PIPELINE_FILES) 						\
			$(REDIRECTS_FILES)

OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(MAKE) -C $(L_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES) $(LIBFT) $(RL_LIB)
	clear
	@echo "$(GREEN)COMPILATION COMPLETE$(RESET)"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C $(L_DIR)
	rm -f $(OBJ_FILES)
	clear
	@echo "$(ORANGE)CLEANING OBJECT FILES$(RESET)"

fclean: clean
	$(MAKE) fclean -C $(L_DIR)
	rm -f $(NAME)
	clear
	@echo "$(RED)ALL CLEANED$(RESET)"

re: fclean all
