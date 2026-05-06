#include "list.h"
#include <stdlib.h>
//#include <stdHeader.h>
#include <assert.h>

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
	if(node_ptr == NULL)
		return NULL;

	node_ptr->data = data;
	node_ptr->next = NULL;
	node_ptr->previous = NULL;

	return node_ptr;
}

static Node * get_tail_ptr(const List list) //returnerar NULL om list är NULL annars så returnerar den pointern till tail
{
	//assert(list != NULL);//om list är tom även om node är tom

	if(list->next == NULL) //om det är tail returnera
		return list;
	
	else //om inte sista fortsätt till nästa
		return get_tail_ptr(list->next);
}

//Är listan tom?
//Returnerar 1 om listan är tom, annars 0
int is_empty(const List list)
{
	if(list == NULL)
		return 1;
	
	else
		return 0;
	
}

//Lägg till en nod först i listan
void add_first(List *list, const Data data)
{
	Node *node_ptr = create_list_node(data);
	if (node_ptr == NULL)
		return; //minne slut
	
	node_ptr->next = *list;
	node_ptr->previous = NULL;	

	if(*list != NULL)
		(*list)->previous = node_ptr;
	

	*list = node_ptr;
}

//lägg till nod sist i listan
void add_last(List *list, const Data data)
{
	Node *node_ptr = create_list_node(data);
	/*if (node_ptr == NULL)
		return; //minne slut*/

    if (*list == NULL)
    {
        node_ptr->next = NULL;
        node_ptr->previous = NULL;
        *list = node_ptr;
        return;
    }

    Node *tail = get_tail_ptr(*list);

    tail->next = node_ptr;
    node_ptr->previous = tail;
    node_ptr->next = NULL;
}

//Ta bort första noden i listan
//precondition: listan är inte tom (testa med assert)
void remove_first(List *list)
{
	if (*list == NULL)
        return;

    Node *to_delete = *list;
	Node *next = to_delete->next;

	*list = next;

	if(next != NULL)
		next->previous = NULL;

    free(to_delete);
}

//ta bort sista noden i listan
//precondition: listan är inte tom (testa med assert)
void remove_last(List *list)
{
	if (*list == NULL)
        return;

    Node *tail = get_tail_ptr(*list);

    // Om det bara finns en nod
    if (tail->previous == NULL)
    {
        free(tail);
        *list = NULL;
        return;
    }

    Node *prev = tail->previous;
    prev->next = NULL;

    free(tail);
}

//töm listan (ta bort alla noder ur listan)
//postcondition: Listan är tom, *list är NULL
void clear_list(List *list)
{
	//alla noder ska frigöras
	Node *current = *list;
    Node *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    *list = NULL;
}

//Skriv ut listan genom UART
/*void print_list(const List list)
{
	char sprintfBuffer[100];
	if(list == NULL)
		return;
	
	sprintf(sprintfBuffer, "\n\r%d", list->data);
	uarte_write(sprintfBuffer);	
		
	print_list(list->next);
}*/

//returnera första datat i listan
//precondition: listan är inte tom (testa med assert)
Data get_first_element(const List list) //TODO: assert istället för if-statement
{
	if (list == NULL)
		return NULL;
	
	return list->data;
}

//returnera sista datat i listan. 
//precondition: listan är inte tom (testa med assert)
Data get_last_element(const List list) //TODO: assert istället för if-statement
{
	struct node* tail = get_tail_ptr(list);

	if(tail == NULL)//fault
		return NULL;
	
	return tail->data;
}

//Returnera hur många noder som finns i listan
int number_of_nodes(const List list)
{
	if(list == NULL) //om list är tom även om node är tom
		return 0;
	
	return 1 + number_of_nodes(list->next);
}

//Sök efter data i listan, returnera 1 om datat finns, annars 0.
int search(const List list, const Data data)
{
	if(list == NULL) //om list är tom även om node är tom
		return 0;
	
	else if(list->data == data) //finns datan
		return 1;
	
	return search(list->next, data);//gå vidare
}

//Ta bort data ur listan (första förekomsten), returnera 0 om datat inte finns, annars 1
int remove_element(List *list, const Data data)
{
	if (*list == NULL)//om list är tom även om node är tom
        return 0;

    if ((*list)->data == data)//ta bort
    {
        Node *to_delete = *list;
        Node *next = to_delete->next;

        if(*list != NULL)
			(*list)->previous = NULL;

        free(to_delete);
        return 1;
    }
    return remove_element(&(*list)->next, data);//gå vidare rekursivt
}