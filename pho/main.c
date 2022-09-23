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

static void	sims_begin(t_philo *philo, t_table *table, pthread_t *threads);
static void	sims_clean(t_philo *philo, t_table *table, pthread_t *threads);
static void	join_threads(t_philo *philo, t_table *table, pthread_t *threads);

int	main(const int c, const char **v)
{
	pthread_t		*threads;
	t_table			*table;
	t_philo			*philo;

	check_params(c, v);
	table = malloc(sizeof(t_table));
	if (! table)
		ft_clean_exit(NULL, NULL, 1);
	philo = malloc(sizeof(t_philo) * ft_atoi(v[1]));
	if (! philo)
		ft_clean_exit(NULL, table, 1);
	threads = malloc (sizeof(pthread_t) * ft_atoi(v[1]));
	if (! threads)
		ft_clean_exit(philo, table, 1);
	if (! parse_table(table, c, v))
		ft_clean_exit(philo, table, 1);
	if (! parse_philo(philo, table))
		ft_clean_exit(philo, table, 1);
	sims_begin(philo, table, threads);
	join_threads(philo, table, threads);
	sims_clean(philo, table, threads);
	return (0);
}

/*		simulation		*/

static void	join_threads(t_philo *philo, t_table *table, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < table->total_philo)
	{
		if (! pthread_join(threads[i], NULL))
		{
			continue ;
		}
		ft_cleaner(threads);
		ft_mutex_destroyer (philo, table);
		ft_clean_exit(philo, table, 1);
	}
}

static void	sims_begin(t_philo *philo, t_table *table, pthread_t *threads)
{
	init_mutexes(philo, table);
	init_routine(philo, table, threads);
	main_thread(philo, table);
}

static void	sims_clean(t_philo *philo, t_table *table, pthread_t *threads)
{
	ft_mutex_destroyer(philo, table);
	ft_clean_exit(philo, table, 0);
	ft_cleaner(threads);
}
