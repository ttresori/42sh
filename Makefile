# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abeauvoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/17 15:44:28 by abeauvoi          #+#    #+#              #
#    Updated: 2019/01/07 21:39:35 by ttresori         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 42sh

#
# Dirs
#

SRCS_DIR	= src
OBJS_DIR	= obj
LIB_DIR		= libft
INC_DIRS	= $(addsuffix includes, ./ $(LIB_DIR)/)
VPATH		= $(SRCS_DIR)

#
# Sources
#

SRCS		= main.c list.c process.c getenv.c init_shell.c errno.c prompt.c \
			  stdin.c move_arrows.c manip_input.c insert_mode.c move_word.c \
			  control_action.c keymap.c hashtable.c keymap_select.c \
			  init_hashtable.c ft_joinpath.c env.c select_mode.c \
			  move_select_mode.c action_select_mode.c move_line.c get_word.c \
			  get_operator.c lexer.c get_newline.c list_lexer.c print_lexer.c \
              init_file_history.c parser_history.c history_opt.c \
			  move_histo.c
#
# Build
#

CC 		= gcc
OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
CFLAGS		= -Wall -Werror -Wextra $(addprefix -I, $(INC_DIRS)) -g3
LFLAGS		= -L$(LIB_DIR) -lft -ltermcap
LIB		= libft.a
COMP		= $(CC) $(CFLAGS) -o $@ -c $<
LINK		= $(CC) $(CFLAGS) $(LFLAGS) -o $@ $(filter-out $(LIB_DIR)/$(LIB), $^)
NUMCORES 	= $(sysctl -n hw.ncpu)
_MAKEFLAGS	= -j$(echo $(NUMCORES)+1| bc) -l$(NUMCORES) -C $(LIB_DIR)

#
# Rules
#

all: $(LIB_DIR)/$(LIB) $(NAME)

debug: CFLAGS += -g3
debug: re

$(LIB_DIR)/$(LIB):
	@make $(_MAKEFLAGS)

$(NAME): $(LIB_DIR)/$(LIB) $(OBJS)
	@$(LINK)
	@echo "completed compilation \033[1;32m√\033[0m"

$(OBJS_DIR)/%.o: %.c
	@mkdir -p $(OBJS_DIR)
	@$(COMP)

clean:
	@rm $(OBJS) 2> /dev/null || true
	@make $(_MAKEFLAGS) $@
	@rm -rf $(OBJS_DIR)
	@echo "cleaned .o files"

fclean: clean
	@rm $(NAME) 2> /dev/null || true
	@make $(_MAKEFLAGS) $@
	@echo "removed binary"

re: fclean
re: all

.PHONY: all clean fclean re
