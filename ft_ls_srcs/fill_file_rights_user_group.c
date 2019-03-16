/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_file_rights.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/15 07:38:42 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/16 16:02:53 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void				fill_group_info(t_info *info, struct stat filestat,
					t_args *args)
{
	int				user_gid;
	struct group	*user_group;

	user_gid = filestat.st_gid;
	user_group = getgrgid(user_gid);
	if (user_group != NULL)
	{
		info->group = free_strjoin(info->group, "\033[1;30m");
		info->group = free_strjoin(info->group, user_group->gr_name);
		info->group = free_strjoin(info->group, "\033[0m  ");
	}
	else
		info->group = ft_itoa(user_gid);
	if (ft_strlen(info->user) > args->biggest_usr)
		args->biggest_usr = ft_strlen(info->user);
	if (ft_strlen(info->group) > args->biggest_grp)
		args->biggest_grp = ft_strlen(info->group);
}

void				fill_user_info(t_info *info, struct stat filestat,
					t_args *args)
{
	int				user_uid;
	struct passwd	*user_name;

	info->user = ft_strnew(0);
	info->group = ft_strnew(0);
	user_uid = filestat.st_uid;
	user_name = getpwuid(user_uid);
	if (user_name != NULL)
	{
		info->user = free_strjoin(info->user, " \033[1;34m");
		info->user = free_strjoin(info->user, user_name->pw_name);
		info->user = free_strjoin(info->user, "\033[0m ");
	}
	else
	{
		info->user = free_strjoin(info->user, " \033[1;34m");
		info->user = free_strjoin(info->user, ft_itoa(user_uid));
		info->user = free_strjoin(info->user, "\033[0m");
	}
	fill_group_info(info, filestat, args);
}

char				*get_type_info_rights(t_info *info, struct stat filestat)
{
	if (filestat.st_mode & S_IFIFO)
		info->rights[0] = 'p';
	if (filestat.st_mode & S_IFCHR)
		info->rights[0] = 'c';
	if (filestat.st_mode & S_IFDIR)
		info->rights[0] = 'd';
	if (filestat.st_mode & S_IFREG)
		info->rights[0] = '-';
	if (filestat.st_mode & S_IFCHR && filestat.st_mode & S_IFDIR)
		info->rights[0] = 'b';
	if (filestat.st_mode & S_IFREG && filestat.st_mode & S_IFCHR)
		info->rights[0] = 'l';
	if (filestat.st_mode & S_IFREG && filestat.st_mode & S_IFDIR)
		info->rights[0] = 's';
	info->rights[10] = ' ';
	info->rights[11] = '\0';
	return (info->rights);
}

void				fill_file_rights(t_info *info, struct stat filestat)
{
	if (!(info->rights = (char*)malloc(sizeof(char) * 12)))
		return ;
	get_type_info_rights(info, filestat);
	info->rights[1] = (filestat.st_mode & S_IRUSR) ? 'r' : '-';
	info->rights[2] = (filestat.st_mode & S_IWUSR) ? 'w' : '-';
	info->rights[3] = (filestat.st_mode & S_IXUSR) ? 'x' : '-';
	if (info->rights[3] != 'x')
		info->rights[3] = (filestat.st_mode & 04000) ? 'S' : info->rights[3];
	else
		info->rights[3] = (filestat.st_mode & 04000) ? 's' : info->rights[3];
	info->rights[4] = (filestat.st_mode & S_IRGRP) ? 'r' : '-';
	info->rights[5] = (filestat.st_mode & S_IWGRP) ? 'w' : '-';
	info->rights[6] = (filestat.st_mode & S_IXGRP) ? 'x' : '-';
	if (info->rights[6] != 'x')
		info->rights[6] = (filestat.st_mode & 02000) ? 'S' : info->rights[6];
	else
		info->rights[6] = (filestat.st_mode & 02000) ? 's' : info->rights[6];
	info->rights[7] = (filestat.st_mode & S_IROTH) ? 'r' : '-';
	info->rights[8] = (filestat.st_mode & S_IWOTH) ? 'w' : '-';
	info->rights[9] = (filestat.st_mode & S_IXOTH) ? 'x' : '-';
	if (info->rights[9] != 'x')
		info->rights[9] = (filestat.st_mode & 01000) ? 'T' : info->rights[9];
	else
		info->rights[9] = (filestat.st_mode & 01000) ? 't' : info->rights[9];
}
