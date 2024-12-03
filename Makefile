NAME			:= ircserv

SRC_DIR			:= srcs
OBJ_DIR			:= obj

SRCS			:= main.cpp core/Server/Server.cpp core/Server/handle_clients.cpp core/Server/handle_cmds.cpp core/Server/clear_server.cpp\
					core/Client.cpp core/Channel.cpp \
					commands/cmds/pass.cpp commands/cmds/nick.cpp commands/cmds/user.cpp \
					commands/cmds/join.cpp commands/cmds/ping.cpp commands/cmds/pong.cpp commands/cmds/privmsg.cpp \
					commands/cmds/cmds_chan/part.cpp commands/cmds/cmds_chan/topic.cpp commands/cmds/cmds_chan/invite.cpp \
					commands/cmds/cmds_chan/kick.cpp commands/cmds/mode/mode.cpp commands/cmds/mode/mode_fct.cpp \
					commands/cmds_utils/list_check_and_manip.cpp commands/cmds_utils/str_check_and_manip.cpp RPL/RPL_list.cpp RPL/RPL_handle.cpp
SRCS        := $(SRCS:%=$(SRC_DIR)/%)
OBJS        := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CC				:= c++
CFLAGS			:= -Wall -Wextra -Werror -std=c++98
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
	@clear

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

#  $(FSANITIZE_FLAG)