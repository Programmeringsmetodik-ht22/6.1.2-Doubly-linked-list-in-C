/*******************************************************************************
* main.c: Implementering av en dubbell�nkad lista f�r lagring och utskrift 
*         av flyttal.
*******************************************************************************/
#include "double_list.h"

/*******************************************************************************
* main: Initierar en ny l�nkad lista l1, som rymmer 20 flyttal vid start. 
*       Listan tilldelas flyttal i stigande ordning. Ytterligare en tom l�nkad 
*       lista l2 initieras, som tilldelas inneh�llet fr�n listan l1 via 
*       f�rflyttning av minnet. Efter f�rflyttningen �ger d�rmed lista l2
*       minnet och lista l1 �r tom. Innan programmet avslutas sker utskrift
*       av lagrat inneh�ll i terminalen.
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