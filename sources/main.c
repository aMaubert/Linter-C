/**
 *  author : amaubert
 *  date : 2018/10/18
 *  version : 1.0
 *  file : source/main.c
 ************************************************************/
#include <stdlib.h>
#include <stdio.h>

double addition(double a, double b) ;

int main(int argc, char const *argv[]) {
  printf("addition 1 + 2 = %.0f\n",addition(1,2)) ;
  return 0 ;
}


double addition(double a, double b){
  return a + b
}
