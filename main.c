/********************************************************************************
* main.c: Demonstration av strukt i C för lagring samt utskrift av persondata.
********************************************************************************/
#include "person.h"
#include <locale.h> 

/********************************************************************************
* main: Lagrar personuppgifter för tre personer och skriver ut i terminalen
*       samt till filen "persons.txt". Undantag görs om dynamiskt minne inte
*       kunde allokeras, då programmet avslutas med felkod 1.
********************************************************************************/
int main(void)
{
   setlocale(LC_ALL, "Swedish");

   person_t p1, p2, *p3;
   FILE* ostream = fopen("persons.txt", "w");

   person_init(&p1, "Erik Pihl", 31, "Lärdomsgatan 3", "Teacher", GENDER_MALE);
   person_init(&p2, "Donald Duck", 88, "1313 Webfoot Street", "Comical Character", GENDER_MALE);
   p3 = person_new("Bruce Wayne", 40, "Wayne Manor", "Batman", GENDER_MALE);

   if (!p3) return 1;

   p1.vptr->print(&p1, 0);
   p2.vptr->print(&p2, 0);
   p3->vptr->print(p3, 0);

   p1.vptr->print(&p1, ostream);
   p2.vptr->print(&p2, ostream);
   p3->vptr->print(p3, ostream);

   fclose(ostream);
   person_delete(&p3);

   printf("My name is %s!\n", p1.vptr->name(&p1));
   printf("I am %u years old!\n", p1.vptr->age(&p1));
   return 0;
}