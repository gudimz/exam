
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct s_params
{
	int width;
	int prec;
	int count;
}		t_params;

void ft_putchar(char c, t_params *prm)
{
	write(1, &c, 1);
	prm->count += 1;
}

void ft_putstr(char *str, int len, t_params *prm)
{
	int i;
	i = 0;
	while(str[i] && len > 0)
	{
		ft_putchar(str[i], prm);
		i++;
		len--;
	}
}

int ft_strlen(char *str)
{
	int  len;

	len = 0;
	while(str[len] != '\0')
	{
		len++;
	}
	return (len);
}

char *ft_itoa_base(unsigned long nbr, char *ref, int base, t_params *prm)
{
	int size;
	char *str;
	unsigned long tmp;

	tmp = nbr;
	size = 0;

	if(nbr == 0 && prm->prec == 0)
		size = 0;
	else if(nbr == 0)
		size = 1;
	while(tmp > 0)
	{
		tmp /= base;
		size++;
	}
	if(!(str = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	str[size] = '\0';
	while(size--)
	{
		str[size] = ref[nbr % base];
		nbr /= base;
	}
	return (str);
}

void ft_print_s(char *str, t_params *prm)
{
	int len;

	len = ft_strlen(str);
	if(prm->prec != -1 && prm->prec < len)
		len = prm->prec;
	while(prm->width > len)
	{
		ft_putchar(' ', prm);
		prm->width--;
	}
	ft_putstr(str, len, prm);
}

void ft_print_x(unsigned long nbr, t_params *prm)
{
	char *str;
	int len;

	str = ft_itoa_base(nbr, "0123456789abcdef", 16, prm);
	len = ft_strlen(str);

	if(prm->prec > len)
		len = prm->prec;
	while(prm->width > len)
	{
		ft_putchar(' ', prm);
		prm->width--;
	}
	while(len > ft_strlen(str))
	{
		ft_putchar('0', prm);
		len--;
	}
	ft_putstr(str, ft_strlen(str), prm);
	free(str);
}

void ft_print_d(long nbr, t_params *prm)
{
	char *str;
	int len;
	int minus;

	minus = 0;
	if(nbr < 0)
	{
		minus = 1;
		nbr *= -1;
	}
	str = ft_itoa_base(nbr, "0123456789", 10, prm);
	len = ft_strlen(str);

	if(prm->prec > len)
		len = prm->prec;
	if(minus && prm->width > 0)
		prm->width --;
	while(prm->width > len)
	{
		ft_putchar(' ', prm);
		prm->width--;
	}
	if(minus)
		ft_putchar('-', prm);
	while(len > ft_strlen(str))
	{
		ft_putchar('0', prm);
		len--;
	}
	ft_putstr(str, ft_strlen(str), prm);
	free(str);
}

int ft_printf(const char *str, ...)
{
	int i;
	va_list arg;
	t_params prm;

	prm.count = 0;
	va_start(arg, str);
	i = 0;
	if(!str)
		return (-1);
	while(str[i])
	{
		if(str[i] == '%')
		{
			i++;
			prm.width = 0;
			prm.prec = -1;
			while(str[i] >= '0' && str[i] <= '9')
			{
				prm.width = prm.width * 10 + (str[i] - '0');
				i++;
			}
			if(str[i] == '.')
			{
				i++;
				prm.prec = 0;
				while(str[i] >= '0' && str[i] <= '9')
				{
				prm.prec = prm.prec * 10 + (str[i] - '0');
				i++;
				}
			}
			if(str[i] == 's')
				ft_print_s(va_arg(arg, char *), &prm);
			else if(str[i] == 'x')
				ft_print_x(va_arg(arg, unsigned int), &prm);
			else if(str[i] == 'd')
				ft_print_d(va_arg(arg, int), &prm);
		}
		else
			ft_putchar(str[i], &prm);
		i++;
	}
	va_end(arg);
	return (prm.count);
}
