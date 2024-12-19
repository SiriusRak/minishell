/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enarindr <enarindr@student.42antananarivo. +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:06:04 by rdiary            #+#    #+#             */
/*   Updated: 2024/12/19 18:44:41 by enarindr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "builtin.h"
# include "struct.h"

int			ft_lstfree(t_d_list **list);
int			ft_free_t_d_list(t_d_list *lst);
int			ft_free_tab(char **tab);
int			ft_iswite_space(char c);
int			ft_notsep(char c);
int			ft_get_input(t_data *data);
int			ft_add_list(t_data *data, int start, int i, char *str);
int			ft_find_next_quote(char *str, int start, char c, t_data *data);
int			ft_find_next_quote_2(char *str, int start, char c);
int			ft_exit_quote(char *str, t_data *data);
int			ft_get_input(t_data *data);
int			ft_take_pipe(char *str, t_data *data);
int			ft_clear_history(t_data *data);
int     	ft_clear_heredoc(t_data *data);
int			ft_free_data(t_data *data);
int			ft_pipe_error(char *str, int i);
int			ft_check_list(t_data *data);
int			ft_lex(t_d_list *list, char *str);
int			ft_lex_ext(t_d_list *list, char **tab, int i);
int			ft_pars(t_d_list *list);
int			ft_pars_ext(char *str, char **tmp, int i, char c);
int			ft_add_out(t_d_list *list, char *str, int i);
int			ft_add_in(t_d_list *list, char *str, int i);
int			ft_add_cmd(t_d_list *list, char *str);
int			ft_check_error(char *str);
int			ft_expand(t_d_list *list, char **chn, int i, int quote);
int			ft_pars_error(t_list *list);
int			ft_all_error(t_d_list *list);
int			ft_readline(t_data *data);
int			ft_chek_sig(t_data *data);
int			ft_chek_sig_cmd(t_data *data);
int			ft_pipe(t_data *data);
int			pre_treat(t_data *data, int i);
int			pre_treat_ext(t_data *data);
int			check_after_child(t_data *data);
int			ft_count_line(char **strings);
int			ft_check_cmd(t_data *data, char *cmd, int is_dir, int c);
int			ft_dlstsize(t_d_list *lst);
int			ft_isdir(t_data *data, char *cmd, int c);
int			ft_redir_input(t_list *in);
int			ft_cd_error(char *cmd, int i, char **old, char **pwd);
int			*ft_manage_exec(t_data *data, char *cmd, int i);
int			ft_check_redir(t_data *data, int *pipe_fd, int fd_in, int i);
int			ft_clean(t_d_list **list, char **str, int i, int type);
int			ft_expand_4(char **chn, int i, char *str, int quote);
int			ft_expand_3(t_d_list *list, char **chn, int i, char *str);
int			ft_expand_1(char **chn, int i, char *str);
int			ft_expand_2(t_d_list *list, char **chn, int i, char *str);
int			ft_take_pipe_ext(t_data *data, int i, char *str, int *start);
int			ft_manage_cmd(t_data *data, int i);
int			ft_lex_ext2(t_d_list *list, char **tab, int i);

char		*ft_epure_line(char *str, int i, int j);
char		*ft_epure_redir(char *str);
char		*ft_arrange_prev_redir(char *str);
char		*ft_arrange_back_redir(char *str);
char		*ft_epure_space(char *str, int i, int j);
char		*ft_get_value(char *key, t_list *env);
char		*ft_expand_key(t_d_list *list, char *str, int start);
char		*ft_expand_here(t_d_list *list, char *ch);
char		*ft_clean_quote(t_d_list *list, char *str, int type);
char		*take_script(int fd);
char		*ft_manage_path(char **s_path, char *f_path, char *cmd);
char		*ft_clean_ext(char *str, int i);
char		*ft_add_heredoc(t_d_list *list, char *str, int c);
char		**ft_lst_to_char(t_list *list, int type);
char		**ft_sort_tab(char **tab);

void		ft_exit_1(t_data *data, int exit_code);
void		ft_exit_child(t_data *data, int exit_code);
void		ft_exit_pipe(char *str, t_data *data);
void		ft_init(t_data *data, char **env);
void		ft_add_front_list(t_d_list **list, t_d_list *new);
void		ft_add_back_list(t_d_list **list, t_d_list *new);
void		signal_handler(int sig, siginfo_t *info, void *context);
void		waiting_signal(t_data *data);
void		signal_heredoc(t_data *data);
void		handler(int sig, siginfo_t *info, void *context);
void		waiting_signial_here(t_data *data);
void		signal_handler_here(int sig, siginfo_t *info, void *context);
void		signal_handler_cmd(int sig, siginfo_t *info, void *context);
void		waiting_signial_cmd(t_data *data);
void		ft_clear_input(t_data *data);
void		ft_free_split(char **strings);
void		ft_redir(t_data *data, t_list *out, int i);
void		ft_execute(t_data *data);
void		ft_export_no_arg(t_data *data);
void		ft_execute_builtin(t_data *data, char *cmd);
void		ft_print_error(char *cmd, char *message);
void		ft_add_file(char *content, char *file);
void		ft_export_error(char *str, int i, char c);
void		ft_manage_fd(int *pipe_fd, int fd_in, int i, t_data *data);
void		ft_wait_pid(t_data *data, int nbr_cmd, int fd_in);
void		ft_child_exec(t_data *data, char **env, char **arg);
void		ft_inputerror(int *pipe_fd, int fd_in);

t_list		*ft_duplicate(char **str);
t_d_list	*ft_newlist(char *content, t_data *data);

#endif
