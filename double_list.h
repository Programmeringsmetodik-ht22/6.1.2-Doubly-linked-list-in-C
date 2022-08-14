/*******************************************************************************
* double_list.h: Innehåller funktionalitet för implementering av dubbellänkade 
*                listor som kan lagra flyttal av datatypen double via strukten
*                double_list samt tillhörande externa funktioner.
*******************************************************************************/
#ifndef DOUBLE_LIST_H_
#define DOUBLE_LIST_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
* double_list: Implementering av en dubbellänkad lista för lagring av flyttal.
*******************************************************************************/
struct double_list
{
   struct double_node* first; /* Pekare till första elementet i listan. */
   struct double_node* last;  /* Pekare till det sista elementet i listan. */
   size_t size;               /* Listans storlek (antalet element i listan). */
};

/*******************************************************************************
* double_node: Implementering av en nod som lagrar ett flyttal, vilket används
*              för dubbellänkade listor av strukten double_list. Listans
*              element kopplas samman via pekarna till föregående samt nästa
*              element och behöver därmed inte lagras på konsekutiva adresser
*              i minnet, vilket är fallet för vektorer.
*******************************************************************************/
struct double_node
{
   struct double_node* previous; /* Pekare till föregående nod. */
   struct double_node* next;     /* Pekare till efterföljande nod. */
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