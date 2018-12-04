#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
  // test avec un if
  if(1 ==1)
  {
	//test avec un for
	for(int i = 0; i < 10; i++)
	{	
		//test avec un while
		while(i%2 == 0)
		{	
			//test avec un do{} while() ;
			do
			{
				//test avec un switch
				switch(i)
				{
					default : break ;
				}	
			}while(true) ;
		}
		
	}
	//test de l'accolade commenté
	if()// {
	{
		
	}	
	printf("hello \n") ;
  }
  		
  return EXIT_SUCCESS ;
}
