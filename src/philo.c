/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:31:27 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/12 12:20:55 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static inline uint64_t
	punch_clock(void)
{
	t_timeval	tick;
	uint64_t	buffer;

	if (gettimeofday(&tick, NULL) == ERROR)
		exit(1);
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
	after_meal(t_seat *const seat, const uint64_t timestamp, \
							const t_option option, const t_number number)
{
	seat->right.authorized_key = number.prev;
	pthread_mutex_unlock(&seat->right.fork);
	seat->left->authorized_key = number.next;
	pthread_mutex_unlock(&seat->left->fork);
	printf("%llu"MS"%d"SLEEP, (punch_clock() - timestamp) / 1000, number.here);
	set_alarm(punch_clock() + option.time_to_sleep, option.offset);
	printf("%llu"MS"%d"THINK, (punch_clock() - timestamp) / 1000, number.here);
}

static inline void
	before_meal(t_seat *const seat, const uint64_t timestamp, \
							const t_option option, const t_number number)
{
	while (seat->voucher == 0)
		sleep(option.offset);
	while (number.here != seat->right.authorized_key)
		usleep(option.offset);
	pthread_mutex_lock(&seat->right.fork);
	printf("%llu"MS"%d"RIGHT, (punch_clock() - timestamp) / 1000, number.here);
	while (number.here != seat->left->authorized_key)
		usleep(option.offset);
	pthread_mutex_lock(&seat->left->fork);
	printf("%llu"MS"%d"LEFT, (punch_clock() - timestamp) / 1000, number.here);
	printf("%llu"MS"%d"EAT, (punch_clock() - timestamp) / 1000, number.here);
	set_alarm(punch_clock() + option.time_to_eat, option.offset);
}

void
	*routine(void *arg)
{
	t_seat *const		seat = (t_seat *)arg;
	const uint64_t		timestamp = seat->table->board.timestamp;
	const t_option		option = seat->table->option;
	const t_number		number = seat->number;

	seat->timecard = punch_clock();
	while (LOOP)
	{
		before_meal(seat, timestamp, option, number);
		--seat->voucher;
		//if ((punch_clock() - seat->timecard) > option.time_to_die)
		//	break ;
		seat->timecard = punch_clock();
		after_meal(seat, timestamp, option, number);
	}
	//seat->table->board.time_of_death = punch_clock();
	//seat->table->board.dead = number.here;
	return (NULL);
}
