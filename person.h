/********************************************************************************
* person.h: Innehåller funktionalitet för lagring samt utskrift av persondata
*           via strukten person samt associerade funktioner.
********************************************************************************/
#ifndef PERSON_H_
#define PERSON_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>  /* Innehåller funktionalitet för utskrift och inmatning. */
#include <stdlib.h> /* Innehåller funktionalitet för dynamisk minnesallokering. */

/********************************************************************************
* gender: Enumeration för val av kön.
********************************************************************************/
typedef enum gender
{
   GENDER_MALE,   /* Man. */
   GENDER_FEMALE, /* Kvinna. */
   GENDER_OTHER,  /* Övrigt. */
   GENDER_NONE    /* Ospecificerat. */
} gender_t;

/********************************************************************************
* person: Strukt för lagring samt utskrift av persondata.
********************************************************************************/
typedef struct person
{
   struct person_mem* mem;           /* Pekare till variabler innehållande persondata. */
   const struct person_vtable* vptr; /* Pekare till vtable innehållande funktionspekare. */
} person_t, *person_ptr_t;

/********************************************************************************
* person_vtable: Strukt för vtable (virtuell tabell) innehållande adresser till 
*                associerade funktioner för strukten person.
********************************************************************************/
typedef struct person_vtable
{
   /********************************************************************************
   * print: Skriver ut lagrad persondata via angiven utström, där standardutenheten
   *        stdout används som default för utskrift i terminalen.
   *
   *        - self   : Pekare till objektet som lagrar persondatan.
   *        - ostream: Pekare till angiven utström (default = stdout).
   ********************************************************************************/
   void (*print)(const struct person* self,
                 FILE* ostream);

   /********************************************************************************
   * gender_str: Returnerar personens kön på textform.
   *
   *             - self: Pekare till objektet som lagrar persondatan.
   ********************************************************************************/
   const char* (*gender_str)(const struct person* self);

   /********************************************************************************
   * name: Returnerar personens namn.
   *
   *       - self: Pekare till objektet som lagrar persondatan.
   ********************************************************************************/
   const char* (*name)(const struct person* self);

   /********************************************************************************
   * age: Returnerar personens ålder.
   *
   *      - self: Pekare till objektet som lagrar persondatan.
   ********************************************************************************/
   unsigned int (*age)(const struct person* self);

   /********************************************************************************
   * address: Returnerar personens hemadress.
   *
   *          - self: Pekare till objektet som lagrar persondatan.
   ********************************************************************************/
   const char* (*address)(const struct person* self);

   /********************************************************************************
   * occupation: Returnerar personens yrke.
   *
   *             - self: Pekare till objektet som lagrar persondatan.
   ********************************************************************************/
   const char* (*occupation)(const struct person* self);

   /********************************************************************************
   * gender: Returnerar personens kön som en enumerator av enumerationen gender.
   *
   *         - self: Pekare till objektet som lagrar persondatan.
   ********************************************************************************/
   enum gender (*gender)(const struct person* self);

   /********************************************************************************
   * clear: Nollställer persondata lagrat av angivet person-objekt.
   *
   *        - self: Pekare till objektet som ska nollställas.
   ********************************************************************************/
   void (*clear)(struct person* self);
} person_vtable_t, *person_vtable_ptr_t;

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
                 const enum gender gender);

/********************************************************************************
* person_clear: Nollställer persondata lagrat av angivet person-objekt.
* 
*               - self: Pekare till objektet som ska nollställas.
********************************************************************************/
void person_clear(struct person* self);

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
                          const enum gender gender);

/********************************************************************************
* person_delete: Raderar angivet person-objekt genom att frigöra dynamiskt 
*                allokerat minne för denna och sätter motsvarande pekare till null. 
*                För att möjliggöra detta passeras adressen till den pekare som 
*                pekar på det dynamiskt allokerade minnet.
*
*                - self: Adressen till den pekare som pekar på objektet som
*                        som ska raderas.
********************************************************************************/
void person_delete(struct person** self);

/********************************************************************************
* person_print: Skriver ut lagrad persondata via angiven utström, där 
*               standardutenheten stdout används som default för utskrift
*               i terminalen.
*
*               - self   : Pekare till objektet som lagrar persondatan.
*               - ostream: Pekare till angiven utström (default = stdout).
********************************************************************************/
void person_print(const struct person* self,
                  FILE* ostream);

/********************************************************************************
* person_gender_str: Returnerar personens kön på textform.
*
*                    - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
const char* person_gender_str(const struct person* self);

/********************************************************************************
* person_name: Returnerar personens namn.
*
*              - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
const char* person_name(const struct person* self);

/********************************************************************************
* person_age: Returnerar personens ålder.
*
*             - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
unsigned int person_age(const struct person* self);

/********************************************************************************
* person_address: Returnerar personens hemadress.
*
*                 - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
const char* person_address(const struct person* self);

/********************************************************************************
* person_occupation: Returnerar personens yrke.
*
*                    - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
const char* person_occupation(const struct person* self);

/********************************************************************************
* person_gender: Returnerar personens kön som en enumerator av enumeration 
*                gender, alltså GENDER_MALE, GENDER_FEMALE, GENDER_OTHER eller
*                GENDER_NONE.
*
*                - self: Pekare till objektet som lagrar persondatan.
********************************************************************************/
enum gender person_gender(const struct person* self);

#endif /* PERSON_H_ */