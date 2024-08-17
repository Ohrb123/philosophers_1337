# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 12:05:04 by oelharbi          #+#    #+#              #
#    Updated: 2024/08/17 21:31:21 by oelharbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

NAME = philo

HEADER = philo.h

OBJ = parsing.o philo.o utils.o routine.o init_philos.o

OBJ_DIR = ../obj/

OBJ_PFX = $(addprefix $(OBJ_DIR), $(notdir $(OBJ)))

all: $(NAME)
	@echo "\033[1;32mCompilation Completed Successfully! ✅\033[0;m"

$(NAME) : $(OBJ_PFX) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJ_PFX) -o $(NAME)

$(OBJ_DIR)%.o : %.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@echo "\033[0;34mCompiling $< .\033[0;m"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[0;31mRemoving object files.\033[0;m"

	@echo "\033[0;31mRemoving object files.\033[0;m"

	@rm -rf $(OBJ_DIR)
	@echo "\033[1;32mCleaning DONE ✅\033[0;m"

fclean: clean
	@echo "\033[0;31mRemoving program.\033[0;m"
	@echo "\033[1;32mDONE ✅\033[0;m"
	@rm -f $(NAME)

re: fclean all 

.PHONY: clean
