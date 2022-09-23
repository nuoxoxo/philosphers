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

static void	cout(const char *s);

void	ft_mutex_destroyer(t_philo *philo, t_table *table)
{
	int				i;

	i = -1;
	while (++i < table->total_philo)
	{
		pthread_mutex_destroy(& philo->chops[i]);
	}
	pthread_mutex_destroy(& table->mtx_death);
	pthread_mutex_destroy(& table->mtx_print);
	pthread_mutex_destroy(& table->mtx_meals);
	pthread_mutex_destroy(& table->mtx_close);
}

/*
	table mtx to destroy:

	pthread_mutex_t		mtx_death; // set Death flag
	pthread_mutex_t		mtx_print;
	pthread_mutex_t		mtx_meals; // count meals
	pthread_mutex_t		mtx_close; // set Close flag

*/

void	ft_clean_exit(t_philo *philo, t_table *table, int exit_granted)
{
	if (philo)
	{
		if (philo->chops)
			ft_cleaner(philo->chops);
		ft_cleaner(philo);
	}
	if (table)
	{
		ft_cleaner(table);
	}
	if (exit_granted)
	{
		exit (1);
	}
}

void	ft_cleaner(void *tmp)
{
	if (tmp)
		free(tmp);
	tmp = NULL;
}

void	ft_usage_exit(void)
{
	cout("\nUsage: ./philo n1 n2 n3 n4 [n5] \n\n");
	cout("n1: number of philosophers \n");
	cout("n2: time to die (in ms)\n");
	cout("n3: time to eat (in ms)\n");
	cout("n4: time to sleep (in ms)\n");
	cout("n5: (optional) number of meals each one must eat \n");
	cout("\n(number of args required: 5 or 6) \n");
	exit (0);
}

static void	cout(const char *s)
{
	write(1, s, len(s));
}
