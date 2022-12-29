/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2022/11/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_cmds	***split_list(t_cmds* list, char* delimiter) {
	// Count the number of delimiters in the list
	int delimiter_count = 0;
	t_cmds* current = list;
	while (current != NULL) {
		if (strcmp(current->cmd, delimiter) == 0) {
			delimiter_count++;
		}
		current = current->next;
	}

	// Allocate an array to hold the sub lists
	int sub_list_count = delimiter_count + 1;
	t_cmds*** sub_lists = malloc(sizeof(t_cmds**) * sub_list_count);

	// Iterate through the list and create the sub lists
	int current_sub_list = 0;
	int current_sub_list_size = 0;
	current = list;
	while (current != NULL) {
		if (strcmp(current->cmd, delimiter) == 0) {
			// Allocate memory for the current sub list and add it to the array
			sub_lists[current_sub_list] = malloc(sizeof(t_cmds*) * (current_sub_list_size + 1));
			current_sub_list++;
			current_sub_list_size = 0;
		} else {
			// Add the current element to the current sub list
			sub_lists[current_sub_list][current_sub_list_size] = current;
			current_sub_list_size++;
		}
		current = current->next;
	}

	// Add a NULL element to the end of each sub list to indicate the end
	int i = 0;
	while (i < sub_list_count) {
		sub_lists[i][current_sub_list_size] = NULL;
		i++;
	}
	return sub_lists;
}
