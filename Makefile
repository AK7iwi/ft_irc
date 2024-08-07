CC				= c++ 
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I./includes -std=c++98 -fsanitize=address -fsanitize=undefined  -fno-omit-frame-pointer -fstack-protector-strong  -fno-optimize-sibling-calls 
NAME 			= ircserv
SRCS			= srcs/main.cpp srcs/core/Server.cpp srcs/core/Client.cpp srcs/core/Channel.cpp \
					srcs/cmds/pass.cpp srcs/cmds/nick.cpp srcs/cmds/user.cpp \
					srcs/cmds/join.cpp srcs/cmds/ping.cpp srcs/cmds/pong.cpp srcs/cmds/privmsg.cpp \
					srcs/cmds/chan_cmds/part.cpp srcs/cmds/chan_cmds/topic.cpp srcs/cmds/chan_cmds/invite.cpp \
					srcs/cmds/chan_cmds/kick.cpp srcs/RPL/rpl.cpp srcs/utils/utils.cpp \
					srcs/cmds/mode/mode.cpp srcs/cmds/mode/mode_fct.cpp\

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