#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
  int i = 2;
  
  
  /*****************************************
   * Opérateurs classique
   *****************************************/
  
  //test +
  i = 10+1 ;
  
  //test -
  i = 10-1 ;
  
  //test *
  i = 10*1 ;
  
  //test /
  i = 10/1 ;
  
  //test %
  i = 10%1 ;
  
  
  /*****************************************
   * Opérateurs d'affectation
   *****************************************/
   
  //test =
  i= 0 ;
  
  // test +=
  i += 3 ;
  
  // test -=
  i -= 3 ;
  
  // test *=
  i *= 3 ;
  
  // test /=
  i/= 3 ;
  
  // test %=
  i %= 3 ;
  
  /*****************************************
   * Opérateurs binaires
   *****************************************/
   
  // test ~
  i = ~10 ;
  
  //test &
  i = i&10 ;
  
  //test |
  i = i|10 ;
  
  //test >>
  i = i>>1 ;
  
  //test <<
  i = i<<1 ;
  
  		
  return EXIT_SUCCESS ;
}