#include "laugh.h"

int longest_laugh(const std::string &s)
{
    int longest = 0;
    int i, j = 0;
    for(i=0;i<s.size();i++)
    {
        if(s[i] == 'a' || s[i] == 'h')
        {
            for(j=i+1;j<s.size();j++)
            {
                if(s[j] != 'h' && s[j] != 'a')
                    break;
                if(s[j] == s[j-1])
                    break;
            }
            longest = std::max(longest, j-i);
            i = j-1;
        }
    }
    return longest;
}
