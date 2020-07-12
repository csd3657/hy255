
#include "mystring.h"

/*fucntion which returns the size of a stirng (strlen C) */
size_t ms_length(const char *pcStr)
{
	const char *pcStrEnd = pcStr;
 	assert(pcStr != NULL);
	while (*pcStrEnd != '\0')
    	pcStrEnd++;
	return pcStrEnd - pcStr;
} 

/*function which copies the src to dest and returns the dest (strcpy C)*/
char* ms_copy(char *dest, const char *src)
{
	/*pointer which help us to read the string */
	char *temp = dest; 
	/*check for errors*/
	assert(src != NULL);
	/*read the string until END*/
	while(*src != '\0'){
		*temp = *src;
		src++;
		temp++;
	}
	/*finally add the \0 end char to the string*/
	*temp = '\0';
	return dest;
}

/*function which copies the n first bits from src to dest and returns the dest (strncpy C)*/
char *ms_ncopy(char *dest, const char *src, size_t n)
{
	int i = 0;
	/*pointer which help us to read the string */
	char *temp = dest; 
	/*check for errors*/
	assert(src);
	assert(n <= ms_length(src)+1);
	/*read the string until END*/
	while((src != NULL) && (i < n)){
		*temp = *src;
		src++;
		temp++;
		i++;
	}
	*temp = '\0';
	return dest;
}

/*function which returns the dest as the union of dest and src (strcat C)*/
char *ms_concat(char *dest, const char *src)
{
	/*copy pointer to the dest string*/
	char *temp = dest;
	/*and we need to reach the last char of the string*/
    temp += ms_length(dest);
	assert(src);
	/*while we have not reach the end of the src string we copy the chars to the end of the dest strig*/
    while(*src != '\0'){
        *temp = *src;
		temp++;
		src++;
    }
	/*we put the terminated char to the pointer*/
    *temp  = '\0';
    return dest;
}

/*function which returns the dest as the union of dest and n chars of src (strncat C)*/
char *ms_nconcat(char *dest, const char *src, size_t n)
{
	int i = 0;
	/*copy pointer to the dest string*/
	char *temp = dest;
	/*and we need to reach the last char of the string*/
    temp += ms_length(dest);
	assert(src);
	/*while we have not reach the end of the src string we copy the chars to the end of the dest strig*/
    while((*src != '\0') && (i < n)){
        *temp = *src;
		temp++;
		src++;
		i++;
    }
	/*we put the terminated char to the pointer*/
    *temp  = '\0';
    return dest;
}

/*function which compares str1 and str2 
and returns 0 if str1==str2, returns negative if str2>str1,
returns positive if str1>str2  (strcmp C) */
int ms_compare(const char *s1, const char *s2)
{
	assert(s1);
    assert(s2);
	/*while we have not find the end of strings*/
    while(!(*s1=='\0' && *s2=='\0')){
		/*if a char from the first string is not the same with the
		 char of the other string we return the difference of the chars */
        if (*s1 != *s2){
			if(*s1 > *s2) return 1;
			else if(*s1 < *s2) return -1;
		}
		s1++;
		s2++;
    }
	/*else we return 0;*/
    return 0;
}

/*It s the same function with ms_compare but compares only n first chars (strncmp C)*/
int ms_ncompare(const char * s1 , const char * s2 , size_t n)
{
    assert(s1!=NULL);
    assert(s2!=NULL);
	if(n == 0){
        return 0;
    }
	/*we search the fisrt n chars and we do the same with the ms_compare function*/
	while(n > 0){
		if(*s1 != *s2){
			if(*s1 > *s2) return 1;
			else if(*s1 < *s2) return -1;
		}
		s1++;
		s2++;
		n--;
	}
    return 0;
}

/*The ms_search() function finds the first occurrence of the substring needle in the string haystack. (strstr C)*/
char * ms_search(const char * haystack, const char * needle)
{
	size_t t;
	t = ms_length(needle);
	/*we start to search if the */
	while(*haystack != '\0'){
		if(ms_ncompare(haystack, needle, t) == 0){
			return (char *) haystack;
		}else{
			haystack++;
		}
		
	}
	return NULL;
}