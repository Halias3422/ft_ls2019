/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_file_infos.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 12:18:21 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/15 15:56:35 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"
/*
void				fill_file_rights(t_info *info, struct stat fileStat)
{
	if (!(info->rights = (char*)malloc(sizeof(char) * 11 + 1)))
	{
		free(info);
		exit (-1);
	}
	info->rights[0] = (fileStat.st_mode & S_IFCHR) ? 'c' : '-';
	info->rights[0] = (fileStat.st_mode & S_IFDIR) ? 'd' : info->rights[0];
	info->rights[0] = (fileStat.st_mode & S_IFIFO) ? 'p' : info->rights[0];
	info->rights[0] = (fileStat.st_mode & S_IFCHR && fileStat.st_mode &
			S_IFDIR) ? 'b' : info->rights[0];
	info->rights[0] = (fileStat.st_mode & S_IFREG && fileStat.st_mode &
			S_IFCHR) ? 'l' : info->rights[0];
	info->rights[0] = (fileStat.st_mode & S_IFREG && fileStat.st_mode &
			S_IFDIR) ? 's' : info->rights[0];
	info->rights[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
	info->rights[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
	info->rights[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
	if (info->rights[3] != 'x')
		info->rights[3] = (fileStat.st_mode & 04000) ? 'S' : info->rights[3];
	else
		info->rights[3] = (fileStat.st_mode & 04000) ? 's' : info->rights[3];
	info->rights[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
	info->rights[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
	info->rights[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
	if (info->rights[6] != 'x')
		info->rights[6] = (fileStat.st_mode & 04000) ? 'S' : info->rights[6];
	else
		info->rights[6] = (fileStat.st_mode & 04000) ? 's' : info->rights[6];
	info->rights[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
	info->rights[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
	info->rights[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
	if (info->rights[9] != 'x')
		info->rights[9] = (fileStat.st_mode & 04000) ? 'T' : info->rights[9];
	else
		info->rights[9] = (fileStat.st_mode & 04000) ? 't' : info->rights[9];
	info->rights[10] = '\0';
}
*/

void				fill_user_group_info(t_info *info, struct stat fileStat, t_args *args)
{
	int				user_uid;
	struct passwd	*user_name;
	int				user_gid;
	struct group	*user_group;

	info->user = ft_strnew(0);
	info->group = ft_strnew(0);
	user_uid = fileStat.st_uid;
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
	user_gid = fileStat.st_gid;
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

void				fill_date_info(t_info *info, time_t ret, char *second)
{
	int				i;
	int				k;

	k = 0;
	i = 4;

	info->date[k++] = ' ';
	if (info->seconds < ret - 15778800 || info->seconds > ret + 15778800)
	{
		while (second[i] && i < 24)
		{
			if (i == 10)
			{
				info->date[k++] = ' ';
				i = 19;
			}
			info->date[k++] = second[i++];
		}
	}
	else
	{
		while (second[i] && i < 16)
			info->date[k++] = second[i++];
	}
}

void				get_date_info(t_info *info, struct stat fileStat, t_args *args)
{
	time_t			stat_time;
	char			*second;
	time_t			*curr_time;
	time_t			ret;

	curr_time = 0;
	ret = 0;
	ret = time(curr_time);
	info->date = ft_strnew(14);
	if (is_contained_in("u", args->arg, 0) <= 0)
		stat_time = fileStat.st_mtime;
	else
		stat_time = fileStat.st_atime;
	second = ctime(&stat_time);
	info->seconds = stat_time;
	fill_date_info(info, ret, second);
}

void				get_minor_and_major(t_info *info, struct stat fileStat, t_args *args)
{
	int				dev;

	dev = fileStat.st_rdev;
	info->major = major(dev);
	if (check_num_length(info->major) > args->biggest_major)
		args->biggest_major = check_num_length(info->major);
	info->minor = minor(dev);
	if (check_num_length(info->minor) > args->biggest_minor)
		args->biggest_minor = check_num_length(info->minor);
}

void				fill_file_infos(t_info *info, t_args *args, struct stat fileStat)
{
	info->printing = 1;
	if (is_contained_in("l", args->arg, 0) > 0 || is_contained_in("g", args->arg
	, 0) > 0 || is_contained_in("o", args->arg, 0) > 0)
	{
		get_minor_and_major(info, fileStat, args);
		info->inodes = fileStat.st_nlink;
		if (check_num_length(info->inodes) > args->biggest_inodes)
			args->biggest_inodes = check_num_length(info->inodes);
		fill_file_rights(info, fileStat);
		fill_user_group_info(info, fileStat, args);
	}
	info->access = fileStat.st_atime;
	get_date_info(info, fileStat, args);
	info->size = fileStat.st_size;
	info->blk_size = fileStat.st_blocks;
	if (check_num_length(info->size) > args->biggest_size && info->is_error < 1)
	{
		args->biggest_size = check_num_length(info->size);
	}
	info->type = S_ISDIR(fileStat.st_mode);
	if (S_ISLNK(fileStat.st_mode) == 1)
		info->type = 2;
	if (info->type == 1 && args->dir_nb++ >= 0)
		info->printing = -1;
}
