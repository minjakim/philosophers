/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:31:27 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/11 10:32:22 by minjakim         ###   ########.fr       */
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
	set_alarm(const uint64_t until, const useconds_t useconds)
{
	while (until >= punch_clock())
		usleep(useconds);
}

static inline u_int64_t
	lap_time(const uint64_t timestamp)
{
	return ((punch_clock() - timestamp));
}

static inline uint32_t
	sleeping(const t_option *const option)
{
	const uint64_t	until = punch_clock() + option->time_to_sleep;

	while (until >= punch_clock())
		usleep(option->offset);
	return (1);
}

static inline uint32_t
	eating(const t_option *const option)
{
	const uint64_t	until = punch_clock() + option->time_to_eat;

	while (until >= punch_clock())
		usleep(option->offset);
	return (1);
}

void
	*routine(void *arg)
{
	t_seat *const		seat = (t_seat *)arg;
	const uint64_t		timestamp = seat->table->board.timestamp;
	const t_option		option = seat->table->option;
	const uint32_t		number = seat->number;
	const uint32_t		next = seat->next;
	uint64_t			start;
	uint64_t			check;

	start = punch_clock();
	while (1)
	{
		while (number ^ seat->right.authorized_key)
			usleep(option.offset);
		pthread_mutex_lock(&seat->right.fork);
		printf("%llu ms %d"HAS_TAKEN_A_RIGHT_FORK, lap_time(timestamp), number);
		while (number ^ seat->left->authorized_key)
			usleep(option.offset);
		pthread_mutex_lock(&seat->left->fork);
		printf("%llu ms %d"HAS_TAKEN_A_LEFT__FORK, lap_time(timestamp), number);
		printf("%llu ms %d"IS_EATING, lap_time(timestamp), number);
		set_alarm(punch_clock() + option.time_to_eat, option.offset);
		if ((check = punch_clock() - start) > option.time_to_die)
		{
			seat->table->board.time_of_death = punch_clock();
			seat->table->board.dead = number;
			break ;
		}
		else
			printf("%llu ms %d"IS_ALIVED"(%llu)\n", lap_time(timestamp), number, check);
		start = punch_clock();
		seat->right.authorized_key = next;
		pthread_mutex_unlock(&seat->right.fork);
		seat->left->authorized_key ^= next;
		pthread_mutex_unlock(&seat->left->fork);
		printf("%llu ms %d"IS_SLEEPING, lap_time(timestamp), number);
		set_alarm(punch_clock() + option.time_to_sleep, option.offset);
		printf("%llu ms %d"IS_THINKING, lap_time(timestamp), number);
		if ((check = punch_clock() - start) > option.time_to_die)
		{
			seat->table->board.time_of_death = punch_clock();
			seat->table->board.dead = number;
			break ;
		}
		start = punch_clock();
	};
	return (NULL);
}
