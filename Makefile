CC				= c++ 
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I./includes -std=c++98 
NAME 			= ircserv
SRCS			= srcs/main.cpp srcs/Server.cpp srcs/Client.cpp srcs/utils.cpp \
					srcs/commands/pass.cpp srcs/commands/nick.cpp srcs/commands/user.cpp \
					srcs/commands/join.cpp srcs/Channel.cpp srcs/rpl.cpp \

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