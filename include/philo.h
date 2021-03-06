/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 12:49:34 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/13 13:00:39 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "resource.h"
# include "types.h"

void					*routine(void *arg);
int						dining(t_table *const table, t_thread *const thread);

#endif
