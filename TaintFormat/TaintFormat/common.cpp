#include "stdafx.h"
#include "common.h"

int CompareByteArray( cpbyte l, cpbyte r, int n )
{
    for (int i = 0; i < n; i++) {
        if (l[i] > r[i]) return 1;
        if (l[i] < r[i]) return -1;
    }
    return 0;
}

char * __cdecl MyStrStr (
    const char * str1,
    const char * str2
    )
{
    char *cp = (char *) str1;
    char *s1, *s2;

    if ( !*str2 )
        return((char *)str1);

    while (*cp)
    {
        s1 = cp;
        s2 = (char *) str2;

        while ( *s1 && *s2 && !(*s1-*s2) )
            s1++, s2++;

        if (!*s2)
            return(cp);

        cp++;
    }

    return(NULL);

}

bool StrPrefix( const char *str, const char *prefix )
{
    if (strlen(str) < strlen(prefix)) return false;
    return strncmp(str, prefix, strlen(prefix)) == 0;
}
