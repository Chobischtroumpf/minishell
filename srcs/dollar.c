/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:12:57 by nathan            #+#    #+#             */
/*   Updated: 2020/12/19 13:39:37 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void skip_spaces(char *str)
{
	char *trimmed;
	char *untrimmed;
	int prev_space;
	// printf("before trim |%s|\n", str);
	trimmed = str;
	untrimmed = str;
	prev_space = 0;
	while (*untrimmed)
	{
		if (ft_isspace(*untrimmed))
		{
			if (!prev_space)
			{
				*trimmed++ = ' ';
				prev_space = 1;
			}
		}
		else
		{
			*trimmed++ = *untrimmed;
			prev_space = 0; 
		}
		++untrimmed;
	}
	*trimmed = '\0';
	// printf("after  trim |%s|\n", str);
}

// int is_empty(const char *s) {
//   while (*s != '\0') {
//     if (!ft_isspace((unsigned char)*s))
//       return 0;
//     s++;
//   }
//   return 1;
// }

void	add_str_to_buffer(char *buffer, char *str, int *j, int quote)
{
	int flag;

	if (!quote)
		skip_spaces(str);
	if (ft_is_split(str))
		flag = 1;
	else
		flag = 0;
	if (flag && !quote)
		buffer[++*j] = 3;
	while(*str)
	{
		buffer[++*j] = *str++;
	}
}

int 	check_part_cases(char *token, char *buffer, int *j, int quote)
{
	// printf("token |%s|\n", token);
	if (!ft_strncmp(token, "$$", 2))
	{
		add_str_to_buffer(buffer, "TEMP_PID", j, quote);
		return (1);
	}
	else if (!ft_strncmp(token, "$?", 2))
	{
		add_str_to_buffer(buffer, ft_itoa(get_minishell()->excode), j, quote);
		return (1);
	}
	else if (token[0] == '$' && (ft_haschr("\\",token[1]) || !token[1]))
	{
		buffer[++*j] = '$';
		return 1;
	}
	return (0);
		
}

int		check_env(char *token, char *buffer, int *j, int quote)
{
	// printf("IN CHECK ENV\n");
	int len;
	char *value;
	len = ft_strlen(token);
	while (len--)
	{
		if ((value = ft_find_by_key2(ft_substr(token,1 , len) )) && (!ft_haschr("_", token[len + 1]) || !token[len + 1]))
		{	
			add_str_to_buffer(buffer, value, j, quote);
			// printf("var value %s\nlen %d\n", value, len);
			return (len);
		}
	}
	

	return 0;
}

int 	replace_false_dollar(char *token, char *buffer, int *j)
{
	int i;
	int count;
	
	i = 1;
	count =0;
	while (token[i] && !ft_haschr("|$", token[i]))
	{
		i++;
		count++;
	}
	if (token[i] != '$' && token[i]!= '|')
		while (token[i])
			buffer[++*j] = token[i++];
	return (count);
}



int		process_dollar(char *token, char *buffer, int *j, int quote)
{	
	int		ret;
	char	*token2;
	
	ret = 0;
	if (quote)
		token2 = ft_substr(token, 0, (int)(ft_strchr(token, '"') - token));// gets rid of last "
	
	else
		token2 = ft_strdup(token);
	
	if ((ret = check_part_cases(token2, buffer, j, quote)))// handles $$ and $?
		return(free_str_ret(token2, ret));
	else if ((ret = check_env(token2, buffer, j, quote))) // is it in env ?
		return(free_str_ret(token2, ret));
	else if ((ret = replace_false_dollar(token2, buffer, j))) // if not in env, get rid off the false key
		return(free_str_ret(token2, ret));
	free(token2);
	return (ret);
}
