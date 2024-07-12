CC				= c++ 
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I./includes -std=c++98 
NAME 			= ircserv
SRCS			= srcs/main.cpp srcs/Server.cpp srcs/Client.cpp srcs/Channel.cpp \
					srcs/cmds/pass.cpp srcs/cmds/nick.cpp srcs/cmds/user.cpp \
					srcs/cmds/join.cpp srcs/cmds/ping.cpp srcs/cmds/pong.cpp \
					srcs/cmds/chan_cmds/part.cpp \
					srcs/RPL/rpl.cpp srcs/utils/utils.cpp \

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