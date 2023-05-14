# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 09:39:09 by alde-fre          #+#    #+#              #
#    Updated: 2023/05/14 12:37:42 by alde-fre         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philosopher

# directories
SRCDIR	=	./src
INCDIR	=	-I ./inc
OBJDIR	=	./obj

###########################################
###				SOURCE FILES			###
###########################################
SRC		=	\
			main.c		\
			manager.c	\
			getter.c	\
			time.c		\
			messages.c	\
			simulation.c\
			actions.c	\
			parsing.c			

###########################################
###				OBJECT FILES			###
###########################################
OBJ		= $(addprefix $(OBJDIR)/,$(SRC:.c=.o))

# compiler
CC		= cc
CFLAGS	= -MMD -MP -Wall -Wextra -Werror

all: obj $(NAME)

raw: CFLAGS += -O0
raw: all

fast: CFLAGS += -Ofast
fast: all

debug: CFLAGS += -g3
debug: all

obj:
	@rm -rf .print
	@mkdir -p $(OBJDIR)

.print:
	@> $@
	@echo "\e[1;36mCompiling...\e[0m"

$(NAME): $(OBJ)
	@echo "\e[1;35mLinking...\e[0m"
	@$(CC) -lpthread -o $@ $+
	@echo "\e[1;32m➤" $@ "created succesfully !\e[0m"

$(OBJDIR)/%.o: $(SRCDIR)/%.c .print
	@echo "\e[0;36m ↳\e[0;36m" $<"\e[0m"
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

temp:
	@echo "\e[1;36mCompiling...\e[0m";

clean:
	rm -rf $(OBJDIR)
	rm -rf .print

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
