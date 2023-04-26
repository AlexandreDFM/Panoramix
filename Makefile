##
## EPITECH PROJECT, 2023
## B-CCP-400-NCE-4-1-panoramix-alexandre-kevin.de-freitas-martins
## File description:
## Makefile
##

NAME		=	panoramix

CC			=	gcc

RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror -I./include -g3 -lpthread

SRC			= 	main.c														   \

OBJ			=	$(SRC:.c=.o)

all:			$(OBJ)
				$(CC) $(SRC) -o $(NAME) $(CFLAGS)

clean:
				$(RM) $(OBJ)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all
