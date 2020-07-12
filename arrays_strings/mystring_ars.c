
#include "mystring.h"

/*fucntion which returns the size of a stirng (strlen C) */
size_t ms_length(const char pcStr[])
{
  size_t uiLength= 0U;
  assert(pcStr != NULL);
  while (pcStr[uiLength] != '\0')
    uiLength++;
  return uiLength;
} 

/*function which copies the src to dest and returns the dest (strcpy C)*/
char* ms_copy(char dest[], const char src[])
{
	size_t i = 0;
	assert(src != NULL);
	/*while second string end*/
	while(src[i] != '\0'){
		dest[i] = src[i];
		i++;
	}
	/*finally add \0 character to our string*/
	dest[i] = '\0';
	return dest;
}

/*function which copies the n first bits from src to dest and returns the dest (strncpy C)*/
char *ms_ncopy(char dest[], const char src[], size_t n)
{
	size_t i = 0;
	/*pointer which help us to read the string */
	char *dest2 = dest; 
	/*check for errors*/
	assert(src!=NULL);
	/*read the string until END*/
	while((src[i] != '\0') && (i < n)){
		dest2[i] = src[i];
		i++;
	}
	dest2[i] = '\0';
	return dest;
}

/*function which returns the dest as the union of dest and src (strcat C)*/
char *ms_concat(char dest[], const char src[])
{
	size_t i = 0;
	size_t  y  = ms_length(dest);

	/*copy pointer to the dest string*/
	/*and we need to reach the last char of the string*/
	assert(src !=NULL);

	/*while we have not reach the end of the src string we copy the chars to the end of the dest strig*/
    while(src[i] != '\0'){
        dest[i + y] = src[i];
		i++;
    }
	/*we put the terminated char to the pointer*/
    dest[i+y]  = '\0';
    return dest;
}

/*function which returns the dest as the union of dest and n chars of src (strncat C)*/
char *ms_nconcat(char dest[], const char src[], size_t n)
{
	size_t i = 0;
	size_t  y  = ms_length(dest);

	/*copy pointer to the dest string*/
	/*and we need to reach the last char of the string*/
	assert(src !=NULL);

	/*while we have not reach the end of the src string we copy the chars to the end of the dest strig*/
    while((src[i] != '\0') && (i<n)){
        dest[i + y] = src[i];
		i++;
    }
	/*we put the terminated char to the pointer*/
    dest[i+y]  = '\0';
    return dest;
}

/*function which compares str1 and str2 
and returns 0 if str1==str2, returns negative if str2>str1,
returns positive if str1>str2  (strcmp C) */
int ms_compare(const char s1[], const char s2[])
{
	size_t i = 0;
	assert(s1 != NULL);
    assert(s2 != NULL);
	/*while we have not find the end of strings*/
    while((s1[i] != '\0' && s2[i] != '\0')){
		/*if a char from the first string is not the same with the
		 char of the other string we return the deifference of the chars */
        if (s1[i] != s2[i]){
			if(s1[i] > s2[i]) return 1;
			else if(s1[i] < s2[i]) return -1;
        }
		i++;
    }
	/*else we return 0;*/
    return 0;
}

/*It s the same function with ms_compare but compares only n first chars (strncmp C)*/
int ms_ncompare(const char s1[] , const char s2[] , size_t n)
{
    size_t i = 0;
	assert(s1 != NULL);
    assert(s2 != NULL);
	/*while we have not find the end of strings*/
    while((s1[i] != '\0') && (s2[i] != '\0') && (i < n)){
		/*if a char from the first string is not the same with the
		 char of the other string we return the deifference of the chars */
		
        if (s1[i] != s2[i]){
            if(s1[i] > s2[i]) return 1;
			else if(s1[i] < s2[i]) return -1;
        }
		i++;
    }
	/*else we return 0;*/
    return 0;
}

/*The ms_search() function finds the first occurrence of the substring needle in the string haystack. (strstr C)*/
char * ms_search(const char haystack[] , const char needle[]){
	
	size_t a = 0;
	size_t b = 0;
	size_t m = 0;
	assert(haystack);
	assert(needle);
	while(haystack[a] != '\0') {
		b=0;
		m=a;
		while(haystack[m]==needle[b])
		{
			b++;
			if (needle[b] == '\0') return (char *)&haystack[a];
			m++;
		}
		a++;
	}
	
	return NULL;
}