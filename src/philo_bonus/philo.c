/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:31:27 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/13 12:51:51 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

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
	after_meal(t_table *const table, const uint64_t standard, \
							const t_option option, const int32_t number)
{
	sem_post(table->right);
	sem_post(table->left);
	printf("%llu"MS"%d"SLEEP, (punch_clock() - standard) / 1000, number);
	set_alarm(punch_clock() + option.time_to_sleep, option.offset);
	if (table->voucher == 0)
		return ;
	printf("%llu"MS"%d"THINK, (punch_clock() - standard) / 1000, number);
}

static inline void
	before_meal(t_table *const table, const uint64_t standard, \
							const t_option option, const int32_t number)
{
	sem_wait(table->right);
	printf("%llu"MS"%d"RIGHT, (punch_clock() - standard) / 1000, number);
	sem_wait(table->left);
	printf("%llu"MS"%d"LEFT, (punch_clock() - standard) / 1000, number);
	printf("%llu"MS"%d"EAT, (punch_clock() - standard) / 1000, number);
	set_alarm(punch_clock() + option.time_to_eat, option.offset);
}

void
	*routine(void *arg)
{
	t_table *const		table = (t_table *)arg;
	const uint64_t		standard = table->timestamp;

	table->timestamp = punch_clock();
	if (table->voucher == UNLIMIT)
	{
		while (UNLIMIT)
		{
			before_meal(table, standard, table->option, table->number);
			table->timestamp = punch_clock();
			after_meal(table, standard, table->option, table->number);
		}
	}
	else
	{
		while (table->voucher)
		{
			before_meal(table, standard, table->option, table->number);
			table->timestamp = punch_clock();
			--table->voucher;
			after_meal(table, standard, table->option, table->number);
		}
	}
	return (NULL);
}
#endif
