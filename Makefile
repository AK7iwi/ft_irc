CC				= c++ 
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I./includes -std=c++98 
NAME 			= ircserv
SRCS			= srcs/main.cpp srcs/Server.cpp srcs/Client.cpp srcs/utils.cpp \
					srcs/commands/pass.cpp \

OBJS 			= $(SRCS:.cpp=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

%.o: %.cpp
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)
				 
fclean:			clean
				$(RM) $(NAME)
	
re:				fclean all

.PHONY:			all clean fclean re