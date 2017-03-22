# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tdumouli <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/08 16:51:40 by tdumouli          #+#    #+#              #
#    Updated: 2017/03/22 15:31:14 by tdumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SPEUDO = "tdumouli"
NAMEI =
NAME = minishell
OBJDIR = ./objet
SRCDIR = ./src
INCDIR = -I. -Isrc/libft/include

MINI =	envie.o enviede.o get_next_line.o is_dir.o utilitaire.o\
		change.o fenster.o grsa.o\
	   	built/echo.o built/cd.o built/setenv.o

LIB = libft/libft.a

OBJ =	$(addprefix $(OBJDIR)/, $(MINI)) 

LSTDIRI = built
debugg = 

############################## normaly no change ###############################

NO_COLOR="\x1b[39m"
RED="\x1b[31m"
GREEN="\x1b[32m"
YELLOW="\x1b[33m"
CC = gcc
CFLAGS = $(INCDIR) -Wall -Wextra -Werror
DEBUG = -fsanitize=address -g3
MAKE = /usr/bin/make

LSTDIR=	$(addprefix $(OBJDIR)/, $(LSTDIRI)) \

ifneq ($(NAMEI), )
all: objdir $(NAMEI)
	@echo $(GREEN)"compilation reussi"$(NO_COLOR)
else
all: objdir $(NAME)
	@echo $(GREEN)"compilation reussi cpl"$(NO_COLOR)
endif

objdir:
	@if ! [ -d $(OBJDIR) ]; then\
		mkdir $(OBJDIR) $(LSTDIR);\
	fi

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo $(GREEN)$@" compile"$(NO_COLOR)

$(NAMEI): $(OBJ)
	@ar cr $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo $(GREEN)"library compile"$(NO_COLOR)

$(NAME): $(OBJ)
	$(MAKE) -C $(SRCDIR)/libft
	$(CC) $(OBJ) $(SRCDIR)/$(LIB) -o $(NAME)
	@echo $(GREEN)$(NAMECPL)" a ete cree"$(NO_COLOR)

clean:
	@$(MAKE) clean -C $(SRCDIR)/libft
	@rm -rf $(OBJ)
	@$(MAKE) cleanv

ifeq ($(shell find . -type f | grep "\.o"), )
cleanv:
	@echo $(GREEN)"les objets sont clean"$(NO_COLOR)
else
cleanv:
	@echo $(RED)"il ya probleme"
	@echo $(YELLOW)$(shell echo | find . -type f | grep "\.o" | cat -e)
	exit
endif

cl:
	@if [ "test" = "test" ]; then\
		echo "Hello world";\
	fi

auteur:
	@echo $(SPEUDO) > auteur
	@echo $(GREEN)"le fichier auteur a bien ete cree"$(NO_COLOR)

fclean: clean
	@$(MAKE) fclean -C $(SRCDIR)/libft
	@rm -f $(NAME) $(NAMELIB)
	@echo $(GREEN)"tout est clean"$(NO_COLOR)

re: fclean all

.PHONY: all clean fclean re cleanv anc
