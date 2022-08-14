/*******************************************************************************
* main.c: Implementering av en dubbellänkad lista för lagring och utskrift 
*         av flyttal.
*******************************************************************************/
#include "double_list.h"

/*******************************************************************************
* main: Initierar en ny länkad lista som rymmer 20 flyttal vid start. Listan
*       tilldelas flyttal i stigande ordning och innehåller skrivs ut i 
*       terminalen innan programmet avslutas.
*******************************************************************************/
int main(void)
{
   struct double_list* l1 = double_list_ptr_new(20, 0.0);
   double num = 0.0;

   for (struct double_node* i = double_list_begin(l1); i != double_list_end(l1); i = i->next)
   {
      double_list_assign_at_address(l1, i, num += 0.5);
   }

   for (size_t i = 0; i < l1->size; ++i)
   {
      printf("%g\n", double_list_at_index(l1, i));
   }

   double_list_print(l1, stdout);
   return 0;
}