/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dohelee <dohelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 17:14:59 by dohelee           #+#    #+#             */
/*   Updated: 2021/07/31 18:06:29 by dohelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/types.h> 
# include <sys/stat.h>

# define PATHLEN_MAX 4096
# define SINGLE 1
# define DOUBLE 2
# define RR 3
# define LL 4
# define R 5
# define L 6
# define PIPE 7
# define SPACING 8
# define DOLLAR 9
# define ARG 0
# define CMD 11

typedef struct s_pipe
{
	char			**f_cmd;
	char			**s_cmd;
	char			*path;
	char			*infile;
	char			*outfile;
}					t_pipe;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	int				in;
	int				out;
	t_token			*out_t;
	t_token			*in_t;
}					t_redir;

typedef struct s_state
{
	char			*input;
	t_token			*head;
	int				ret;
	t_env			*env;
	char			**path;
	int				redirected_fd;
	int				save_fd;
	int				type;
	bool			cmd_using;
	int				cmd_status;
	int				cmd_pid;
	bool			heredoc_using;
	int				heredoc_status;
	int				heredoc_fd;
	t_token			*redirection;
	int				len;
	char			***cmd;
	t_redir			**re;
	int				flag;
	int				fd_in;
	int				fd_out;
	struct stat		buf;
}					t_state;

t_state	g_state;

t_env	*init_env(t_env *env, char *value);
void	free_env(t_env *tmp);
t_env	*get_env(t_env *env, char *key);
void	env_parsing(t_env *tmp, char *variable);

void	add_env(t_env *env, char *variable);
void	delete_env(t_env *env, char *key);
void	show_env(t_env *env);

void	sig_handler(int sig_num);
void	heredoc_sig_handler(int sig_num);

int		ft_strcmp(char *arr1, char *arr2);

int		redirect_right_single(char *file);
int		redirect_right_double(char *file);
int		redirect_left_single(char *file);
int		redirect_left_double(char *str);

int		check_redirect(t_redir *re);
int		read_heredoc(char *str);

void	parser(int i, int j);

int		check_quote(char *s, int flag_d, int flag_s);
t_token	*create_token(char *str, int type);
int		has_type(char *input, int i);
char	*return_envval(char *buf);

char	*convert_dollar(char *s, int idx, int i, char *value);
char	*treat_dollar(int len, int idx, int i);
void	treat_quote(int type);
void	generate_token(char *buf, int type, int len);

void	ft_cmd(t_token *token, char **path);

char	*parse_path(char *cmd, int i);
char	*get_path(char **env);

void	loop_pipe(char ***arg, char **env, int cnt, t_redir **re);

int		ft_echo(char **arg);
void	ft_cd(char **arg);
int		check_exitarg(char **arg);

void	check_cmd2(char **arg, char **env);
int		check_cmd(char **arg, int *i);
int		ft_re(t_redir *re, int flag);
void	child_process(int cnt, int *fd, t_redir *re, int i);
void	parent_process(int pid, int *fd, t_redir *re, int *i);

void	env_free(t_env *env);

#endif