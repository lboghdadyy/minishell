#include "../../minishell.h"

static	int	ft_intlen(int i)
{
	int	len;

	len = 0;
	while (i > 0)
	{
		len++;
		i /= 10;
	}
	return (len);
}

static	void	ft_fill_it(char *str, int n, int sign)
{
	int	i;
	int	j;

	i = 0;
	if (sign == -1)
		j = ft_intlen(n) + 1;
	else
		j = ft_intlen(n);
	str[j] = '\0';
	j--;
	while (n >= 1)
	{
		str[j] = (n % 10) + 48;
		j--;
		n = n / 10;
	}
	if (sign == -1)
		str[j] = '-';
}

char	*ft_itoa(int n)
{
	char	*asc;
	int		sign;

	if (n <= -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	sign = 1;
	if (n < 0)
	{
		n *= -1;
		sign = -1;
	}
	if (sign == -1)
		asc = malloc(ft_intlen(n) + 2);
	else
		asc = malloc(ft_intlen(n) + 1);
	if (!asc)
		return (NULL);
	ft_fill_it(asc, n, sign);
	return (asc);
}