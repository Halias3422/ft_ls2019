/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_colors.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/12 07:50:15 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/19 09:03:00 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void		add_colors(t_info *info, struct stat filestat)
{
	info->color = "\033[0m";
	if (filestat.st_mode & S_IXUSR)
		info->color = "\033[0;31m";
	if (filestat.st_mode & S_IFDIR)
		info->color = "\033[1;36m";
	if (filestat.st_mode & S_IFREG && filestat.st_mode & S_IFCHR)
		info->color = "\033[0;35m";
	if (filestat.st_mode & S_IXGRP && filestat.st_mode & 02000)
		info->color = "\033[0;30;46m";
	if (filestat.st_mode & S_IXUSR && filestat.st_mode & 04000)
		info->color = "\033[0;30;41m";
}
