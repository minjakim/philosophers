/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 12:49:06 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/13 17:51:53 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "resource.h"

typedef pthread_t		t_thread;
typedef struct timeval	t_timeval;
typedef struct s_table	t_table;

typedef struct s_option
{
	useconds_t	offset;
	union
	{
		struct
		{
			int32_t	number_of_philos;
			int32_t	time_to_die;
			int32_t	time_to_eat;
			int32_t	time_to_sleep;
			int32_t	number_of_times_to_eat;
		};
		uint32_t	options[5];
	};
}	t_option;

# if BONUS == 0
typedef pthread_mutex_t	t_mutex;

typedef struct s_number
{
	uint32_t	prev;
	uint32_t	here;
	uint32_t	next;
}	t_number;

typedef struct s_lock
{
	uint32_t	authorized_key;
	t_mutex		fork;
}	t_lock;

typedef struct s_seat
{
	uint64_t	timestamp;
	t_number	number;
	int32_t		voucher;
	t_lock		right;
	t_lock		*left;
	t_table		*table;
}	t_seat;

struct s_table
{
	uint64_t	timestamp;
	t_option	option;
	t_seat		*seats;
};
# else
typedef sem_t			t_sem;
typedef pid_t			t_seat;

struct s_table
{
	uint64_t	timestamp;
	uint32_t	number;
	int32_t		voucher;
	t_option	option;
	t_sem		*right;
	t_sem		*left;
	t_sem		*print;
	t_seat		*seats;
};
# endif

#endif
