/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 12:49:34 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/11 14:58:53 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef BONUS
#  define BONUS	0
# endif

# include "resource.h"
# include "types.h"

void		*routine(void *arg);
int			dining(t_table *const table, t_thread *const thread, int i);
void		set_the_table(t_table *const table, int number);
uint64_t	get_time(void);

#endif
