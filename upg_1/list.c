#include "list.h"
#include <stdlib.h>



//Returnera en tom lista - funktionen är färdig
List create_empty_list(void)
{
    return NULL;
}

//Här skapas nya noder. Denna funktion är den enda som ska använda malloc.
//Denna funktion ska i sin tur bara kallas av add_first och add_last.
//Notera att den är static och inte finns med i interfacet
static Node * create_list_node(const Data data)
{
	//glöm inte att kolla så att malloc inte returnerade NULL

}

//Är listan tom?
//Returnerar 1 om listan är tom, annars 0
int is_empty(const List list)
{
	if(list == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//Lägg till en nod först i listan
void add_first(List *list, const Data data)
{

}

//lägg till nod sist i listan
void add_last(List *list, const Data data)
{

}

//Ta bort första noden i listan
//precondition: listan är inte tom (testa med assert)
void remove_first(List *list)
{

}

//ta bort sista noden i listan
//precondition: listan är inte tom (testa med assert)
void remove_last(List *list)
{

}

//töm listan (ta bort alla noder ur listan)
//postcondition: Listan är tom, *list är NULL
void clear_list(List *list)
{
	//alla noder ska frigöras
}

//Skriv ut listan genom UART
void print_list(const List list)
{

}

//returnera första datat i listan
//precondition: listan är inte tom (testa med assert)
Data get_first_element(const List list)
{

}

//returnera sista datat i listan. 
//precondition: listan är inte tom (testa med assert)
Data get_last_element(const List list)
{

}

//Returnera hur många noder som finns i listan
int number_of_nodes(const List list)
{

}

//Sök efter data i listan, returnera 1 om datat finns, annars 0.
int search(const List list, const Data data)
{
	
}

//Ta bort data ur listan (första förekomsten), returnera 0 om datat inte finns, annars 1
int remove_element(List *list, const Data data)
{

}
