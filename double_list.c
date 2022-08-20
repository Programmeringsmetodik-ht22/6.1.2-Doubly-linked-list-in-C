/*******************************************************************************
* double_list.c: Innehåller funktioner för implementering av dubbellänkade
*                listor via struktar double_list samt double_node.
*******************************************************************************/
#include "double_list.h"

/* Statiska funktioner: */
static struct double_node* double_node_new(const double data);
static void double_node_delete(struct double_node** self);

/*******************************************************************************
* double_list_new: Initierar tom länkad lista.
* 
*                  - self: Pekare till den länkade lista som skall initieras.
*******************************************************************************/
void double_list_new(struct double_list* self)
{
   self->first = 0;
   self->last = 0;
   self->size = 0;
   return;
}

/*******************************************************************************
* double_list_delete: Tömmer angiven länkad lista genom att frigöra minne för
*                     allokerade noder och nollställer listans parametrar.
* 
*                     - self: Pekare till den länkade listan.
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
* double_list_ptr_new: Allokerar minne för ny länkad lista med angiven storlek.
*                      Varje element tilldelas angiven startvärde.
* 
*                      - size     : Storleken på den länkade listan vid start.
*                      - start_val: Startvärde för samtliga element i listan.
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
* double_list_ptr_delete: Frigör minne allokerat för angiven länkad lista.
*                         En dubbelpekare till den länkade listan passeras
*                         för att både frigöra minnet för listan samt sätta 
*                         pekaren till det heapallokerad minnet till null.
* 
*                         - self: Adressen till den pekare som pekar på 
*                                 den länkade listan.
*******************************************************************************/
void double_list_ptr_delete(struct double_list** self)
{
   double_list_delete(*self);
   free(*self);
   *self = 0;
   return;
}

/*******************************************************************************
* double_list_begin: Returnerar adressen till den första noden i angiven
*                    länkad lista.
* 
*                    - self: Pekaren till den länkade listan.
*******************************************************************************/
struct double_node* double_list_begin(const struct double_list* self)
{
   return self->first;
}

/*******************************************************************************
* double_list_end: Returnerar adressen direkt efter sista noden i angiven
*                  länkad lista.
* 
*                  - self: Pekare till den länkade listan.
*******************************************************************************/
struct double_node* double_list_end(const struct double_list* self)
{
   return self->last->next;
}

/*******************************************************************************
* double_list_resize: Ändrar storleken på angiven länkad lista. Ifall nya noder 
*                     läggs till sätts deras respektive startvärde till noll.
* 
*                     - self    : Pekare till den länkade listan.
*                     - new_size: Ny storlek sett till antalet noder.
*******************************************************************************/
int double_list_resize(struct double_list* self,
                       const size_t new_size)
{
   while (self->size < new_size)
   {
      double_list_push_back(self, 0);
   }

   while (self->size > new_size)
   {
      double_list_pop_back(self);
   }

   if (self->size == new_size)
   {
      return 0;
   }
   else
   {
      return 1;
   }
}

/*******************************************************************************
* double_list_push_front: Placerar ett nytt flyttal lagrat via en ny nod
*                         längst fram i angiven länkad lista.
* 
*                         - self: Pekare till den länkade listan.
*                         - data: Det flyttal som skall lagras.
*******************************************************************************/
int double_list_push_front(struct double_list* self, 
                           const double data)
{
   struct double_node* n1 = double_node_new(data);
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
*                        längst bak i angiven länkad lista.
* 
*                        - self: Pekare till den länkade listan.
*                        - data: Det flyttal som skall lagras.
*******************************************************************************/
int double_list_push_back(struct double_list* self, 
                          const double data)
{
   struct double_node* n1 = self->last;
   struct double_node* n2 = double_node_new(data);
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
* double_list_pop_front: Tar bort första elementet i angiven länkad lista.
* 
*                        - self: Pekare till den länkade listan.
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
* double_list_pop_back: Tar bort det sista elementet i angiven länkad lista.
* 
*                       - self: Pekare till den länkade listan.
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
* double_list_insert_at_index: Lägger till en ny nod som lagrar angivet flyttal
*                               på angivet index.
* 
*                              - self : Pekare till den länkade listan.
*                              - index: Index där den nya noden skall placeras.
*                              - val  : Värdet som skall lagras.
*******************************************************************************/
int double_list_insert_at_index(struct double_list* self,
                                const size_t index,
                                const double val)
{
   if (index == 0)
   {
      return double_list_push_front(self, val);
   }
   else if (index >= self->size)
   {
      return double_list_push_back(self, val);
   }
   else
   {
      struct double_node* n2 = double_node_new(val);
      struct double_node* n3 = double_list_node_at(self, index);
      struct double_node* n1 = n3->previous;

      if (!n2) return 1;

      n1->next = n2;
      n2->previous = n1;

      n2->next = n3;
      n3->previous = n2;

      self->size++;
      return 0;
   }
}

/*******************************************************************************
* double_list_insert_at_address: Lägger till en ny nod till noden på angiven
*                                adress i angiven länkad lista. Ingen kontroll
*                                genomförs gällande ifall angiven adress är
*                                korrekt, vilket måste skötas av användaren.
* 
*                                - self   : Pekare till den länkade listan.
*                                - address: Pekar på adressen där den nya
*                                           noden skall placeras. 
*                                - val    : Värdet som skall lagras.
*******************************************************************************/
int double_list_insert_at_address(struct double_list* self,
                                  struct double_node* address,
                                  const double val)
{
   if (!self->size)
   {
      return double_list_push_back(self, val);
   }
   else
   {
      struct double_node* n2 = double_node_new(val);
      struct double_node* n3 = address;
      struct double_node* n1 = n3->previous;

      if (!n2) return 1;

      n1->next = n2;
      n2->previous = n1;

      n2->next = n3;
      n3->previous = n2;
      self->size++;
      return 0;
   }
}

/*******************************************************************************
* double_list_remove_at_index: Tar bort nod lagrad på angivet index i en 
*                              länkad lista.
* 
*                             - self : Pekare till den länkade listan.
*                             - index: Index för den nod som skall raderas.
*******************************************************************************/
int double_list_remove_at_index(struct double_list* self,
                                const size_t index)
{
   if (index < self->size)
   {
      struct double_node* n2 = double_list_node_at(self, index);
      struct double_node* n1 = n2->previous;
      struct double_node* n3 = n2->next;

      n1->next = n3;
      n3->previous = n1;

      double_node_delete(&n2);
      self->size--;
      return 0;
   }
   else
   {
      return 1;
   }
}

/*******************************************************************************
* double_list_remove_at_address: Tar bort nod lagrad på angiven adress i en
*                                länkad lista. Ingen kontroll genomförs
*                                gällande ifall angiven adress är korrekt,
*                                vilket måste skötas av användaren.
*
*                                - self   : Pekare till den länkade listan.
*                                - address: Adressen till noden som skall raderas.
*******************************************************************************/
void double_list_remove_at_address(struct double_list* self,
                                  struct double_node* address)
{
   struct double_node* n2 = address;
   struct double_node* n1 = n2->previous;
   struct double_node* n3 = n2->next;

   n1->next = n3;
   n3->previous = n1;

   double_node_delete(&n2);
   self->size--;
   return;
}

/*******************************************************************************
* double_list_assign_at_index: Tilldelar ett nytt värde på angivet index.
* 
*                              - self : Pekare till den länkade listan.
*                              - index: Index där det nya värdet skall lagras.
*                              - val  : Värdet som skall lagras.
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
* double_list_assign_at_address: Tilldelar ett flyttal till noden på angiven 
*                                adress i angiven länkad lista. Ingen kontroll
*                                genomförs gällande ifall angiven adress är
*                                korrekt, vilket måste skötas av användaren.
* 
*                                - self   : Pekare till den länkade listan.
*                                - address: Pekar på nod som skall tilldelas.
*                                - val    : Flyttalet som skall tilldelas.
*******************************************************************************/
void double_list_assign_at_address(struct double_list* self, 
                                   struct double_node* address, 
                                   const double val)
{
   address->data = val;
   return;
}

/*******************************************************************************
* double_list_at_index: Returnerar flyttal lagrat på angivet index i en 
*                       länkad lista. Vid felaktigt index returneras 0.0.
* 
*                       - self : Pekare till den länkade listan.
*                       - index: Index för flyttalet som skall returneras.
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
* double_list_at_address: Returnerar flyttal lagrat av nod på angiven adress 
*                         i en länkad lista.
*                         - self    : Pekare till den länkade listan.
*                         - address : Adressen till noden vars lagrade värde
*                                     skall returneras.
*******************************************************************************/
double double_list_at_address(const struct double_list* self, 
                              const struct double_node* address)
{
   return address->data;
}

/*******************************************************************************
* double_list_copy: Kopierar innehållet från en länkad lista till en annan.
*                   Eventuellt tidigare innehåll raderas ur listan som
*                   kopiering sker till.
* 
*                   - self  : Pekare till den länkade lista som kopierat
*                              innehåll skall lagras i.
*                   - source: Pekare till den länkade lista vars innehåll 
*                              skall kopieras.
*******************************************************************************/
int double_list_copy(struct double_list* self,
                     const struct double_list* source)
{
   double_list_delete(self);
   double_list_resize(self, source->size);

   if (self->size == source->size)
   {
      struct double_node* n1 = self->first;

      for (struct double_node* i = source->first; i != source->last->next; i = i->next)
      {
         n1->data = i->data;
         n1 = n1->next;
      }

      return 0;
   }
   else
   {
      return 1;
   }
}

/*******************************************************************************
* double_list_join: Sätter samman innehåll lagrat i två länkade listor genom
*                   att kopiera från en lista till en annan.
* 
*                   - self      : Pekare till den länkade lista där det
*                                 sammansatta innehållet skall lagras.
*                   - other_list: Pekare till den lista vars innehåll skall
*                                 kopieras till den sammansatta listan.
*******************************************************************************/
int double_list_join(struct double_list* self,
                     const struct double_list* other_list)
{
   if (!self->size)
   {
      return double_list_copy(self, other_list);
   }
   else
   {
      const size_t new_size = self->size + other_list->size;
      struct double_node* n1 = self->last;
      double_list_resize(self, new_size);

      if (self->size != new_size)
      {
         return 1;
      }
      else
      {
         n1 = n1->next;

         for (struct double_node* i = other_list->first; i != other_list->last->next; i = i->next)
         {
            n1->data = i->data;
            n1 = n1->next;
         }

         return 0;
      }
   }
}

/*******************************************************************************
* double_list_move: Förflyttar innehåll från en länkad lista till en annan.
*                   Efter förflyttningen äger angiven länkad lista allokerat
*                   minne, medan den lista som utgör källa töms och kan därför
*                   inte längre användas för att komma åt innehållet.
* 
*                   - self  : Pekare till den länkade listan som innehållet
*                             skall förflyttas till.
*                   - source: Pekare till den lista som utgör källa.
*******************************************************************************/
void double_list_move(struct double_list* self,
                      struct double_list* source)
{
   double_list_delete(self);
   self->first = source->first;
   self->last = source->last;
   self->size = source->size;

   source->first = 0;
   source->last = 0;
   source->size = 0;
   return;
}

/*******************************************************************************
* double_list_print: Skriver ut flyttal lagrade i en länkad lista via angiven
*                    utström, där standardutenhet stdout används som default
*                    för utskrift i terminalen.
* 
*                    - self   : Pekare till den länkade listan.
*                    - ostream: Pekare till aktuell utström.
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
* double_list_node_at: Returnerar adressen till noden på angivet index i en
*                      länkad lista via iteration. Beroende på nodens index
*                      sker iteration framåt eller bakåt. 
* 
*                      - self : Pekare till den länkade listan.
*                      - index: Index till noden vars adress skall returneras.
*******************************************************************************/
struct double_node* double_list_node_at(const struct double_list* self, 
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
* double_list_clear: Tömmer och nollställer länkad lista.
* 
*                    - self: Pekare till den länkade listan.
*******************************************************************************/
void (*double_list_clear)(struct double_list* self) = &double_list_delete;

/*******************************************************************************
* double_node_new: Returnerar en ny nod som lagrar angivet flyttal.
* 
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
* double_node_delete: Frigör minne allokerat för en nod och sätter nodpekaren
*                     till null (därav skall adressen till nodpekaren passeras).
* 
*                     - self: Adressen till den pekare som pekar på nodpekaren.
*******************************************************************************/
static void double_node_delete(struct double_node** self)
{
   free(*self);
   *self = 0;
   return;
}