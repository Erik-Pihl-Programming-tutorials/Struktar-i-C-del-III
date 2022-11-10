/********************************************************************************
* person.c: Innehåller definitioner av associerade funktioner tillhörande
*           strukten person, som används för agring samt utskrift av persondata.
********************************************************************************/
#include "person.h"

/********************************************************************************
* person_mem: Strukt innehållande variabler för lagring av persondata.
********************************************************************************/
typedef struct person_mem
{
   const char* name;       /* Personens namn. */
   unsigned int age;       /* Personens ålder. */
   const char* address;    /* Personens hemadress. */
   const char* occupation; /* Personens yrke. */
   enum gender gender;     /* Personens kön. */
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
*              - age       : Personens ålder.
*              - address   : Personens hemadress.
*              - occupation: Personens yrke.
*              - gender    : Personens kön.
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
* person_clear: Nollställer persondata lagrat av angivet person-objekt.
*
*               - self: Pekare till objektet som ska nollställas.
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
*             Om minnesallokeringen misslyckas så returneras null.
*
*             - name      : Personens namn.
*             - age       : Personens ålder.
*             - address   : Personens hemadress.
*             - occupation: Personens yrke.
*             - gender    : Personens kön.
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
* person_delete: Raderar angivet person-objekt genom att frigöra dynamiskt
*                allokerat minne för denna och sätter motsvarande pekare till
*                null. För att möjliggöra detta passeras adressen till den pekare 
*                som pekar på det dynamiskt allokerade minnet.
*
*                - self: Adressen till den pekare som pekar på objektet som
*                        som ska raderas.
********************************************************************************/
void person_delete(struct person** self)
{
   free(*self);
   *self = 0;
   return;
}

/********************************************************************************
* person_print: Skriver ut lagrad persondata via angiven utström, där
*               standardutenheten stdout används som default för utskrift
*               i terminalen.
*
*               - self   : Pekare till objektet som lagrar persondatan.
*               - ostream: Pekare till angiven utström (default = stdout).
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
* person_gender_str: Returnerar personens kön på textform.
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
* person_age: Returnerar personens ålder.
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
* person_gender: Returnerar personens kön som en enumerator av enumeration
*                gender, alltså GENDER_MALE, GENDER_FEMALE, GENDER_OTHER eller
*                GENDER_NONE.
*
*                - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
enum gender person_gender(const struct person* self)
{
   return self->mem->gender;
}

/********************************************************************************
* person_vtable_ptr_new: Returnerar en pekare till ett vtable innehållande
*                        funktionspekare till associerade funktioner för
*                        strukten person. Tabellen deklareras statiskt så att
*                        minnet för den kvarstår hela programmet. Pekarna sätts
*                        till att peka på motsvarande funktioner vid start.
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
* person_mem_new: Allokerar minne för lagring av ny persondata och returnerar
*                 en pekare till det objekt som lagrar persondatan. Ifall
*                 minnesallokeringen misslyckas så returneras en nullpekare.
* 
*                 - name      : Personens namn.
*                 - age       : Personens ålder.
*                 - address   : Personens hemadress.
*                 - occupation: Personens yrke.
*                 - gender    : Personens kön.
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
* person_mem_delete: Frigör minne allokerat för lagring av persondata och
*                    sätter motsvarande pekare till null. För att möjliggöra
*                    detta så passeras adressen till den pekare som pekar på
*                    personuppgifterna (annars hade en kopia av denna pekare
*                    kommit fram och vi hade då inte kunnat sätta ordinarie
*                    pekaren till null, bara kopian).
*
*                    - self: Adressen till den pekare som pekar på 
*                            personuppgifterna.
********************************************************************************/
static void person_mem_delete(struct person_mem** self)
{
   free(*self);
   *self = 0;
   return;
}