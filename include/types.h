/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 12:49:06 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/11 05:44:35 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "resource.h"

typedef pthread_t		t_thread;
typedef	pthread_mutex_t	t_mutex;
typedef struct timeval	t_timeval;
typedef struct s_table	t_table;

typedef struct s_authorized
{
	uint32_t		key;
	struct s_key	*next;
}	t_authorized;

typedef struct s_lock
{
	uint32_t	authorization;
	t_mutex		fork;
}	t_lock;

typedef struct s_borad
{
	uint64_t	timestamp;
	uint64_t	time_of_death;
	uint32_t	dead;
}	t_board;

typedef struct s_option
{
	useconds_t	offset;
	uint32_t	number_of_philos;
	uint32_t	time_to_die;
	uint32_t	time_to_eat;
	uint32_t	time_to_sleep;
}	t_option;

typedef struct s_seat
{
	uint32_t	number;
	uint32_t	certificate;
	t_lock		right;
	t_lock		*left;
	t_table		*table;
}	t_seat;

struct s_table
{
	t_board		board;
	t_option	option;
	t_seat		*seats;
};

#endif
