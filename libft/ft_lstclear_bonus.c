/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:36:02 by amakela           #+#    #+#             */
/*   Updated: 2023/11/16 12:27:47 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*prev;

	if (!lst || !del)
		return ;
	current = *lst;
	while (current != NULL)
	{
		(*del)(current->content);
		prev = current;
		current = current->next;
		free(prev);
	}
	*lst = NULL;
}
