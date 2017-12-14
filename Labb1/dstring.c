#include "dstring.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>


DString dstring_initialize(const char* str)
{
	// Precondition: str ar ej NULL - testas med en assert
	assert(str != NULL);

	DString strPtr;
	int stringLength = strlen(str);

	strPtr = (DString)malloc(sizeof(DString)*(stringLength + 1));
	if (strPtr != NULL)
	{
		strcpy(strPtr, str);
		assert(strcmp(str, strPtr) == 0);
		return strPtr;
	}
	else
	{
		printf("\n\tMemory could not be allocated.\n\t");
		return NULL;
	}
	/* Tips:
	   - Allokera (t.ex. med malloc) tillrackligt med minne for att fa plats med str,
         glom inte att det maste finnas plats f�r \0 (nolltermineringen).
         Glom inte att testa sa att allokeringen lyckades
	   - Det ra tillatet att anv�nda inbyggda strangfunktioner (som t.ex strcpy())
	   - Kom ihag att anvanda assert() */

	// Postcondition: returvardet innehaller samma strang som 'str'

}

int dstring_concatenate(DString* destination, DString source)
{
	// Precondition: destination ar ej NULL
	// Precondition: *destination ar ej NULL
	// Precondition: source ar ej NULL
    // Preconditions testas med asserts.
	assert(destination != NULL);
	assert(*destination != NULL);
	assert(source != NULL);


	// skapar en int-variabel som �r l�ngden f�r b�da str�ngarna + 1 f�r att f� plats med EN nullterminering
	int stringLength = strlen(*destination) + strlen(source) + 1;

	// omallokerar minne f�r att f� plats med b�da str�ngarna i *destination
	*destination = (DString)realloc(*destination, sizeof(char) * stringLength);
	if (*destination != NULL)
	{
		// om omallokeringen har lyckats s� l�ggs source till i *destination och 1 returneras f�r att visa att det lyckades
		strcat(*destination, source);
		assert(strlen(*destination) == stringLength - 1);
		return 1;
	}
	else
	{
		return 0;
	}
	/* Tips: 
	   - Tank p� att *destination redan ar en dynamiskt allokerad strang
	   - Tank p� att vi kommer att behova allokera mer minne for att fa plats med den har langre strangen.
         Minnet som *destination pekar pa behover utokas (realloc), hur stort ska det "nya" minnet bli?
         Glom inte att nolltermineringen maste fa plats.
         Nar du allokerar minne dynamiskt maste du alltid testa sa att allokeringen lyckades innan du
         borjar jobba med minnet.
       - Det ar tillatet att anvanda inbyggda funktioner (som t.ex. strcat()).
    */

	// Postcondition: *destination innehaller den gamla strangen ihopslagen med source
}

void dstring_truncate(DString* destination, unsigned int truncatedLength)
{
	// Precondition: destination ar ej NULL, *destination ar ej NULL - testa med asserts
	assert(destination != NULL);
	assert(*destination != NULL);

	// Om l�ngden p� destination �r kortare �n truncated length g�rs ingenting
	if (strlen(*destination) > truncatedLength)
	{
		// Omallokerar minne s� att bara truncatedLength + nullterminering f�r plats
		*destination = (DString*)realloc(*destination, sizeof(char) * (truncatedLength +1));
		if (*destination != NULL)
		{
			// L�gger till nullterminering efter str�ngen vi vill spara
			*(*destination + truncatedLength) = '\0';
		}
	}
	
//	if (str)
	/* Tips:
	   - Anvand realloc for att frigora det overflodiga minnet
         (realloc frigor forst minnet och allokerar sedan nytt for den angivna storleken)
	   - glom inte nolltermineringen */

	// Postcondition: *destination ar inte langre an 'truncatedLength' tecken
	assert(strlen(*destination) <= truncatedLength);
}

void dstring_print(DString str, FILE* textfile)
{
	// Precondition: textfile ar inte NULL - maste testas innan du forsoker skriva till filen
	assert(textfile != NULL);

	fwrite(str, sizeof(char),strlen(str),  textfile);

    /*Tank p� att filpekaren kopplas till filen innan funktionen anropas*/

	/* filpekaren far inte stangas, filen ska fungera som vanligt efter anropet */
}

void dstring_delete(DString* stringToDelete)
{
	// Precondition: stringToDelete ar inte NULL
	assert(*stringToDelete != NULL);
	*stringToDelete = NULL;
	free(*stringToDelete);
	assert(*stringToDelete == NULL);

	// Postcondition: *stringToDelete ar NULL och minnet ar frigjort
}
