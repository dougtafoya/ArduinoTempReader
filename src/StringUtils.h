#ifndef STRING_UTILS_H
#define STRING_UTILS_H

static int compareString(char* str1, char* str2)
{
	while (*str1 == *str2)
	{
	    if (!*str1 || !*str2)
	    {
	    	break;
	    }
	    str1++;
	    str2++;
	}
	 
   if (*str1 == '\0' && *str2 == '\0')
   {
   		return 1;
   }
   else
   {
   		return 0;
   }
}

//returned length includes terminator
static int stringLength(char* string)
{
    if(*string == '\0')
    {
    	return 1;
    }

    int count = 0;
    char* counterP = string;

    while(*counterP++)
    {
        count++;
    }
    //to include terminator
    return count+1;
}

//leaves it up to the caller where the dest points to
static void copyString(char* dest,char* source)
{
	char* origin = dest;
	while(*source)
	{
		*dest++ = *source++;
	}
	//needed to move terminator as well
	*dest = *source;

	dest = origin;
}

static int concatString(char* dest,int destSize,char* source)
{
	int destLengthWithoutTerminator = stringLength(dest)-1;
	int sourceLength = stringLength(source);

	if(destLengthWithoutTerminator+sourceLength > destSize)
	{
		return -1;
	}

	char* editDestPtr = dest+destLengthWithoutTerminator;
	copyString(editDestPtr,source);

	return 0;
}

#endif
