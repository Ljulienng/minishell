
NAME = minishell
SRCS_PATH = ./srcs/
CMDS_PATH = ./srcs/cmds/
CORE_PATH = ./srcs/core/
OPTION_PATH = ./srcs/options/
TOOLS_PATH = ./srcs/tools/
CC = gcc
LIBFT_HEADERS = ./libft/includes/
LIB = ./libft/libft.a
HEADERS = ./includes/
CFLAGS = -Werror -Wall -Wextra -g -I $(HEADERS) -I $(LIBFT_HEADERS)

CORE_FILES =	main.c \
				detect_cmd.c \
				store_arg.c \
				split_quote.c \
				split_arg.c \
				core_env.c \
				exec_bin.c \
				signal.c
CMDS_FILES =	ft_pwd.c \
				ft_exit.c \
				ft_echo.c \
				ft_cd.c \
				ft_env.c \
				ft_export.c \
				ft_unset.c
OPTION_FILES = 	semicolons.c \
				redirection.c \
				fd.c \
				pipe.c
TOOLS_FILES =	ft_tools.c \
				ft_tools2.c \
				ft_tools3.c

CMDS = $(addprefix $(CMDS_PATH), $(CMDS_FILES))
CORE = $(addprefix $(CORE_PATH), $(CORE_FILES))
OPTION = $(addprefix $(OPTION_PATH), $(OPTION_FILES))
TOOLS = $(addprefix $(TOOLS_PATH), $(TOOLS_FILES))

OBJS = $(CMDS:.c=.o) $(CORE:.c=.o) $(OPTION:.c=.o) $(TOOLS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB)

$(LIB):
		make -j4 -C ./libft

clean:
	make fclean -j4 -C ./libft
	rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re