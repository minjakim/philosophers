/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:33:07 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/11 05:43:57 by minjakim         ###   ########.fr       */
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

static inline uint32_t
	punch_alarm(const uint64_t until, const useconds_t useconds)
{
	while (until >= punch_clock())
		usleep(useconds);
	return (punch_clock() - until);
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
	uint64_t			start;
	uint64_t			check;

	start = punch_clock();
	while (1)
	{
		while (seat->certificate ^ seat->right.authorization)
			usleep(option.offset);
		pthread_mutex_lock(&seat->right.fork);
		printf("%llu ms %d"HAS_TAKEN_A_RIGHT_FORK, lap_time(timestamp), number);
		while (seat->certificate ^ seat->left->authorization)
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
		seat->right.authorization ^= 1;
		pthread_mutex_unlock(&seat->right.fork);
		seat->left->authorization ^= 1;
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

int
	initialize(int argc, char **argv, t_table *table)
{
	table->option.offset = 32;
	table->option.number_of_philos = 4;
	table->option.time_to_die = 410 * 1000;
	table->option.time_to_eat = 200 * 1000;
	table->option.time_to_sleep = 200 * 1000;
	table->seats = malloc(sizeof(t_seat) * table->option.number_of_philos);
	//if (table->option.number_of_philos & 1)


	return (0);
}

int
	main(int argc, char **argv)
{
	t_thread	*thread;
	t_table		table;

	initialize(argc, argv, &table);
	thread = malloc(sizeof(t_thread) * table.option.number_of_philos);
	for (int i = 0; i < table.option.number_of_philos; i++)
	{
		table.seats[i].table = &table;
		table.seats[i].number = i + 1;
		table.seats[i].right.authorization = 0;
		if (i == table.option.number_of_philos - 1)
		{
			table.seats[i].left = &table.seats[0].right;
			if (table.option.number_of_philos & 1)
				table.seats[i].certificate = table.option.number_of_philos;
			else
				table.seats[i].certificate = (i & 1);
		}
		else
		{
			table.seats[i].left = &table.seats[i + 1].right;
			table.seats[i].certificate = (i & 1);
		}
		//printf("phlio: %d key: %d\n", table.seats[i].number, table.seats[i].key);
		pthread_mutex_init(&table.seats[i].right.fork, NULL);
		if (i == 0)
			table.board.timestamp = punch_clock();
		if (pthread_create(&thread[i], NULL, routine, &table.seats[i]))
			return (1);
		pthread_detach(thread[i]);
	}
	while (LOOP)
	{
		if (table.board.dead)
		{
			printf("%llu ms %d is  died(%llu)\n", (table.board.time_of_death - table.board.timestamp) / 1000, table.board.dead, punch_clock() - table.board.time_of_death);
			break ;
		}
		else
			usleep(512);
	}
	return (0);
}
