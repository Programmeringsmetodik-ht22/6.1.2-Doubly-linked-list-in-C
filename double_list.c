/*******************************************************************************
* double_list.c: Inneh�ller funktioner f�r implementering av dubbell�nkade
*                listor via struktar double_list samt double_node.
*******************************************************************************/
#include "double_list.h"

/* Statiska funktioner: */
static struct double_node* double_list_node_at(const struct double_list* self, 
                                               const size_t index);
static struct double_node* double_node_new(const double data);
static void double_node_delete(struct double_node** self);

/*******************************************************************************
* double_list_new: Initierar tom l�nkad lista.
*                  - self: Pekare till den l�nkade lista som skall initieras.
*******************************************************************************/
void double_list_new(struct double_list* self)
{
   self->first = 0;
   self->last = 0;
   self->size = 0;
   return;
}

/*******************************************************************************
* double_list_delete: T�mmer angiven l�nkad lista genom att frig�ra minne f�r
*                     allokerade noder och nollst�ller listans parametrar.
*                     - self: Pekare till den l�nkade listan.
*******************************************************************************/
void double_list_delete(struct double_list* self)
{
   for (struct double_node* i = self->first; i; )
   {
      struct double_node* next = i->next;
      double_node_delete(&i);
      i = next;
   }

   self->first = 0;
   self->last = 0;
   self->size = 0;
   return;
}

/*******************************************************************************
* double_list_ptr_new: Allokerar minne f�r ny l�nkad lista med angiven storlek.
*                      Varje element tilldelas angiven startv�rde.
*                      - size: Antalet element den l�nkade listan skall rymma.
*                      - start_val: Startv�rde f�r samtliga element i listan.
*******************************************************************************/
struct double_list* double_list_ptr_new(const size_t size,
                                        const double start_val)
{
   struct double_list* self = (struct double_list*)malloc(sizeof(struct double_list));
   if (!self) return 0;
   double_list_new(self);

   for (size_t i = 0; i < size; ++i)
   {
      double_list_push_back(self, start_val);
   }
   return self;
}

/*******************************************************************************
* double_list_ptr_delete: Frig�r minne allokerat f�r angiven l�nkad lista.
*                         En dubbelpekare till den l�nkade listan passeras
*                         f�r att b�de frig�ra minnet f�r listan samt s�tta 
*                         pekaren till det heapallokerad minnet till null.
*                         - self: Adressen till den pekare som pekar p� 
*                                 den l�nkade listan.
*******************************************************************************/
void double_list_ptr_delete(struct double_list** self)
{
   double_list_delete(*self);
   free(*self);
   *self = 0;
   return;
}

/*******************************************************************************
* double_list_begin: Returnerar adressen till den f�rsta noden i angiven
*                    l�nkad lista.
*                    -self: Pekaren till den l�nkade listan.
*******************************************************************************/
struct double_node* double_list_begin(const struct double_list* self)
{
   return self->first;
}

/*******************************************************************************
* double_list_end: Returnerar adressen direkt efter sista noden i angiven
*                  l�nkad lista.
*                  -self: Pekare till den l�nkade listan.
*******************************************************************************/
struct double_node* double_list_end(const struct double_list* self)
{
   return self->last->next;
}

/*******************************************************************************
* double_list_push_front: Placerar ett nytt flyttal lagrat via en ny nod
*                         l�ngst fram i angiven l�nkad lista.
*                         - self: Pekare till den l�nkade listan.
*                         - new_element: Det flyttal som skall lagras.
*******************************************************************************/
int double_list_push_front(struct double_list* self, 
                           const double new_element)
{
   struct double_node* n1 = double_node_new(new_element);
   struct double_node* n2 = self->first;
   if (!n1) return 1;

   if (!self->size++)
   {
      self->first = n1;
      self->last = n1;
   }
   else
   {
      n1->next = n2;
      n2->previous = n2;
      self->first = n1;
   }

   return 0;
}

/*******************************************************************************
* double_list_push_back: Placerar ett nytt flyttal lagrat via en ny nod
*                        l�ngst bak i angiven l�nkad lista.
*                        - self: Pekare till den l�nkade listan.
*                        - new_element: Det flyttal som skall lagras.
*******************************************************************************/
int double_list_push_back(struct double_list* self, 
                          const double new_element)
{
   struct double_node* n1 = self->last;
   struct double_node* n2 = double_node_new(new_element);
   if (!n2) return 1;

   if (!self->size++)
   {
      self->first = n2;
      self->last = n2;
   }
   else
   {
      n1->next = n2;
      n2->previous = n1;
      self->last = n2;
   }

   return 0;
}

/*******************************************************************************
* double_list_pop_front: Tar bort f�rsta elementet i angiven l�nkad lista.
*                        - self: Pekare till den l�nkade listan.
*******************************************************************************/
void double_list_pop_front(struct double_list* self)
{
   if (self->size <= 1)
   {
      double_list_delete(self);
   }
   else
   {
      struct double_node* n1 = self->first;
      struct double_node* n2 = n1->next;

      n2->previous = 0;
      double_node_delete(&n1);
      self->first = n2;
      self->size--;
   }
   return;
}

/*******************************************************************************
* double_list_pop_back: Tar bort det sista elementet i angiven l�nkad lista.
*                       - self: Pekare till den l�nkade listan.
*******************************************************************************/
void double_list_pop_back(struct double_list* self)
{
   if (self->size <= 1)
   {
      double_list_delete(self);
   }
   else
   {
      struct double_node* n2 = self->last;
      struct double_node* n1 = n2->previous;

      n1->next = 0;
      double_node_delete(&n2);

      self->last = n1;
      self->size--;
   }
   return;
}

/*******************************************************************************
* double_list_assign_at_index: Tilldelar ett nytt v�rde p� angivet index.
*                              - self: Pekare till den l�nkade listan.
*                              - index: Index d�r det nya v�rdet skall lagras.
*                              - val: V�rdet som skall lagras p� angivet index.
*******************************************************************************/
void double_list_assign_at_index(struct double_list* self, 
                                 const size_t index, 
                                 const double val)
{
   if (index < self->size)
   {
      double_list_node_at(self, index)->data = val;
   }
   return;
}

/*******************************************************************************
* double_list_assign_at_address: Tilldelar ett flyttal till noden p� angiven 
*                                adress i angiven l�nkad lista. Denna funktion 
*                                �r l�mplig f�r iteration av l�nkade listor.
*                                - self: Pekare till den l�nkade listan.
*                                - address: Pekar p� nod som skall tilldelas.
*                                - val: Flyttalet som skall tilldelas.
*******************************************************************************/
void double_list_assign_at_address(struct double_list* self, 
                                   const struct double_node* address, 
                                   const double val)
{
   struct double_node* n1 = address;
   n1->data = val;
   return;
}

/*******************************************************************************
* double_list_at_index: Returnerar flyttal lagrat p� angivet index i en 
*                       l�nkad lista. Vid felaktigt index returneras 0.0.
*                       - self: Den l�nkade listan.
*                       - index: Index f�r flyttalet som skall returneras.
*******************************************************************************/
double double_list_at_index(const struct double_list* self, 
                            const size_t index)
{
   if (index < self->size)
   {
      return double_list_node_at(self, index)->data;
   }
   else
   {
      return 0;
   }
}

/*******************************************************************************
* double_list_at_address: Returnerar flyttal lagrat av nod p� angiven adress 
*                         i en l�nkad lista.
*                         - self: Pekare till den l�nkade listan.
*                         - address: Adressen till noden vars lagrade v�rde
*                                    skall returneras.
*******************************************************************************/
double double_list_at_address(const struct double_list* self, 
                              const struct double_node* address)
{
   return address->data;
}

/*******************************************************************************
* double_list_print: Skriver ut flyttal lagrade i en l�nkad lista via angiven
*                    utstr�m, d�r standardutenhet stdout anv�nds som default
*                    f�r utskrift i terminalen.
*                    - self: Pekare till den l�nkade listan.
*                    - ostream: Pekare till aktuell utstr�m.
*******************************************************************************/
void double_list_print(const struct double_list* self, 
                       FILE* ostream)
{
   if (!self->size) return;
   if (!ostream) ostream = stdout;
   fprintf(ostream, "--------------------------------------------------------------------------------\n");

   for (const struct double_node* i = self->first; i != self->last->next; i = i->next)
   {
      fprintf(ostream, "%g\n", i->data);
   }

   fprintf(ostream, "--------------------------------------------------------------------------------\n\n");
   return;
}

/*******************************************************************************
* double_list_clear: T�mmer och nollst�ller l�nkad lista.
*                    - self: Pekare till den l�nkade listan.
*******************************************************************************/
void (*double_list_clear)(struct double_list* self) = &double_list_delete;

/*******************************************************************************
* double_list_node_at: Returnerar adressen till noden p� angivet index i en
*                      l�nkad lista via iteration. Beroende p� nodens index
*                      sker iteration fram�t eller bak�t. 
*                      - self: Pekare till den l�nkade listan.
*                      - index: Index till noden vars adress skall returneras.
*******************************************************************************/
static struct double_node* double_list_node_at(const struct double_list* self, 
                                               const size_t index)
{
   if (index < self->size / 2)
   {
      struct double_node* node = self->first;
      for (size_t i = 0; i < index; ++i) node = node->next;
      return node;
   }
   else if (index >= self->size / 2 && index < self->size)
   {
      struct double_node* node = self->last;
      for (size_t i = self->size - 1; i > index; --i) node = node->previous;
      return node;
   }
   else
   {
      return 0;
   }
}

/*******************************************************************************
* double_node_new: Returnerar en ny nod som lagrar angivet flyttal.
*                  data: Det flyttal som skall lagras av den nya noden.
*******************************************************************************/
static struct double_node* double_node_new(const double data)
{
   struct double_node* self = (struct double_node*)malloc(sizeof(struct double_node));
   if (!self) return 0;
   self->previous = 0;
   self->next = 0;
   self->data = data;
   return self;
}

/*******************************************************************************
* double_node_delete: Frig�r minne allokerat f�r en nod och s�tter nodpekaren
*                     till null (d�rav skall adressen till nodpekaren passeras).
*                     - self: Adressen till den pekare som pekar p� nodpekaren.
*******************************************************************************/
static void double_node_delete(struct double_node** self)
{
   free(*self);
   *self = 0;
   return;
}