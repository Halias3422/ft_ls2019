/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: vde-sain <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/02/12 08:53:19 by vde-sain     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/27 13:37:06 by vde-sain    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_ls.h"

void		free_list(t_info *lst, t_args *args)
{
	t_info	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		if (lst->is_error == 1)
			free(lst->file);
		free(lst->date);
		free(lst);
		lst = tmp;
	}
	free(args->arg);
	lst = NULL;
}
