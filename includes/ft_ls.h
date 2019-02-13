/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/08 09:29:10 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 12:50:08 by vde-sain    ###    #+. /#+    ###.fr     */
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
	int				is_error;
	int				type;
	char			*rights;
	int				inodes;
	char			*user;
	char			*group;
	int				size;
	time_t			seconds;
	char			*date;
	struct s_info	*next;
	struct s_info	*next2;
	int				lvl_recursive;
}					t_info;

typedef struct		s_args
{
	char			*arg;
	int				is_file;
}					t_args;

/*
**		CHECK_PARAMS.C
*/

t_info			*check_params(int ac, char **av, t_info *info, t_args *args);
t_info			*ft_list_back(t_info *head, t_info *info);
void			check_file_name(char *arg, t_info *info, t_args *args);
void			check_args(char *arg, t_args *args, t_info *info);

/*
**		FILL_FILE_INFOS.C
*/

void			fill_file_infos(t_info *info, t_args *args, struct stat fileStat);
void			fill_full_rights(t_info *info, struct stat fileStat);

/*
**		DEAL_WITH_RECURSIVE.C
*/

t_info			*deal_with_recursive(t_info *info, t_args *args);

/*
**		FREE.C
*/

void			free_list(t_info *lst);

#endif
