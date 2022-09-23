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

static void	check_params_digit_and_limit(const int c, const char **v);
static int	check_params_digit(const char *s);
static int	check_params_limit(const char *s);

void	check_params(const int c, const char **v)
{
	int			v1;
	int			v2;
	int			v3;
	int			v4;
	int			v5;

	if (c < 5 || c > 6)
		ft_usage_exit();
	check_params_digit_and_limit(c, v);
	v1 = ft_atoi(v[1]);
	v2 = ft_atoi(v[2]);
	v3 = ft_atoi(v[3]);
	v4 = ft_atoi(v[4]);
	if (c == 6)
	{
		v5 = ft_atoi(v[5]);
	}
	else
	{
		v5 = 1e9;
	}
	if (! v5)
		exit (0);
	if (v5 < 0 || v1 < 1 || v2 < 1 || v3 < 1 || v4 < 1)
		ft_usage_exit();
}

///		static

static void	check_params_digit_and_limit(const int c, const char **v)
{
	int				i;

	i = 0;
	while (++i < c)
	{
		if (check_params_digit(v[i]) || check_params_limit(v[i]))
			ft_usage_exit();
	}
}

static int	check_params_digit(const char *s)
{
	int				i;

	i = -1;
	if (s[i + 1] == '-' || s[i + 1] == '+')
		i++;
	while (s[++i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
	}
	return (0);
}

static int	check_params_limit(const char *s)
{
	long long			ll;

	ll = ft_atoll(s);
	if (ll < -2147483648 || ll > 2147483647)
		return (1);
	return (0);
}
