/*******************************************************************************
* main.c: Implementering av en dubbellänkad lista för lagring och utskrift 
*         av flyttal.
*******************************************************************************/
#include "double_list.h"

/*******************************************************************************
* main: Initierar en ny länkad lista l1, som rymmer 20 flyttal vid start. 
*       Listan tilldelas flyttal i stigande ordning. Ytterligare en tom länkad 
*       lista l2 initieras, som tilldelas innehållet från listan l1 via 
*       förflyttning av minnet. Efter förflyttningen äger därmed lista l2
*       minnet och lista l1 är tom. Innan programmet avslutas sker utskrift
*       av lagrat innehåll i terminalen.
*******************************************************************************/
int main(void)
{
   struct double_list* l1 = double_list_ptr_new(20, 0.0);
   struct double_list l2 = { .first = 0, .last = 0, .size = 0 };
   double num = 0.0;

   for (struct double_node* i = double_list_begin(l1); i != double_list_end(l1); i = i->next)
   {
      double_list_assign_at_address(l1, i, num += 0.5);
   }

   double_list_move(&l2, l1);
   double_list_print(&l2, stdout);

   return 0;
}