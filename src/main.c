/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjakim <minjakim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 13:33:07 by minjakim          #+#    #+#             */
/*   Updated: 2021/09/11 10:47:37 by minjakim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int
	initialize(t_table *table, t_thread *thread, int i)
{
	table->seats = malloc(sizeof(t_seat) * table->option.number_of_philos);
	if (table->seats == NULL && write(2, ERR_MALLOC, sizeof(ERR_MALLOC) - 1))
		return (FAIL);
	thread = malloc(sizeof(t_thread) * table->option.number_of_philos);
	if (thread == NULL && write(2, ERR_MALLOC, sizeof(ERR_MALLOC) - 1))
		return (FAIL);
	table->option.offset = 32;
	table->option.time_to_die *= 1000;
	table->option.time_to_eat *= 1000;
	table->option.time_to_sleep *= 1000;
	while (--i)
	{
		table->seats[i].table = table;
		table->seats[i].number = i + 1;
		table->seats[i].right.authorized_key = i + 1;
		if (!(table->seats[i].number & 1))
			table->seats[i].right.authorized_key -= 1;
		if (i == table->option.number_of_philos - 1)
			table->seats[i].left = &table->seats[0].right;
		else
			table->seats[i].left = &table->seats[i + 1].right;
	}
	return (SUCCESS);
}

static inline unsigned char
	convert(unsigned char *a, const char *str)
{
	return (*a = *str - '0');
}

static int
	checktoi(const char *str)
{
	int				digit;
	unsigned char	a;
	long			i;

	while (*str == '0')
		if (*(++str) == '\0')
			return (0);
	i = 0;
	digit = 0;
	while (*str && (convert(&a, str) < 10 && ++digit < 11))
		(i = (i << 1) + (i << 3) + a) && str++;
	if (*str && write(2, ERR_FORMAT, sizeof(ERR_FORMAT)))
		return (ERROR);
	if (((10 < digit) || (INT32_MAX < i))
		&& write(2, ERR_RANGE, sizeof(ERR_RANGE)))
		return (ERROR);
	return (i);
}

static int
	parse_args(int argc, char **const argv, t_table *table)
{
	table->option.number_of_times_to_eat = 0;
	while (--argc > -1)
	{
		if (*argv[argc] == '\0' && write(2, ERR_EMPTY, sizeof(ERR_EMPTY) - 1))
			return (FAIL);
		table->option.options[argc] = checktoi(argv[argc]);
		if (table->option.options[argc] == ERROR)
			return (FAIL);
	}
	return (SUCCESS);
}

int
	main(int argc, char **argv)
{
	t_thread	**thread;
	t_table		table;
	int			i;

	if (--argc < 4 || 5 < argc || !parse_args(argc, argv, &table)
		|| !initialize(&table, *thread, table.option.number_of_philos))
		return (0);
	i = 0;
	table.board.timestamp = get_time();
	while (++i < table.option.number_of_philos)
	{
		pthread_mutex_init(&table.seats[i].right.fork, NULL);
		if (pthread_create(thread[i], NULL, routine, &table.seats[i])
			&& write(2, ERR_PTHREAD, sizeof(ERR_PTHREAD) - 1))
			return (0);
		pthread_detach(*thread[i]);
	}
	while (LOOP)
	{
		if (table.board.dead)
		{
			printf("%llu ms %d is  died(%llu)\n", (table.board.time_of_death - table.board.timestamp) / 1000, table.board.dead, get_time() - table.board.time_of_death);
			break ;
		}
		else
			usleep(512);
	}
	return (0);
}
