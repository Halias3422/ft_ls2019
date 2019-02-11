/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/08 09:29:10 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/11 15:37:18 by vde-sain    ###    #+. /#+    ###.fr     */
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
	int				is_error;
	char			*rights;
	int				inodes;
	char			*user;
	char			*group;
	int				size;
	char			date;
	char			*name;
	struct s_info	*next;
}					t_info;

typedef struct		s_args
{
	char			*arg;
	int				is_file;
}					t_args;

/*
**		CHECK_PARAMS.C
*/

void			check_params(int ac, char **av, t_info *info, t_args *args);

#endif
