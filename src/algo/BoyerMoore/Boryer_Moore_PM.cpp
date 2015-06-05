
/*
The Boyer - Moore Algorithm
m = characters in pattern
n = characters in text
*/

std::unordered_map<char, int> last;			// last(c) is the index of the last (right-most) occurrence of c in Pattern

void function_to_get_last(const std::string& pattern)
{
	for (char chr = 'a'; chr <= 'z'; ++chr)
		last[chr] = -1;
	for (int i = 0; i < pattern.size(); ++i)
		last[pattern[i]] = i;
}

int if_text_in_pattern(const std::string& text, const std::string& pattern)		// return -1 if not found
{
	function_to_get_last(pattern);
	int m = pattern.size();
	int n = text.size();
	int i = m - 1;
	int j = m - 1;
	while (i <= n - 1)
	{
		if (pattern[j] == text[i])
		{
			if (j == 0)
				return i;
			else
			{
				i--;
				j--;
			}
		}
		else
		{
			i = i + m - std::min(j, 1 + last[text[i]]);
			j = m - 1;
		}
	}
	return -1;
}
