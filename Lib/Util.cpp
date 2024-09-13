#include "Util.h"

std::string GetStringIn(std::string string)
{
	int begin = 0;
	int end = 0;
	bool stringstarted = false;

	for (int i = 0; i <= string.length(); i++)
	{
		if(string[i] == ' ')
		{
			if(stringstarted)
			{
				end = i - 1;
			}

			if(string[begin] == ' ')
			{
				begin ++;
			}
		}
		else if(string[i] != ' ')
		{
			if(!stringstarted)
			{
				begin = i;
				stringstarted = true;
			}
			
			if(i == string.length ())
			{
				end = i;
			}
		}
	}
	
	return string.substr (begin, end - begin);
}