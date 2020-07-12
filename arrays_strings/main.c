#include "mystring.h"

int main(void)
{
   char a[] = "DIMITRIS";
   char b[] = "MILATHIANAKIS";

   printf("\nLenght: %s is %d", a, ms_length(a));
   printf("\nLenght: %s is %d", b, ms_length(b));

   ms_copy(a, b);
   printf("\nms_copy: %s", a);

   ms_ncopy(a, b, 4);
   printf("\nms_ncopy: %s", a);
   ms_copy(a, "DIMITRIS");
   ms_copy(b, "MILATHIANAKIS");

   ms_concat(a, b);
   printf("\nms_concat: %s", a);
   ms_copy(a, "DIMITRIS");
   ms_copy(b, "MILATHIANAKIS");

   ms_nconcat(a, b, 4);
   printf("\nms_nconcat: %s", a);
   ms_copy(a, "BA");
   ms_copy(b, "A");

   if (ms_compare(a, b) == 0)
   {
      printf("\nISA: %s %s", a, b);
   }
   else if (ms_compare(a, b) < 0)
   {
      printf("\n MEGALUTERO: %s %s", a, b);
   }else{
      printf("\n MIKROTERO: %s %s", a, b);
   }

   if(ms_search(a,b) != NULL){
      printf("\n\n VRETHIKE TO %s mesa STO %s\n\n", b, a);

   }else{
   printf("\n\n DEN VRETHIKE TO %s mesa STO %s\n\n", b, a);
   }

   return 0;
}
