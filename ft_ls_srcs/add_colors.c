/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   add_colors.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/03/12 07:50:15 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/03/12 15:41:38 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void		add_colors(t_info *info, struct stat fileStat)
{
	info->color = "\033[0m";
	if (fileStat.st_mode & S_IXUSR)
		info->color = "\033[0;31m";
	if (fileStat.st_mode & S_IFDIR)
		info->color = "\033[1;36m";
	if (fileStat.st_mode & S_IFREG && fileStat.st_mode & S_IFCHR)
		info->color = "\033[0;35m";
	if (fileStat.st_mode & S_IXGRP && fileStat.st_mode & 02000)
		info->color = "\033[0;30;46m";
	if (fileStat.st_mode & S_IXUSR && fileStat.st_mode & 04000)
		info->color = "\033[0;30;41m";
}
