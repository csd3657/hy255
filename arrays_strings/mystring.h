
#include <stdio.h>
#include <assert.h>
#include <stddef.h>


/*fucntion that returns the size of a stirng (strlen C)*/
size_t ms_length(const char pcStr[]);

/*function which copies the src to dest and returns the dest (strcpy C)*/
char* ms_copy (char *dest, const char *src);

/*function which copies the n first bits from src to dest and returns the dest (strncpy C)*/
char *ms_ncopy(char *dest, const char *src, size_t n);

/*function which returns the dest as the union of dest and src (strncat C)*/
char *ms_concat(char *dest, const char *src);

/*function which returns the dest as the union of dest and n chars of src (strcmp C)*/
char *ms_nconcat(char *dest, const char *src, size_t n);

/*function which compares str1 and str2 
and returns 0 if str1==str2, returns negative if str2>str1,
returns positive if str1>str2  ( C)*/
int ms_compare(const char *s1, const char *s2);

/*It s the same function with ms_compare but compares only n first chars (strncmp C)*/
int ms_ncompare(const char * str1 , const char * str2 , size_t n);

/*The ms_search() function finds the first occurrence of the substring needle in the string haystack. (strstr C)*/
char * ms_search(const char * haystack, const char * needle);
