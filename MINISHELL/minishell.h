/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:21:05 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/27 09:43:04 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

enum
{
	OR,
	AND,
	PIPE,
	REDIR_IN,
	WORD,
	DOLLAR,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	PARA_OPEN,
	PARA_CLOSE,
	D_QU,
	S_QU,
	SPACEE,
} ;

typedef struct all_not_vars
{
	DIR				*curenet_dir;
	int				total;
	int				index ;
	int				up ;
	int				increment ;
	char			**allocation ;
	char			*aloca;
	int				flag ;
	char			*var ;
	char			*for_current ;
	char			*res_type ;
	int				check;
	long long		res;
	int				saftey;
	int				minis;
}	t_all_not_vars;

typedef struct all_vars
{
	char	*in_here ;
	char	*tmp;
	int		positon ;
	char	*env;
	int		index;
	int		increment;
	int		flag;
	char	*get_path;
	int		res_type;
	char	*allocation;
	char	*see_path;
	int		check_flag;
	int		this_path;
	int		for_total;
	char	*for_cd;
	char	*path_to;
	int		hold;
	char	*worck_with;
	char	*for_res;
	char	*make_sure;
	char	**twode;
	int		know;
}	t_all_vars;

typedef struct s_gc
{
	struct s_gc	*next;
	void		*address;
	int			fd;
	int			flag;
}	t_gc;

typedef struct s_tracker
{
	struct s_list	*head;
	struct s_list	*tail;
	char			**env;
	int				flag;
}	t_tracker;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			*content;
	int				fd_out;
	int				fd_in;
	int				is_visited;
	int				is_good;
	int				token_type;
	int				q_type;
}	t_list;

typedef struct s_tree_helper
{
	int				pipe_i;
	int				def_in;
	int				def_out;
	int				sav_in;
	int				sav_out;
	int				red_in;
	int				red_out;
	int				**pipes;
	int				*fds;
	char			**env;
	char			**path;
	char			**export;
	struct s_tree	*root;
	struct s_tree	*next_target;
	char			*extra_save;
}	t_th;

typedef struct s_tree
{
	char			*extra_save;
	char			*saved;
	char			**content;
	char			**fds_in;
	char			**fds_out;
	int				exit_status;
	int				is_in_pipe;
	int				token_type;
	int				here_fd;
	int				fd_out;
	int				fd_in;
	struct s_tree	*right;
	struct s_tree	*left;
	int				*b_q;
	t_th			*tree_h;
}	t_tree;

typedef struct s_pt
{
	int	s_bool;
	int	bo_bool;
	int	bc_bool;
	int	d_bool;
	int	e_bool;
	int	ex_bool;
}	t_pt;

typedef struct for_path
{
	int		index ;
	char	**allocation ;
	int		place;
	int		flag;
	int		increment;
	char	*save ;
}	t_path;

void		for_one_if(char *string, t_tree *leaf);
void		for_condition(t_tree *leaf, char *string, int export);
int			function_helper_two(t_tree *leaf);
int			function_search_for(char *value, char **env);
int			return_place(char *value, char **env);
int			check_com(char *for_cd, char **env, t_tree *leaf);
int			return_int_pwd_path(char **env, char *new_env);
int			on_all(char *string, int check);
int			sec_check(char string);
int			loop_on_all(char *string, int check);
int			add_function_helper(char *for_current, t_tree *leaf);
void		return_extra(t_tree *leaf, char *new_env);
int			wait_for_here_doc(int pass);
void		for_this_one(char *string, t_tree *leaf, int e);
char		**keep_only_what_to_start_find(char **res_type, char *start);
char		**check_both(char **all_in, char *string);
char		**check_in_every(char **all_in, char *string);
void		for_pwd(char *p);
int			check_this_start(char *string, char *compare);
void		for_plus_check(char *string, t_tree *leaf, int *export);
char		**delet_from(char **env, int position);
void		for_the_export(char **env, t_tree *leaf);
int			check_if_it_valid(char string);
int			one_check(char string);
int			check_quotes_only(char *string);
int			res_index(char *string, char here);
int			search_inside(char *string, char *what_to);
char		**check_sides(char **all_in, char *string, char *last_string);
char		**function_this_one(char *much_start, char *much_end, \
int choose, int first_pos);
void		function_check_wild_card(t_tree *leaf);
char		**function_to_check(char **env, int here, char *put);
char		*function_check_wild_card_builts(char *string, int *var);
int			check_if_in_env(char **env, char *value);
int			function_for_echo(t_tree *leaf);
char		*merge_to(char *string, char *merge);
int			ft_strcmp(char *s1, char *s2);
void		jump_over_leftside(t_list **node);
void		signals_handler(int sign);
void		ft_bzero(void *s, size_t n);
void		*gc(int size, int pass, int flag, int exit_status);
char		**tab_split(char *s);
int			exit_status(int state, int mode);
char		*expand_factory(char *to_expand, char **env, int *am, int pass);
int			ft_strncmp(char *s1, char *s2, int n);
int			ft_strlen(const char *s);
int			look_space(t_tree *leaf);
char		*ft_substr(char *s, unsigned int start, int len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strtrim(char *s, char *set);
char		*ft_strchr(char *s, int c);
char		*ft_itoa(int n);
void		add_dollar(t_list **tmp);
char		*checking(t_list *tmp);
char		**generate_cmd(char **string);
void		add_fd(t_tree *leaf, int fd);
t_list		*look_for(t_list *tmp, int token_type, int var);
void		add_to_list_single(t_tracker *holder, char *input, int *start);
void		add_to_list_double(t_tracker *holder, \
char *input, int start, int *end);
int			compare(t_list *tmp, int token);
int			is_good(t_list *tmp, t_list *tmp_2);
t_tree		*parsing(char *input, t_th *tree_h);
char		*skip_empty_blocks(char *input);
char		*cut_string(char *string, int start, int finish);
int			check_validity(t_tracker *holder);
int			is_delimiter(char c, int pass);
char		*delete_opening_quotes(char *string, int quotes_type);
char		**ft_split(char *s, char c);
int			check_para(t_list *tmp);
int			check_para_2(t_list *tmp);
int			is_empty(char *input);
int			here_comp(char *s1, char *s2, int n);
char		*set_delimiter(t_list **tmp, int *bool);
char		*add_to_string(char *string, char *to_add, int start, int end);
t_tree		*creat_leaf(t_list *node, t_th *tree_h);
t_list		*search_for(t_list *node);
void		merge_nodes(t_list *starting_point, \
t_list *ending_point, int new_type);
t_tree		*tree_generator(t_list *node, t_th *tree_h);
void		join_quotes(t_list **starting_point);
int			run_here_doc(t_list *tmp, char **env);
void		reset_to_right(t_list **node);
void		reset_to_left(t_list **node);
void		fill_content(t_list **tmp, t_tree *leaf);
void		jump_over(t_list **tmp_3);
char		**build_cmd(t_tree *leaf);
void		set_content(t_list *tmp_2, t_list *tmp, t_tree *leaf, int size);
void		jump_over(t_list **node);
int			detect_para(t_list *node, int *i);
t_list		*jump_over_2(t_list *node);
void		check_for_prev(t_list **node);
int			limit_check(char *string);
void		check_for_next(t_list **node);
void		fill_node(t_gc *node, void *address, int fd, int flag);
int			cmd(t_tree *leaf);
void		close_fds(t_tree *leaf);
char		**path_maker(char **env);
int			*add_pipes(t_th *tree_h);
int			my_fork(void);
int			*my_pipe(void);
char		*check_access(t_tree *leaf, t_th *tree_h, char *cmd);
void		exec_left(t_tree *leaf, int *pipe);
void		exec_right(t_tree *leaf, int *pipe);
int			is_built(t_tree *leaf);
int			what_qoutes(char *s);
int			exec_red_in(t_tree *leaf);
int			exec_red_out(t_tree *leaf);
void		exit_c(int sign);
int			cd_function(char *path, char **env, t_tree *leaf);
int			check_string(char *string, char *what_to_compare);
int			count_word(char *string);
int			le_count(char *string);
void		putstr(char *string);
char		*merge_path(char *string, char *path_add);
void		paste(char string);
int			check_if_to_turn(char *path, char **env, t_tree *leaf);
int			check_res_type(int res_type, char *path, char *for_cd);
int			check_cd(char *path);
int			merge_function(char *path, char **env, t_tree *leaf);
int			helper_parc(t_list *tmp_2, int pass);
int			function_for_exit(char *string);
char		*remove_cd(char *string, char *ignore);
int			all_white(char string);
char		**move_env(char **env);
int			open_in(t_tree *leaf);
char		*remove_cd(char *string, char *ignore);
char		*flag_last(char *string, char flag_this);
char		*return_line(char *string);
char		**copy_twode(char **string);
int			all_white(char string);
char		*copy_for_remove_string(char *allocation, char *string);
char		*remove_string(char *string, char *to_move);
char		*copy_till_charac(char *string, char to_here);
char		*return_this(char *string, char *merge);
int			execution(t_tree *root_tree);
char		**put_check_env(char *check, char *value, char **env);
int			search_in_for(char *string, char search);
char		**put_check_env(char *check, char *value, char **env);
int			check_function_compare(char *string, char *check);
int			return_before_equal(char *value, char **env, char *all_this);
char		**add_it_to_env(char **env, char *string);
char		**add_it_to_env_index(char **env, char *string, int here);
char		*for_herdoc(char *string, char **env);
void		check_if_checked(char *string, t_tree *leaf);
int			only_pass(t_tree *leaf);
int			turn_dir(char **env, t_tree *leaf, char *p);
int			loop_check(char *string);
int			return_invalid(char string);
char		**extract_check(char *string, t_tree *leaf);
char		*copy_after_find(char *string, char here);
int			open_here_doc(t_list *tmp);
void		put_tmp(char *in, int fd, char **env, int bool);
char		*merge_both( char *add, char *string_added);
int			count_twode(char **string);
void		function_export(t_tree *leaf, int up);
void		function_down_cd(t_tree *leaf, char *p);
void		funcrtion_this_exit(t_tree *leaf);
char		**for_the_unset(char **env, char *var_name);
void		print_env(char **env, t_tree *leaf);
int			check_last_elem(char *string, char to_check);
char		**check_space(char **string);
int			turn_position(char *string, char here);
int			function_unset(t_tree *leaf);
void		check_dollar(t_list	**tmp, t_list *next);
void		print_error(char *error, char *arg);
void		function_check_wild_card_cmds(t_tree *leaf);
char		*delete_first_and_last(char *string);
char		**add_to_content(char **wild, char **content, int index);
char		*cut_star(char *string);
int			open_out(t_tree *leaf, int token_type);
int			here_para(int pass);
void		is_quotes(char *string, int *bool);
int			is_empty(char *input);
int			exec_word(t_tree *leaf);
int			is_quotes_only(char **input, int i);
int			is_space(char *string);
int			wild_case(char *input);
int			not_empyt_quote(char *input);
int			all_sapce(char *input);
int			check_if_ended(t_pt *bool, int pass);
void		if_export(char	**content, t_pt	*bool);
void		update_new(char	**new, char	**content, char *tmp, t_pt *bool);
char		**wild_helper(char *string);
int			*re_size_array(int *first_array, int new_input, \
int old_input, int index);
char		*function_array_line(char **env);
void		skip_red(t_list **tmp_2);
char		*file_check(t_tree *leaf);
void		incrementt(int *flag, int *index, int *increment);
int			para_red(t_list *tmp_2);
void		close_herefiles(t_tracker *holder);
void		adress_unset(int *flag, int *increment, int *index, int cap);
void		add_function_export(t_tree *leaf);
int			if_else(char string);
char		**return_it_for_sure(int first_pos, DIR	*curenet_dir);
int			my_dup(int file);
int			my_dup2(int file_1, int file_2);
void		close_pipes(t_tree *leaf);
char		**merge_and_sort(char **arr_1, char **arr_2);
long long	convert_number(char *string);
int			check_exist_in_env(char *value, char **env);
int			check_n(char **string, int *index);
char		*only_for_one_of_this_add(char *string, char to_here);
int			export_check(t_tree *leaf);
char		*dollar_exp(char *to_modify, int *b, int i);
int			is_digit(char c);
int			is_alnumex(char c);
char		*delete_opening_quotes_only(char *string);
char		*return_malloc(char *string);
void		set_bq(char **res, t_tree *leaf, int index, int size);
void		on_new(void);
int			initial_checks(void);
#endif