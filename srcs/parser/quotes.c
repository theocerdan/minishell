#include "../includes/minishell.h"

int		has_two_type_quotes(char *str)
{
	int		i;
	int		sql_qts;
	int		dbl_qts;

	i = 0;
	sql_qts = 0;
	dbl_qts = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			sql_qts++;
		else if (str[i] == '\"')
			dbl_qts++;
		i++;
	}
	if (sql_qts != 0 && dbl_qts != 0 && sql_qts % 2 == 0 && dbl_qts % 2 == 0)
		return (1);
	return (0);
}

char	*resolve_quote_issue(char *str)
{
	char	*result;

	result = str;
	do
	{
		result = operate_quotes(result);
	} while (still_has_quote(result));
	return (result);
}

char	*resolve_special_case_quotes(char *str)
{
	char	*result;

	result = str;
	do
	{
		result = special_case_quotes(result);
	} while (has_two_type_quotes(result));
	return (result);
}

char    *check_if_quotes(char *each_cmd)
{
	int     i;
	char    *str;

	i = 0;
	str = each_cmd;
	while (str[i])
	{
		if (quote_hole(str, str[i]))
		{
			printf("Error : need a quote to finish the line.\n");
			exit(0);
		}
		else if (is_between_quotes(str, i, str[i]))
			str = resolve_quote_issue(str);
		else if (has_two_type_quotes(str))
		{
			str = resolve_special_case_quotes(str);
			break ;
		}
		i++;
	}
	return (str);
}
