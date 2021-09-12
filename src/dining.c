/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 10:28:34 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/12 12:21:21 by minjakim         ###   ########.fr       */
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

static inline int
	watching(t_table *const table)
{
	int	i;
	int	f;

	while (LOOP)
	{
		//if (table->board.dead)
		//{
		//	printf("%llu"MS"%d"DIED"(%llu)\n", (table->board.time_of_death - table->board.timestamp) / 1000, table->board.dead, punch_clock() - table->board.time_of_death);
		//	break ;
		//}
		if (table->option.number_of_times_to_eat != UNLIMIT)
		{
			i = -1;
			f = 0;
			while (++i < table->option.number_of_philos)
				if (table->seats[i].voucher == 0)
					++f;
			if (f == table->option.number_of_philos)
					return (0);
		}
		usleep(512);
		i = -1;
		while (++i < table->option.number_of_philos)
		{
			if (punch_clock() - table->seats[i].timecard > table->option.time_to_die)
			{
				printf("%llu"MS"%d"DIED, (punch_clock() - table->board.timestamp) / 1000, i + 1);
				return (0);
			}
		}
	}
	return (0);
}

static void
	check_the_option(t_table *const table)
{
	if (50 < table->option.number_of_philos)
		table->option.offset *= 8;
	if (500 < table->option.number_of_philos)
		table->option.offset *= 8;
	if (1000 < table->option.number_of_philos)
		table->option.offset *= 2;
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
	dining(t_table *const table, t_thread *const thread, int i)
{
	set_the_table(table, 0);
	check_the_option(table);
	table->board.timestamp = punch_clock();
	while (++i < table->option.number_of_philos)
	{
		pthread_mutex_init(&table->seats[i].right.fork, NULL);
		if (pthread_create(&thread[i], NULL, routine, &table->seats[i])
			&& write(2, ERR_PTHREAD, sizeof(ERR_PTHREAD) - 1))
			return (0);
		pthread_detach(thread[i]);
	}
	return (watching(table));
}
