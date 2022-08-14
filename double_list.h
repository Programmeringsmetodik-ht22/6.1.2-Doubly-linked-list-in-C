/*******************************************************************************
* double_list.h: Inneh�ller funktionalitet f�r implementering av dubbell�nkade 
*                listor som kan lagra flyttal av datatypen double via strukten
*                double_list samt tillh�rande externa funktioner.
*******************************************************************************/
#ifndef DOUBLE_LIST_H_
#define DOUBLE_LIST_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
* double_list: Implementering av en dubbell�nkad lista f�r lagring av flyttal.
*******************************************************************************/
struct double_list
{
   struct double_node* first; /* Pekare till f�rsta elementet i listan. */
   struct double_node* last;  /* Pekare till det sista elementet i listan. */
   size_t size;               /* Listans storlek (antalet element i listan). */
};

/*******************************************************************************
* double_node: Implementering av en nod som lagrar ett flyttal, vilket anv�nds
*              f�r dubbell�nkade listor av strukten double_list. Listans
*              element kopplas samman via pekarna till f�reg�ende samt n�sta
*              element och beh�ver d�rmed inte lagras p� konsekutiva adresser
*              i minnet, vilket �r fallet f�r vektorer.
*******************************************************************************/
struct double_node
{
   struct double_node* previous; /* Pekare till f�reg�ende nod. */
   struct double_node* next;     /* Pekare till efterf�ljande nod. */
   double data;                  /* Det flyttal som noden lagrar. */
};

/* Externa funktioner: */
void double_list_new(struct double_list* self);
void double_list_delete(struct double_list* self);
struct double_list* double_list_ptr_new(const size_t size,
                                        const double start_val);
void double_list_ptr_delete(struct double_list** self);
struct double_node* double_list_begin(const struct double_list* self);
struct double_node* double_list_end(const struct double_list* self);
int double_list_push_front(struct double_list* self, 
                           const double new_element);
int double_list_push_back(struct double_list* self, 
                          const double new_element);
void double_list_pop_front(struct double_list* self);
void double_list_pop_back(struct double_list* self);
void double_list_assign_at_index(struct double_list* self,
                              const size_t index, 
                              const double val);
void double_list_assign_at_address(struct double_list* self, 
                                   const struct double_node* address, 
                                   const double val);
double double_list_at_index(const struct double_list* self, 
                            const size_t index);
double double_list_at_address(const struct double_list* self, 
                              const struct double_node* address);
void double_list_print(const struct double_list* self, 
                       FILE* ostream);

/* Funktionspekare: */
extern void (*double_list_clear)(struct double_list* self);

#endif /* DOUBLE_LIST_H_ */