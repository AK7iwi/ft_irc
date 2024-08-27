NAME			:= ircserv

SRC_DIR			:= srcs
OBJ_DIR			:= obj

SRCS			:= main.cpp core/Server/Server.cpp core/Server/utils_server.cpp core/Client.cpp core/Channel.cpp \
					cmds/pass.cpp cmds/nick.cpp cmds/user.cpp \
					cmds/join.cpp cmds/ping.cpp cmds/pong.cpp cmds/privmsg.cpp \
					cmds/chan_cmds/part.cpp cmds/chan_cmds/topic.cpp cmds/chan_cmds/invite.cpp \
					cmds/chan_cmds/kick.cpp RPL/rpl.cpp utils/utils.cpp \
					cmds/mode/mode.cpp cmds/mode/mode_fct.cpp
SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CC				:= c++
CFLAGS			:= -Wall -Wextra -Werror
CPPFLAGS    	:= -I includes
FSANITIZE_FLAG	:= -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -fstack-protector-strong -fno-optimize-sibling-calls 

RM				:= rm -rf
DIR_DUP     	= mkdir -p $(@D)

# Color
DEF_COLOR	= \033[0;39m
RED 		= \033[0;91m 

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.cpp
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

clean:
	$(RM) $(OBJS)
	$(RM) $(OBJ_DIR)
	@echo "$(RED)Ircserv objects cleaned!$(DEF_COLOR)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(RED)Ircserv cleaned!$(DEF_COLOR)"

re:	fclean all
	@echo "$(RED)Cleaned and rebuilt!$(DEF_COLOR)"

.PHONY: all clean fclean re

# $(FSANITIZE_FLAG)