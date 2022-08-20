/*******************************************************************************
* double_list.c: Inneh�ller funktioner f�r implementering av dubbell�nkade
*                listor via struktar double_list samt double_node.
*******************************************************************************/
#include "double_list.h"

/* Statiska funktioner: */
static struct double_node* double_node_new(const double data);
static void double_node_delete(struct double_node** self);

/*******************************************************************************
* double_list_new: Initierar tom l�nkad lista.
* 
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
* 
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
* 
*                      - size     : Storleken p� den l�nkade listan vid start.
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
* 
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
* 
*                    - self: Pekaren till den l�nkade listan.
*******************************************************************************/
struct double_node* double_list_begin(const struct double_list* self)
{
   return self->first;
}

/*******************************************************************************
* double_list_end: Returnerar adressen direkt efter sista noden i angiven
*                  l�nkad lista.
* 
*                  - self: Pekare till den l�nkade listan.
*******************************************************************************/
struct double_node* double_list_end(const struct double_list* self)
{
   return self->last->next;
}

/*******************************************************************************
* double_list_resize: �ndrar storleken p� angiven l�nkad lista. Ifall nya noder 
*                     l�ggs till s�tts deras respektive startv�rde till noll.
* 
*                     - self    : Pekare till den l�nkade listan.
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
*                         l�ngst fram i angiven l�nkad lista.
* 
*                         - self: Pekare till den l�nkade listan.
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
*                        l�ngst bak i angiven l�nkad lista.
* 
*                        - self: Pekare till den l�nkade listan.
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
* double_list_pop_front: Tar bort f�rsta elementet i angiven l�nkad lista.
* 
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
* 
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
* double_list_insert_at_index: L�gger till en ny nod som lagrar angivet flyttal
*                               p� angivet index.
* 
*                              - self : Pekare till den l�nkade listan.
*                              - index: Index d�r den nya noden skall placeras.
*                              - val  : V�rdet som skall lagras.
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
* double_list_insert_at_address: L�gger till en ny nod till noden p� angiven
*                                adress i angiven l�nkad lista. Ingen kontroll
*                                genomf�rs g�llande ifall angiven adress �r
*                                korrekt, vilket m�ste sk�tas av anv�ndaren.
* 
*                                - self   : Pekare till den l�nkade listan.
*                                - address: Pekar p� adressen d�r den nya
*                                           noden skall placeras. 
*                                - val    : V�rdet som skall lagras.
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
* double_list_remove_at_index: Tar bort nod lagrad p� angivet index i en 
*                              l�nkad lista.
* 
*                             - self : Pekare till den l�nkade listan.
*                             - index: Index f�r den nod som skall raderas.
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
* double_list_remove_at_address: Tar bort nod lagrad p� angiven adress i en
*                                l�nkad lista. Ingen kontroll genomf�rs
*                                g�llande ifall angiven adress �r korrekt,
*                                vilket m�ste sk�tas av anv�ndaren.
*
*                                - self   : Pekare till den l�nkade listan.
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
* double_list_assign_at_index: Tilldelar ett nytt v�rde p� angivet index.
* 
*                              - self : Pekare till den l�nkade listan.
*                              - index: Index d�r det nya v�rdet skall lagras.
*                              - val  : V�rdet som skall lagras.
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
*                                adress i angiven l�nkad lista. Ingen kontroll
*                                genomf�rs g�llande ifall angiven adress �r
*                                korrekt, vilket m�ste sk�tas av anv�ndaren.
* 
*                                - self   : Pekare till den l�nkade listan.
*                                - address: Pekar p� nod som skall tilldelas.
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
* double_list_at_index: Returnerar flyttal lagrat p� angivet index i en 
*                       l�nkad lista. Vid felaktigt index returneras 0.0.
* 
*                       - self : Pekare till den l�nkade listan.
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
*                         - self    : Pekare till den l�nkade listan.
*                         - address : Adressen till noden vars lagrade v�rde
*                                     skall returneras.
*******************************************************************************/
double double_list_at_address(const struct double_list* self, 
                              const struct double_node* address)
{
   return address->data;
}

/*******************************************************************************
* double_list_copy: Kopierar inneh�llet fr�n en l�nkad lista till en annan.
*                   Eventuellt tidigare inneh�ll raderas ur listan som
*                   kopiering sker till.
* 
*                   - self  : Pekare till den l�nkade lista som kopierat
*                              inneh�ll skall lagras i.
*                   - source: Pekare till den l�nkade lista vars inneh�ll 
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
* double_list_join: S�tter samman inneh�ll lagrat i tv� l�nkade listor genom
*                   att kopiera fr�n en lista till en annan.
* 
*                   - self      : Pekare till den l�nkade lista d�r det
*                                 sammansatta inneh�llet skall lagras.
*                   - other_list: Pekare till den lista vars inneh�ll skall
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
* double_list_move: F�rflyttar inneh�ll fr�n en l�nkad lista till en annan.
*                   Efter f�rflyttningen �ger angiven l�nkad lista allokerat
*                   minne, medan den lista som utg�r k�lla t�ms och kan d�rf�r
*                   inte l�ngre anv�ndas f�r att komma �t inneh�llet.
* 
*                   - self  : Pekare till den l�nkade listan som inneh�llet
*                             skall f�rflyttas till.
*                   - source: Pekare till den lista som utg�r k�lla.
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
* double_list_print: Skriver ut flyttal lagrade i en l�nkad lista via angiven
*                    utstr�m, d�r standardutenhet stdout anv�nds som default
*                    f�r utskrift i terminalen.
* 
*                    - self   : Pekare till den l�nkade listan.
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
* double_list_node_at: Returnerar adressen till noden p� angivet index i en
*                      l�nkad lista via iteration. Beroende p� nodens index
*                      sker iteration fram�t eller bak�t. 
* 
*                      - self : Pekare till den l�nkade listan.
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
* double_list_clear: T�mmer och nollst�ller l�nkad lista.
* 
*                    - self: Pekare till den l�nkade listan.
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
* double_node_delete: Frig�r minne allokerat f�r en nod och s�tter nodpekaren
*                     till null (d�rav skall adressen till nodpekaren passeras).
* 
*                     - self: Adressen till den pekare som pekar p� nodpekaren.
*******************************************************************************/
static void double_node_delete(struct double_node** self)
{
   free(*self);
   *self = 0;
   return;
}