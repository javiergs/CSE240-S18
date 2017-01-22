#include <stdio.h>
#define add(a,b) (a+b)
#define square(a) (a*a)
#define max(a,b) ((a>b)? a:b)
#define even(a) (((a%2)==0)? 1:0)

void main(){

   int a = 5, b = 6;

   printf("add(%d,%d) = %d\n",a,b,add(a,b));

   printf("square(%d) = %d\n",a,square(a));

   printf("max(%d,%d) = %d\n",a,b,max(a,b));

   if(even(a) == 0){
	printf("even(%d) = %d, %d is not an even number\n",a,even(a),a);
   }
   else{
	printf("even(%d) = %d, %d is an even number\n",a,even(a),a);
   }
}
