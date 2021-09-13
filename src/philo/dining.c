/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 10:28:34 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/13 13:02:50 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philo.h"

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

static inline int
	check_the_status(const t_table *const table)
{
	const uint64_t	standard = table->timestamp;
	const t_option	option = table->option;
	const uint64_t	time_to_die = option.time_to_die;
	int32_t			i;

	i = -1;
	while (++i < option.number_of_philos)
	{
		if ((punch_clock() - table->seats[i].timestamp) > time_to_die)
		{
			printf("%llu"MS"%d"DIED, (punch_clock() - standard) / 1000, i + 1);
			return (i);
		}
	}
	return (option.number_of_philos);
}

static inline void
	check_the_voucher(const t_table *const table)
{
	const t_option	option = table->option;
	int32_t			no_voucher;
	int32_t			i;

	while (check_the_status(table) == table->option.number_of_philos)
	{
		usleep(512);
		i = -1;
		no_voucher = 0;
		while (++i < option.number_of_philos)
			if (table->seats[i].voucher == 0)
				++no_voucher;
		if (no_voucher == option.number_of_philos)
			break ;
	}
}

static void
	set_the_table(t_table *const table, int i)
{
	t_seat *const	seats = table->seats;

	while (++i <= table->option.number_of_philos)
	{
		seats[i - 1].table = table;
		seats[i - 1].number.prev = i - 1;
		seats[i - 1].number.here = i;
		seats[i - 1].number.next = i + 1;
		seats[i - 1].voucher = table->option.number_of_times_to_eat;
		seats[i - 1].right.authorized_key = seats[i - 1].number.here;
		if (i == table->option.number_of_philos)
		{
			seats[i - 1].left = &seats[0].right;
			seats[i - 1].number.next = 1;
			if (table->option.number_of_philos & 1)
				seats[i - 1].right.authorized_key = i;
		}
		else
			seats[i - 1].left = &seats[i].right;
		if (!(i & 1))
			seats[i - 1].right.authorized_key = seats[i - 1].number.prev;
	}
	seats[0].number.prev = table->option.number_of_philos;
}

int
	dining(t_table *const table, t_thread *const thread)
{
	int	i;

	i = -1;
	set_the_table(table, 0);
	table->timestamp = punch_clock();
	if (table->timestamp != UINT64_MAX)
	{
		while (++i < table->option.number_of_philos)
		{
			pthread_mutex_init(&table->seats[i].right.fork, NULL);
			table->seats[i].timestamp = table->timestamp;
			if (pthread_create(&thread[i], NULL, routine, &table->seats[i])
				&& write(2, ERR_PTHREAD, sizeof(ERR_PTHREAD) - 1))
				return (0);
			pthread_detach(thread[i]);
		}
		if (table->option.number_of_times_to_eat != UNLIMIT)
			check_the_voucher(table);
		else
			while (check_the_status(table) == table->option.number_of_philos)
				usleep(512);
	}
	return (0);
}
#endif
