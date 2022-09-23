/* ************************************************************************** */
/*                                                                            */
/*                                                        ...      :::::::    */
/*   _                                                  ...      :::    :::   */
/*                                                    ... ...         :::     */
/*   By: nuo <marvin@42.fr>                         ...  ...       :::        */
/*                                                ...........   :::           */
/*   Created: ____/__/__ __:__:__ by nuo               ...    :::             */
/*   Updated: ____/__/__ __:__:__ by nuo              ...   ::::::::.fi       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	parse_table_1(t_table *t, const int c, const char **v);
static int	parse_table_2(t_table *t, const int c, const char **v);

int	parse_table(t_table *table, const int c, const char **v)
{
	if (! parse_table_1(table, c, v))
		return (0);
	if (! parse_table_2(table, c, v))
		return (0);
	return (1);
}

int	parse_philo(t_philo *philo, t_table *table)
{
	pthread_mutex_t			*chops;
	int						i;

	chops = malloc (sizeof(pthread_mutex_t) * table->total_philo);
	if (! chops)
		return (0);
	i = -1;
	while (++i < table->total_philo)
	{
		philo[i].chops = chops;
		philo[i].table = table;
		philo[i].last_meal = ft_current_ms();
		philo[i].id = i + 1;
		philo[i].eaten = 0;
	}
	return (1);
}

//	helpers

static int	parse_table_1(t_table *table, const int c, const char **v)
{
	if (c < 5 || c > 6 || ! table)
		return (0);
	table->total_philo = ft_atoi(v[1]);
	table->time_to_die = ft_atoi(v[2]);
	table->time_to_eat = ft_atoi(v[3]);
	table->time_to_sleep = ft_atoi(v[4]);
	if (c == 6)
	{
		table->meals = ft_atoi(v[5]);
		return (1);
	}
	table->meals = -1;
	return (1);
}

static int	parse_table_2(t_table *table, const int c, const char **v)
{
	table->flag_of_death = 0;
	table->flag_of_close = 0;
	(void) c;
	(void) v;
	return (1);
}
