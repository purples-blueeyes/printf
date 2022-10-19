#include "main.h"

/**
 * _printf - prints and input into the standard output
 * @format: format string.
 *
 * Return: bytes to be printed.
 */

int _printf(const char *format, ...)
{
	int sum = 0;
	va_list list;
	char *k, *start;

	params_t params = PARAMS_INIT;

	va_start(list, format);

	/* checking for NULL char */
	if (!format || (format[0] == '%' && !format[1]))
		return (-1);
	if (format[0] == '%' && format[1] == ' ' && !format[2])
		return (-1);
	for (k = (char *)format; *k; k++)
	{
		init_params(&params, list);

		/*checking for the % specifier*/
		if (*k != '%')
		{
			sum += _putchar(*k);
			continue;
		}

		start = k;
			k++;
			/* while char at k is flag character */
			while (get_flag(k, &params))
			{
				k++;
			}
			k = get_width(k, &params, list);
			k = get_precision(k, &params, list);
			if (get_modifier(k, &params))
				k++;
			if (!get_specifier(k))
				sum += print_from_to(start, k,
						params.l_modifier || params.h_modifier ? k - 1 : 0);
			else
				sum += get_print_func(k, list, &params);
	}
	_putchar(BUF_FLUSH);
	va_end(list);
	return (sum);
}

