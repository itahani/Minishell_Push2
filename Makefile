NAME =		minishell

LAUNCHER_DIR = launcher/

BUILTINS_DIR = builtins/

LEXER_DIR = lexer/

UTILS_DIR = utils/

EXEC_BUILTIN_DIR = exec/builtin/

EXEC_DIR = exec/

ERROR_DIR = error_manager/

ENVP_DIR = envp/

MAIN = 		main.c

SRCS =		${UTILS_DIR}splittos.c\
			${BUILTINS_DIR}echo_utils.c\
			${LEXER_DIR}token_utils.c\
			${ERROR_DIR}syntax_utils2.c\
			${ERROR_DIR}syntax_utils.c\
			${EXEC_DIR}exec_utils1.c\
			${ERROR_DIR}syntax_redir.c\
			${BUILTINS_DIR}echo2.c\
			${BUILTINS_DIR}export2.c\
			${BUILTINS_DIR}export3.c\
			${LEXER_DIR}expand_utils1.c\
			${BUILTINS_DIR}export4.c\
			${ERROR_DIR}quotes.c\
			${BUILTINS_DIR}cd2.c\
			${UTILS_DIR}shlvl.c\
			${UTILS_DIR}ft_strcmp.c\
			${UTILS_DIR}isnumber.c\
			${UTILS_DIR}ft_strsame.c\
			${LEXER_DIR}lexer_utils.c\
			${UTILS_DIR}ft_strtrim.c\
			${UTILS_DIR}malloc_list.c\
			${UTILS_DIR}ft_isalpha.c\
			${UTILS_DIR}ft_split_piscine.c\
			${UTILS_DIR}ft_strdup.c\
			${UTILS_DIR}array_list.c\
			${UTILS_DIR}megafree.c\
			${UTILS_DIR}ft_itoa.c\
			${EXEC_DIR}heredoc.c\
			${LEXER_DIR}lexer_utils_1.c\
			${LEXER_DIR}lexer.c\
			${LEXER_DIR}expand.c\
			${LEXER_DIR}expand_utils.c\
			${ENVP_DIR}env_list.c\
			${ENVP_DIR}env_list_utils.c\
			${BUILTINS_DIR}echo.c\
			${BUILTINS_DIR}env.c\
			${BUILTINS_DIR}cd.c\
			${BUILTINS_DIR}unset.c\
			${BUILTINS_DIR}export.c\
			${BUILTINS_DIR}exit.c\
			${BUILTINS_DIR}pwd.c\
			${EXEC_DIR}heredoc_utils.c\
			${UTILS_DIR}ft_strjoin.c\
			${LEXER_DIR}token.c\
			${LEXER_DIR}token_list_utils.c\
			${UTILS_DIR}join_str_in_init.c\
			${UTILS_DIR}ft_print_fd.c\
			${UTILS_DIR}ft_lstsize_token.c\
			${UTILS_DIR}ft_atoi.c\
			${EXEC_DIR}command_manager2.c\
			${EXEC_DIR}path2.c\
			${ERROR_DIR}error_manager.c\
			${EXEC_DIR}init_exec_init.c\
			${EXEC_DIR}exec.c\
			${EXEC_DIR}exec2.c\
			${EXEC_DIR}is_itcommand.c\
			${EXEC_DIR}file_manager.c\
			${EXEC_DIR}command_manager.c\
			${EXEC_DIR}path.c\
			${EXEC_BUILTIN_DIR}is_builtin.c\
			${EXEC_DIR}fd_manager.c\
			${EXEC_DIR}signals.c\




			



MAIN_M =	${MAIN:.c=.o}
OBJS =		${SRCS:.c=.o}

CC =		cc

RM =		rm -f

CFLAGS =	-Wall -Werror -Wextra -g3 -g

LFALGS = -lreadline #-fsanitize=address

all:		${NAME}

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${MAIN_M} ${OBJS}
		${CC} ${MAIN_M} ${OBJS} -o ${NAME} ${LFALGS} 

clean:
		${RM} ${OBJS}
		${RM} ${MAIN_M}


fclean:		clean
		${RM} ${NAME}

re:		fclean
		$(MAKE) all -j

.PHONY:		all clean fclean re
