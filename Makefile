NAME	=	ircserv
CC		=	c++
CFLAGS	=	-Wall -Wextra -Werror -std=c++98

SRC		=	

OBJ		=	$(SRC:.cpp=.o)

%.o		:	%.cpp
			@ $(CC) $(CFLAGS) -c $< -o $@

all		:	$(NAME)


