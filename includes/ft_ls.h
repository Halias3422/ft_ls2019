/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/25 07:09:07 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/15 15:03:31 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "../libft/includes/libft.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <time.h>

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
**CHECK_PARAMS.C
*/

t_info				*check_params(int ac, char **av, t_info *info, t_args *args);
t_info				*ft_list_back(t_info *head, t_info *info);
void				check_file_name(char *arg, t_info *info, t_args *args);
void				check_args(char *arg, t_args *args, t_info *info);

/*
**FILL_FILE_INFOS.C
*/

void				fill_file_infos(t_info *info, t_args *args, struct stat fileStat);
void				fill_full_rights(t_info *info, struct stat fileStat);

/*
**FILL_FILE_RIGHTS.C
*/

void				fill_file_rights(t_info *info, struct stat fileStat);
char				*get_type_info_rights(t_info *info, struct stat fileStat);

/*
**ADD_COLORS.C
*/

void				add_colors(t_info *info, struct stat fileStat);

/*
**DIR_PASSED_AS_ARG.C
*/

t_info				*dir_passed_as_arg(t_info *info, t_args *args);
t_info				*get_content_of_dir(t_info *info, t_args *args, DIR *dirp, t_info *head);
/*
**DEAL_WITH_RECURSIVE.C
*/

void				deal_with_recursive(t_info *info, t_args *args);
void				print_rec_files(t_info *info, t_args *args);

/*
**SORT_ROOT.C
*/

t_info				*sort_error(t_info *info, t_args *args);
t_info				*sort_root(t_info *info, t_args *args);

/*
**SORT_LIST.C
*/

t_info				*sort_list_ascii(t_info *info);
t_info				*sort_list_s(t_info *info);
t_info				*sort_list(t_info *info, t_args *args);

/*
**SORT_LIST2.c
*/

t_info				*sort_list_reverse(t_info *info);
t_info				*sort_list_access(t_info *info);
t_info				*sort_list_time(t_info *info);

/*
**PRINT_ROOT.C
*/

void				final_print_inside_fold(t_info *folder, int len, t_args *args);
void				print_dir_content(t_info *info, t_args *args, t_info *folder
					, int len);
void				print_root(t_info *info, t_args *args);

/*
**EXTENDED_PRINTING.C
*/

void				extended_printing_root(t_info *info, t_args *args, int len);
void				print_block_size(t_info *info);

/*
**FREE.C
*/

void				free_list(t_info *lst, t_args *args);
void				free_one_list(t_info *lst, t_args *args);

#endif

