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

# Diretórios
SRC_DIR     = ./src
CONTROLLER  = $(SRC_DIR)/controller
BUILTINS    = $(SRC_DIR)/builtins
PROCESSING  = $(SRC_DIR)/processing
EXPANSION   = $(SRC_DIR)/expansion
PIPELINE    = $(SRC_DIR)/pipeline
REDIRECTS   = $(SRC_DIR)/redirects

# Arquivos por pasta
CONTROLLER_FILES = $(CONTROLLER)/main.c 			\
				   $(CONTROLLER)/signals.c 			\
				   $(CONTROLLER)/read_line.c 		\
                   $(CONTROLLER)/exec_cmd.c 		\
				   $(CONTROLLER)/frees.c 			\
				   $(CONTROLLER)/utils.c

BUILTINS_FILES   = $(BUILTINS)/cd.c 				\
				   $(BUILTINS)/env.c 				\
				   $(BUILTINS)/pwd.c 				\
				   $(BUILTINS)/echo.c 				\
				   $(BUILTINS)/exit.c 				\
                   $(BUILTINS)/unset.c 				\
                   $(BUILTINS)/export.c 			\
				   $(BUILTINS)/export_add.c 		\
				   $(BUILTINS)/export_utils.c

PROCESSING_FILES = $(PROCESSING)/tokenize.c 		\
				   $(PROCESSING)/utils.c 			\
                   $(PROCESSING)/redir.c 			\
				   $(PROCESSING)/r_utils.c 			\
				   $(PROCESSING)/invalid_rdir.c

EXPANSION_FILES  = $(EXPANSION)/expansion.c 		\
				   $(EXPANSION)/gets.c 				\
				   $(EXPANSION)/utils.c

PIPELINE_FILES   = $(PIPELINE)/Init_vars.c 			\
				   $(PIPELINE)/full_split.c 		\
				   $(PIPELINE)/pipetting.c

REDIRECTS_FILES  = $(REDIRECTS)/redirects.c 		\
				   $(REDIRECTS)/utills.c 			\
				   $(REDIRECTS)/right_utils.c

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
