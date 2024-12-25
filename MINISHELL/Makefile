SRC = ./execution/all_basic_functions.c ./execution/cd.c  ./execution/cd_2.c  ./execution/cd_function_utils.c \
./execution/export_again.c ./execution/export_again_2.c ./execution/export_again_3.c ./execution/cd_utils.c \
./execution/tree_recursion/execution.c ./execution/tree_recursion/execution_4.c ./execution/tree_recursion/execution_2.c ./execution/cd_add_file.c ./execution/tree_recursion/cmd.c ./execution/tree_recursion/cmd_2.c\
./execution/tree_recursion/execution_3.c ./execution/exit.c ./execution/export_function.c ./execution/export_function_utils.c \
 ./execution/pwd_path.c ./execution/export_last.c ./execution/export_last_2.c ./execution/other_export.c \
./execution/wild_card.c ./execution/wild_card_2.c ./execution/wild_card_3.c ./execution/wild_card_4.c ./parsing/check_validity.c ./parsing/check_validity_2.c ./parsing/check_validity_3.c ./parsing/parsing.c ./execution/expo_u.c \
./utils/plus_5_functions.c ./parsing/skip_empty_blocks.c ./parsing/parsing_tools.c ./parsing/here_doc.c ./parsing/extra_pars.c ./utils/gc.c ./utils/tools/executions_tools.c ./utils/tools/built_ins_extra.c ./utils/tools/built_ins_extra_2.c ./utils/tools/extra_built.c ./utils/tools/extra_b_test.c\
./utils/tools/built_ins_extra_3.c ./utils/tools/built_ins_extra_4.c ./utils/tools/built_ins_extra_5.c ./utils/tools/for_the_5_built.c \
./utils/tools/built_ins_extra_6.c ./utils/tools/built_ins.c  ./utils/tools/expanding.c ./utils/tools/extra_tools.c ./utils/tools/extra_tools_2.c ./utils/tools/b_test.c ./utils/tools/z_test.c\
./utils/libft_functions/libft_functions_1.c ./utils/libft_functions/libft_functions_2.c ./utils/libft_functions/split.c \
./utils/libft_functions/libft_functions_3.c ./utils/libft_functions/tab_split.c ./utils/list_center.c ./utils/tree.c ./utils/tree_tools.c ./utils/tree_2.c ./utils/tree_3.c \
./utils/initialisers.c ./utils/initialisers_2.c ./utils/rediractions_tools.c ./utils/tools/add_extra_file.c  main.c

READLINE_L = $(shell brew --prefix readline)/lib
READLINE_I = $(shell brew --prefix readline)/include

CFLAG = -Wall -Wextra -Werror 
OBJ = $(SRC:.c=.o)


LINKING = -lreadline 

NAME = minishell

all: $(NAME)


$(NAME): $(OBJ)
	${CC} ${CFLAG} ${OBJ} -o ${NAME} -L ${READLINE_L} -lreadline
%.o: %.c minishell.h
	${CC} ${CFLAG}  -I ${READLINE_I} -c $< -o $@ 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean