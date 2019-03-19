/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 07:09:07 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/19 09:15:37 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/includes/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>

typedef struct		s_info
{
	char			*file;
	char			*path;
	char			*color;
	int				is_error;
	int				type;
	char			*rights;
	int				inodes;
	char			*user;
	char			*group;
	int				major;
	int				minor;
	int				size;
	int				blk_size;
	time_t			access;
	int				access_equal;
	time_t			seconds;
	char			*date;
	struct s_info	*next;
	struct s_info	*next2;
	int				sub_folder;
	long long		total_size;
	int				printing;
	int				forbidden;
	int				first_link;
}					t_info;

typedef struct		s_args
{
	int				dot_arg;
	char			*arg;
	size_t			biggest_word;
	size_t			biggest_inodes;
	size_t			biggest_usr;
	size_t			biggest_grp;
	size_t			biggest_size;
	size_t			biggest_major;
	size_t			biggest_minor;
	int				sub_fold_nb;
	int				nb;
	int				dir_nb;
	int				nb_files;
	int				is_file;
	int				printed;
}					t_args;

/*
**MAIN.C
*/

int					main(int ac, char **av);
void				check_nb_files(int ac, char **av, t_args *args);
int					init_info_link(t_info *info, int link_nb);
void				init_args(t_args *args);

/*
**CHECK_PARAMS.C
*/

t_info				*check_params(int ac, char **av, t_info *info,
					t_args *args);
t_info				*check_multiple_params(int ac, char **av, t_info *info,
					t_args *args);
t_info				*ft_list_back(t_info *head, t_info *info);
void				check_file_name(char *arg, t_info *info, t_args *args);
void				check_args(char *arg, t_args *args, t_info *info);

/*
**FILL_FILE_INFOS.C
*/

void				fill_file_infos(t_info *info, t_args *args,
					struct stat filestat);
void				get_minor_and_major(t_info *info, struct stat filestat,
					t_args *args);
void				get_date_info(t_info *info, struct stat filestat,
					t_args *args);
void				fill_date_info(t_info *info, time_t ret, char *second);
void				fill_full_rights(t_info *info, struct stat filestat);

/*
**FILL_FILE_RIGHTS_USER_GROUP.C
*/

void				fill_file_rights(t_info *info, struct stat filestat);
char				*get_type_info_rights(t_info *info, struct stat filestat);
void				fill_user_info(t_info *info, struct stat filestat, t_args
					*args);
void				fill_group_info(t_info *info, struct stat filestat,
					t_args *args);

/*
**ADD_COLORS.C
*/

void				add_colors(t_info *info, struct stat filestat);

/*
**DIR_PASSED_AS_ARG.C
*/

t_info				*dir_passed_as_arg(t_info *info, t_args *args);
t_info				*get_content_of_dir(t_info *info, t_args *args, DIR *dirp,
					t_info *head);
t_info				*fill_content_of_dir(struct dirent *read, t_info *head,
					t_args *args, char *curr_file);
/*
**DEAL_WITH_RECURSIVE.C
*/

void				deal_with_recursive(t_info *info, t_args *args);
void				go_end_folder(t_info *folder, t_args *args, t_info *info,
					t_info *head);
t_info				*iterating_through_fold(t_info *info, t_info *folder,
					t_args *args);
t_info				*dir_inside_recursive(t_info *info, t_args *args);
void				print_rec_files(t_info *info, t_args *args);

/*
**SORT_ROOT.C
*/

t_info				*sort_root(t_info *info, t_args *args);
t_info				*sort_root_by_args(t_info *info, t_args *args);

/*
**SORT_ERROR.C
*/

t_info				*sort_error(t_info *info, t_args *args);
t_info				*print_error(t_info *info);
t_info				*move_error_back(t_info *info, t_info *error);

/*
**SORT_LIST.C
*/

t_info				*sort_list(t_info *info, t_args *args);
t_info				*sort_list_time_acc_size(t_info *info, t_args *args, int i,
					int check);
t_info				*sort_list_ascii(t_info *info);
t_info				*add_node_middle_ascii(t_info *info, t_info *ne);
void				add_node_middle_list(t_info *info, t_info *ne, t_info *tmp,
					t_info *tmp2);

/*
**SORT_LIST2.c
*/

t_info				*sort_list_s(t_info *info);
t_info				*add_node_middle_s(t_info *info, t_info *ne);
t_info				*sort_list_time(t_info *info);
t_info				*add_node_middle_time(t_info *info, t_info *ne);

/*
**SORT_LIST3.C
*/

t_info				*sort_list_access(t_info *info);
t_info				*add_node_middle_access(t_info *info, t_info *ne);
t_info				*sort_list_reverse(t_info *info);

/*
**PRINT_ROOT.C
*/

void				print_root_and_dirs(t_info *info, t_args *args,
					t_info *head, int len);
void				printing_depending_on_file(t_info *info, t_args *args,
					int len, int printed);
void				print_dir_content(t_info *info, t_args *args, t_info *folder
					, int len);
void				print_dir_content_two(t_info *info, t_info *folder,
					t_args *args, int len);
void				print_root(t_info *info, t_args *args);

/*
**EXTENDED_PRINTING.C
*/

void				extended_printing_root_one(t_info *info, t_args *args,
					int len);
void				extended_printing_root_two(t_info *ifndenfo, t_args *args,
					int len);
void				print_block_size(t_info *info);
void				print_major_minor(t_info *info, int len, t_args *args);

/*
**EXTRA_FT_PRINT.C
*/

void				print_spaces(size_t nb1, size_t nb2, int len);
void				printing_link(t_info *info, t_args *args);
void				final_print_inside_fold(t_info *folder, int len,
					t_args *args);
void				print_content_of_single_dir_one(t_info *info, t_args *args);
void				print_content_of_single_dir_two(t_info *info, t_args *args,
					t_info *folder, int len);

/*
**FREE.C
*/

void				free_list(t_info *lst, t_args *args);
void				free_one_list(t_info *lst, t_args *args);

#endif
