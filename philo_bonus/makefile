# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oelharbi <oelharbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 12:05:04 by oelharbi          #+#    #+#              #
#    Updated: 2024/07/20 15:17:32 by oelharbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

NAME = philo_bonus

HEADER = philo_bonus.h

OBJ = parsing_bonus.o philo_bonus.o utils_bonus.o routine_bonus.o checker_bonus.o init_bonus.o

all: $(NAME)
	@echo "\033[1;32mCompilation Completed Successfully! ✅\033[0;m"

$(NAME) : $(OBJ) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o : %.c $(HEADER)
	@echo "\033[0;34mCompiling $< .\033[0;m"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "\033[0;31mRemoving object files.\033[0;m"

	@echo "\033[0;31mRemoving object files.\033[0;m"

	@rm -f $(OBJ)
	@echo "\033[1;32mCleaning DONE ✅\033[0;m"

fclean: clean
	@echo "\033[0;31mRemoving program.\033[0;m"
	@echo "\033[1;32mDONE ✅\033[0;m"
	@rm -f $(NAME)

re: fclean all 

.PHONY: clean
