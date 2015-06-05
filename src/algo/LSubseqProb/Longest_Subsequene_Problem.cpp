
/*				
					--**	LCS Problem		**--
*/


#define type int
std::pair<type,std::string> longest_common_substr(const std::string& str1, const std::string& str2)
{
	std::vector<std::vector<type>> l(str1.size() + 1, std::vector<type>(str2.size() + 1, 0));

	std::string ans = "";

	for (std::size_t i = 1; i < str1.size() + 1; ++i)
	{
		for (std::size_t j = 1; j < str2.size() + 1; ++j)
		{
			if (str1[i - 1] == str2[j - 1])
				l[i][j] = l[i - 1][j - 1] + 1;
			else
				l[i][j] = max(l[i - 1][j], l[i][j - 1]);	
		}
	}

	for (std::size_t j = str2.size(),i = str1.size(); j > 0,i>0;)
	{
		if (str1[i - 1] == str2[j - 1])
		{
			ans = str1[i - 1] + ans;
			i--;
			j--;
		}
		else
			l[i][j - 1] > l[i - 1][j] ? j-- : i--;
	}
	return std::make_pair(l.back().back(), ans);
}