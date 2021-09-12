/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:31:27 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/13 07:29:14 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

#if BONUS == 1
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
	after_meal(t_seat *const seat, const uint64_t standard, \
							const t_option option, const int32_t number)
{
	sem_post(seat->table->forks);
	printf("%llu"MS"%d"SLEEP, (punch_clock() - standard) / 1000, number);
	set_alarm(punch_clock() + option.time_to_sleep, option.offset);
	printf("%llu"MS"%d"THINK, (punch_clock() - standard) / 1000, number);
}

static inline void
	before_meal(t_seat *const seat, const uint64_t standard, \
							const t_option option, const int32_t number)
{
	sem_wait(seat->table->forks);
	printf("%llu"MS"%d"FORKS, (punch_clock() - standard) / 1000, number);
	printf("%llu"MS"%d"EAT, (punch_clock() - standard) / 1000, number);
	set_alarm(punch_clock() + option.time_to_eat, option.offset);
}

void
	*routine(void *arg)
{
	t_seat *const		seat = (t_seat *)arg;
	const uint64_t		standard = seat->table->timestamp;
	const t_option		option = seat->table->option;
	const int32_t		number = seat->number;

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
