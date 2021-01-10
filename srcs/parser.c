int	istoken(char c)
{
	return (c == '>' || c == '<' || 
		c == '|' || c == ';' c == "'" || c == '"');
}

int	count(char *s)
{
	int i;
	int count;
	
	i = 0;
	count = 0;
	while (s[i])
	{
		if ((!i && (s[i] != 32)) ||
			(i && (str[i - 1] == 32) && str[i] != 32) ||
			(i && istoken(s[i])))
			count++;
		i++;
		if (s[i] == '>' && s[i - 1] == '>')
			i++;
	}
}

char	**tokenize(char *s)
{
	int	count;
	char	**split;
	
	if (!s || !s[0])
		return (empty(array()));
	count
}

char	**parse(char *s)
{
	
}
