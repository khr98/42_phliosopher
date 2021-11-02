#include "philo_bonus.h"

int	ft_atoi(const char *str)
{
	int	num;
	int	minus;

	num = 0;
	minus = 1;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		num = (num * 10) + *str - '0';
		str++;
	}
	return (num * minus);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ('0' > str[i] || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}
