/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:13:20 by amakela           #+#    #+#             */
/*   Updated: 2023/11/16 13:19:02 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*new;
	void	*temp;

	if (!f || !del)
		return (NULL);
	list = NULL;
	while (lst)
	{
		temp = (*f)(lst->content);
		new = ft_lstnew(temp);
		if (new == NULL)
		{
			ft_lstclear(&list, del);
			free(temp);
			return (NULL);
		}
		ft_lstadd_back(&list, new);
		lst = lst->next;
	}
	return (list);
}
