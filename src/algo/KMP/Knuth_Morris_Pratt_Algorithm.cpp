
/*
	KMPMatch(T,P)
	T : Text    : n characters
	P : Pattern : m characteris

	KMPFailureFunction(P)
*/
std::unordered_map<size_t,size_t> f;

void KMPFailureFunction(const std::string& p)
{
	size_t m=p.size();
	size_t i=1;
	size_t j=0;
	f[0]=0;
	while(i<m)
	{
		if(p[j]==p[i])
		{
			f[i]=j+1;
			i++;
			j++;
		}
		else if(j>0)
		{
			j=f[j-1];
		}
		else
		{
			f[i]=0;
			i++;
		}
	}
}

size_t KMPMatch(const std::string& t,const std::string& p)
{
	KMPFailureFunction(p);
	size_t n=t.size();
	size_t m=p.size();
	size_t i=0;
	size_t j=0;
	while(i<n)
	{
		if(p[j]==t[i])
		{
			if(j==m-1)
				return i-m+1;
			i++;
			j++;
		}
		else if(j>0)
			j=f[j-1];
		else 	
			i++;
	}
	return std::string::npos;

}

