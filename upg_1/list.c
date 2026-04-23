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
	Node *node_ptr = malloc(sizeof(Node));

	node_ptr->data = data;

	return node_ptr;
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
	Node *node_ptr = create_list_node(data);
	
	node_ptr->next = *list;
	node_ptr->previous = NULL;	

	if(*list != NULL)
	{
		(*list)->previous = node_ptr;
	}

	*list = node_ptr;
}

//lägg till nod sist i listan
void add_last(List *list, const Data data)
{
	Node *node_ptr = create_list_list(data);

	struct node* previous = get_tail_ptr(list);

	if(previous == NULL)
	{
		//fault
	}

	node_ptr->previous = previous; 
	node_ptr->next = NULL;

	if(*list != NULL)
	{
		(*list)->next = NULL;
	}
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
Data get_first_element(const List list) //TODO: assert istället för if-statement
{
	if (list == NULL)
	{
		return NULL;
	}
	return list->data;
}

//returnera sista datat i listan. 
//precondition: listan är inte tom (testa med assert)
Data get_last_element(const List list) //TODO: assert istället för if-statement
{
	struct node* tail = get_tail_ptr(list);

	if(tail == NULL)
	{
		//fault
		return NULL;
	}
	return tail->data;
}

//Returnera hur många noder som finns i listan
int number_of_nodes(const List list)
{
	if(list == NULL) //om list är tom även om node är tom
	{
		return 0;
	}
	return 1 + number_of_nodes(list->next);
}

//Sök efter data i listan, returnera 1 om datat finns, annars 0.
int search(const List list, const Data data)
{
	if(list == NULL) //om list är tom även om node är tom
	{
		return 0;
	}
	else if(list->data == data) //finns datan
	{
		return 1;
	}
	return search(list->next, data);//gå vidare
}

//Ta bort data ur listan (första förekomsten), returnera 0 om datat inte finns, annars 1
int remove_element(List *list, const Data data)
{
	if(*list == NULL) //om list är tom även om node är tom
	{
		return 0;
	}
	else if((*list)->data == data) //ta bort
	{
		Node* to_delete = *list;
		Node* next = to_delete->next;
		*list = next;
		if(next != NULL);
		{
			next->previous = to_delete->previous;
		}
		free(to_delete);
		return 1;
	}
	return search((*list)->next, data);//gå vidare
}

static Node * get_tail_ptr(const List list) //returnerar NULL om list är NULL annars så returnerar den pointern till tail
{
	if(list == NULL) //om list är tom även om node är tom
	{
		return NULL;
	}
	else if(list->next == NULL) //om det är tail returnera
	{
		return list;
	}
	else //om inte sista fortsätt till nästa
	{
		return get_tail_ptr(list->next);
	}
}