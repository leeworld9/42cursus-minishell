# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/20 12:03:42 by dohelee           #+#    #+#              #
#    Updated: 2021/07/31 16:11:59 by dohelee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 
CFLAGS = -Wall -Wextra -Werror

LIB_FT_NAME = ft
LIB_FT_DIR = ./libft

NAME = minishell
SRCS_DIR = .
SRCS_NAME = main.c env.c signal.c parser.c cmd.c cmd_path.c \
			redirection.c redirection_utils.c utils.c builtin.c cd.c echo.c parser_util.c \
			parser_sub.c cmd_util.c

SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME)) 
OBJS = $(SRCS:.c=.o)

$(SRCS_DIR)/%.o : $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -I$(SRCS_DIR) -c $^ -o $@

$(NAME) : $(OBJS)
	$(MAKE) all -C $(LIB_FT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIB_FT_DIR) -l$(LIB_FT_NAME) -lreadline -o $(NAME)

all	: $(NAME)

clean :
	$(MAKE) clean -C $(LIB_FT_DIR)
	rm -f $(OBJS)
	
fclean : clean
	$(MAKE) fclean -C $(LIB_FT_DIR)
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
