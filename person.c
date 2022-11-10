/********************************************************************************
* person.c: Inneh�ller definitioner av associerade funktioner tillh�rande
*           strukten person, som anv�nds f�r agring samt utskrift av persondata.
********************************************************************************/
#include "person.h"

/********************************************************************************
* person_mem: Strukt inneh�llande variabler f�r lagring av persondata.
********************************************************************************/
typedef struct person_mem
{
   const char* name;       /* Personens namn. */
   unsigned int age;       /* Personens �lder. */
   const char* address;    /* Personens hemadress. */
   const char* occupation; /* Personens yrke. */
   enum gender gender;     /* Personens k�n. */
} person_mem_t, *person_mem_ptr_t;

/* Statiska funktioner: */
static struct person_vtable* person_vtable_ptr_new(void);
static struct person_mem* person_mem_new(const char* name,
                                         const unsigned age,
                                         const char* address,
                                         const char* occupation,
                                         const enum gender gender);
static void person_mem_delete(struct person_mem** self);

/********************************************************************************
* person_init: Lagrar angiven persondata i ett person-objekt.
*
*              - self      : Pekare till objektet som ska lagra uppgifterna.
*              - name      : Personens namn.
*              - age       : Personens �lder.
*              - address   : Personens hemadress.
*              - occupation: Personens yrke.
*              - gender    : Personens k�n.
********************************************************************************/
void person_init(struct person* self,
                 const char* name,
                 const unsigned int age,
                 const char* address,
                 const char* occupation,
                 const enum gender gender)
{
   self->mem = person_mem_new(name, age, address, occupation, gender);
   self->vptr = person_vtable_ptr_new();
   return;
}

/********************************************************************************
* person_clear: Nollst�ller persondata lagrat av angivet person-objekt.
*
*               - self: Pekare till objektet som ska nollst�llas.
********************************************************************************/
void person_clear(struct person* self)
{
   person_mem_delete(&self->mem);
   self->vptr = 0;
   return;
}

/********************************************************************************
* person_new: Allokerar minne och lagrar angiven persondata i ett person-objekt.
*             En pekare till det dynamiskt allokerade objektet returneras.
*             Om minnesallokeringen misslyckas s� returneras null.
*
*             - name      : Personens namn.
*             - age       : Personens �lder.
*             - address   : Personens hemadress.
*             - occupation: Personens yrke.
*             - gender    : Personens k�n.
********************************************************************************/
struct person* person_new(const char* name,
                          const unsigned int age,
                          const char* address,
                          const char* occupation,
                          const enum gender gender)
{
   struct person* self = (struct person*)malloc(sizeof(struct person));
   if (!self) return 0;
   person_init(self, name, age, address, occupation, gender);
   return self;
}

/********************************************************************************
* person_delete: Raderar angivet person-objekt genom att frig�ra dynamiskt
*                allokerat minne f�r denna och s�tter motsvarande pekare till
*                null. F�r att m�jligg�ra detta passeras adressen till den pekare 
*                som pekar p� det dynamiskt allokerade minnet.
*
*                - self: Adressen till den pekare som pekar p� objektet som
*                        som ska raderas.
********************************************************************************/
void person_delete(struct person** self)
{
   free(*self);
   *self = 0;
   return;
}

/********************************************************************************
* person_print: Skriver ut lagrad persondata via angiven utstr�m, d�r
*               standardutenheten stdout anv�nds som default f�r utskrift
*               i terminalen.
*
*               - self   : Pekare till objektet som lagrar persondatan.
*               - ostream: Pekare till angiven utstr�m (default = stdout).
********************************************************************************/
void person_print(const struct person* self,
                  FILE* ostream)
{
   if (!ostream) ostream = stdout;
   fprintf(ostream, "--------------------------------------------------------------------------------\n");
   fprintf(ostream, "Name: %s\n", self->mem->name);
   fprintf(ostream, "Age: %u\n", self->mem->age);
   fprintf(ostream, "Address: %s\n", self->mem->address);
   fprintf(ostream, "Occupation: %s\n", self->mem->occupation);
   fprintf(ostream, "Gender: %s\n", person_gender_str(self));
   fprintf(ostream, "--------------------------------------------------------------------------------\n\n");
   return;
}

/********************************************************************************
* person_gender_str: Returnerar personens k�n p� textform.
*
*                    - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
const char* person_gender_str(const struct person* self)
{ 
   if (self->mem->gender == GENDER_MALE) return "Male";
   else if (self->mem->gender == GENDER_FEMALE) return "Female";
   else if (self->mem->gender == GENDER_OTHER) return "Other";
   else return "Unspecified";
}

/********************************************************************************
* person_name: Returnerar personens namn.
*
*              - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
const char* person_name(const struct person* self)
{
   return self->mem->name;
}

/********************************************************************************
* person_age: Returnerar personens �lder.
*
*             - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
unsigned int person_age(const struct person* self)
{
   return self->mem->age;
}

/********************************************************************************
* person_address: Returnerar personens hemadress.
*
*                 - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
const char* person_address(const struct person* self)
{
   return self->mem->address;
}

/********************************************************************************
* person_occupation: Returnerar personens yrke.
*
*                    - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
const char* person_occupation(const struct person* self)
{
   return self->mem->occupation;
}

/********************************************************************************
* person_gender: Returnerar personens k�n som en enumerator av enumeration
*                gender, allts� GENDER_MALE, GENDER_FEMALE, GENDER_OTHER eller
*                GENDER_NONE.
*
*                - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
enum gender person_gender(const struct person* self)
{
   return self->mem->gender;
}

/********************************************************************************
* person_vtable_ptr_new: Returnerar en pekare till ett vtable inneh�llande
*                        funktionspekare till associerade funktioner f�r
*                        strukten person. Tabellen deklareras statiskt s� att
*                        minnet f�r den kvarst�r hela programmet. Pekarna s�tts
*                        till att peka p� motsvarande funktioner vid start.
*                        Vid anrop av denna funktion returneras sedan en pekare
*                        till denna tabell.
********************************************************************************/
static struct person_vtable* person_vtable_ptr_new(void)
{
   static struct person_vtable self = 
   {
      .print = &person_print,
      .gender_str = &person_gender_str,
      .name = &person_name,
      .age = &person_age,
      .address = &person_address,
      .occupation = &person_occupation,
      .gender = &person_gender,
      .clear = &person_clear
   };

   return &self;
}

/********************************************************************************
* person_mem_new: Allokerar minne f�r lagring av ny persondata och returnerar
*                 en pekare till det objekt som lagrar persondatan. Ifall
*                 minnesallokeringen misslyckas s� returneras en nullpekare.
* 
*                 - name      : Personens namn.
*                 - age       : Personens �lder.
*                 - address   : Personens hemadress.
*                 - occupation: Personens yrke.
*                 - gender    : Personens k�n.
********************************************************************************/
static struct person_mem* person_mem_new(const char* name,
                                         const unsigned age,
                                         const char* address,
                                         const char* occupation,
                                         const enum gender gender)
{
   struct person_mem* self = (struct person_mem*)malloc(sizeof(struct person_mem));
   if (!self) return 0;
   self->name = name;
   self->age = age;
   self->address = address;
   self->occupation = occupation;
   self->gender = gender;
   return self;
}

/********************************************************************************
* person_mem_delete: Frig�r minne allokerat f�r lagring av persondata och
*                    s�tter motsvarande pekare till null. F�r att m�jligg�ra
*                    detta s� passeras adressen till den pekare som pekar p�
*                    personuppgifterna (annars hade en kopia av denna pekare
*                    kommit fram och vi hade d� inte kunnat s�tta ordinarie
*                    pekaren till null, bara kopian).
*
*                    - self: Adressen till den pekare som pekar p� 
*                            personuppgifterna.
********************************************************************************/
static void person_mem_delete(struct person_mem** self)
{
   free(*self);
   *self = 0;
   return;
}