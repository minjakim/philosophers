/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:31:27 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/12 22:15:24 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

#if BONUS == 0
static inline uint64_t
	punch_clock(void)
{
	t_timeval	tick;
	uint64_t	buffer;

	if (gettimeofday(&tick, NULL) == ERROR)
		return (UINT64_MAX);
	buffer = (tick.tv_sec << 10) - (tick.tv_sec << 4) - (tick.tv_sec << 3);
	return ((buffer << 10) - (buffer << 4) - (buffer << 3) + (tick.tv_usec));
}

static inline void
	set_alarm(const uint64_t until, const useconds_t offset)
{
	while (until >= punch_clock())
		usleep(offset);
}

static inline void
	after_meal(t_seat *const seat, const uint64_t standard, \
							const t_option option, const t_number number)
{
	seat->right.authorized_key = number.prev;
	pthread_mutex_unlock(&seat->right.fork);
	seat->left->authorized_key = number.next;
	pthread_mutex_unlock(&seat->left->fork);
	printf("%llu"MS"%d"SLEEP, (punch_clock() - standard) / 1000, number.here);
	set_alarm(punch_clock() + option.time_to_sleep, option.offset);
	printf("%llu"MS"%d"THINK, (punch_clock() - standard) / 1000, number.here);
}

static inline void
	before_meal(t_seat *const seat, const uint64_t standard, \
							const t_option option, const t_number number)
{
	while (number.here != seat->right.authorized_key)
		usleep(option.offset);
	pthread_mutex_lock(&seat->right.fork);
	printf("%llu"MS"%d"RIGHT, (punch_clock() - standard) / 1000, number.here);
	while (number.here != seat->left->authorized_key)
		usleep(option.offset);
	pthread_mutex_lock(&seat->left->fork);
	printf("%llu"MS"%d"LEFT, (punch_clock() - standard) / 1000, number.here);
	printf("%llu"MS"%d"EAT, (punch_clock() - standard) / 1000, number.here);
	set_alarm(punch_clock() + option.time_to_eat, option.offset);
}

void
	*routine(void *arg)
{
	t_seat *const		seat = (t_seat *)arg;
	const uint64_t		standard = seat->table->timestamp;
	const t_option		option = seat->table->option;
	const t_number		number = seat->number;

	if (seat->voucher == UNLIMIT)
	{
		while (UNLIMIT)
		{
			before_meal(seat, standard, option, number);
			seat->timestamp = punch_clock();
			after_meal(seat, standard, option, number);
		}
	}
	else
	{
		while (seat->voucher)
		{
			before_meal(seat, standard, option, number);
			seat->timestamp = punch_clock();
			--seat->voucher;
			after_meal(seat, standard, option, number);
		}
	}
	return (NULL);
}
#endif
