/**
 * @file social.c
 * @brief Implementation file for the Social Network program.
 *
 * This file contains the implementations of functions declared in the "social.h" header file.
 * The program simulates a social network where nodes represent individuals, groups, businesses,
 * or organizations. Each node has unique attributes, and functionalities such as node creation,
 * deletion, searching, content posting, and network analysis are implemented.
 *
 * @details
 * The functions defined in this file interact with global linked lists and manage various types
 * of nodes. The nodes are linked based on their types and relationships, forming a comprehensive
 * social network. The actual structure and function prototypes are defined in "social.h".
 *
 * @note
 * The program uses global linked lists to store nodes of different types, and these lists are
 * declared as extern in "social.h". The memory management, creation, and manipulation of nodes
 * are implemented in this file.
 */

#include "social.h"

// Globally declared standard limmits

int name_limit = 100;
int content_limit = 300;

// Global linked lists of all member types

struct individual *all_Individuals = NULL;
struct business *all_business = NULL;
struct organisation *all_Organisation = NULL;
struct group *all_Group = NULL;

// Throwaway character to catch new line characters
char throwaway;

// Function to take input for a name
char *name_input()
{

    int limit = name_limit;

    // Creating the name string
    char *name = (char *)malloc(name_limit * sizeof(char));

    // Checking for intial memory allocation success
    if (name == NULL)
    {
        printf("Memory allocation failed. Please try again\n");
        return NULL;
    }

    int size = 0;

    while (1)
    {
        // Checking array is full and reallocating if necessary
        if (size == limit)
        {
            limit *= 2;
            name = (char *)realloc(name, limit * sizeof(char)); // Doubling the previous size

            if (name == NULL)
            {
                printf("Memory allocation failed as name too big. PLease try again\n"); // Checking if Memory allocation was successful
                return NULL;
            }
        }

        // Taking input from the user
        char c;
        scanf("%c", &c);

        // If end of the name, terminate.
        if (c == '\n')
        {
            name[size] = '\0'; // Name ends, so finishing the string
            break;
        }
        else
        {
            name[size] = c; // Character gets added to the name string
        }

        size++;
    }

    return name; // Pointer(array) to the name is returned
}

// Function to take input fro a date
struct tm *date_input()
{
    // Creating a new structure
    struct tm *temp_date = (struct tm *)malloc(sizeof(struct tm));

    // Checking for successfull allocation of memory
    if (temp_date == NULL)
    {
        printf("Memory allocation failed!!. Please try again\n");
        return NULL;
    }

    // Taking input from the user
    if (scanf("%d/%d/%d%c", &(temp_date->tm_mday), &(temp_date->tm_mon), &(temp_date->tm_year), &throwaway) != 4)
    {
        // Date entered is of invalid format
        printf("Invalid date format.\n");

        temp_date->tm_mday = -1;
        temp_date->tm_mon = -1;
        temp_date->tm_year = -1;

        return temp_date;
    }

    return temp_date; // Returning the pointer of the created date structure
}

// Function to take the input for content
char *content_input()
{
    // Initialzing a new char pointer(array)
    char *content = (char *)malloc(content_limit * sizeof(char));

    // Checking for successfull memory allocation
    if (content == NULL)
    {
        printf("Memory allocation failed. Please try again\n");
        return NULL;
    }

    int size = 0;              // Tracks the size of the string
    int limit = content_limit; // Determines the maximum size of the array

    while (1)
    {

        // Checking array is full and reallocating if necessary
        if (size == limit)
        {
            limit *= 2;
            content = (char *)realloc(content, limit * sizeof(char)); // Doubling the array size

            if (content == NULL) // Checking if reallocation was successful
            {
                printf("Memory allocation failed as content too big. PLease try again\n");
                free(content);
                return NULL;
            }
        }

        // Taking input from the user
        char c;
        scanf("%c", &c);

        // If end of the content, terminate.
        if (c == '\n')
        {
            content[size] = '\0';
            break;
        }
        else
        {
            content[size] = c;
        }

        size++;
    }

    return content; // returning the pointer(array)
}

// Function to take input for a birthday
struct tm *birthday_input()
{

    // Taking data from the user
    printf("Will you input a birthday?? (Y/N)\n");
    char c;
    scanf("%c%c", &c, &throwaway);

    while (c != 'Y' && c != 'y' && c != 'n' && c != 'N')
    {
        printf("Error!! PLease input either Y (yes) or N (no)\n");
        scanf("%c%c", &c, &throwaway);
    }

    // Take birthday if yes
    if (c == 'Y' || c == 'y')
    {

        printf("Enter your birthday\n");
        struct tm *temp = date_input();
        return temp;
    }
    else
    {

        struct tm *temp_date;

        temp_date->tm_mday = -1;
        temp_date->tm_mon = -1;
        temp_date->tm_year = -1;

        return temp_date;
    }
}

// Function to print a given node
void print_node(void *node, char type[])
{

    if (node == NULL) // Empty node check
        return;

    if (strcmp(type, "Individual") == 0) // If the given node is of Individual type
    {
        struct individual *temp_ind = (struct individual *)node; // Creating a temporary (typecasted) node to work with

        // Printing the attributes

        printf("\nName of the %s :- %s\n", type, temp_ind->name);
        printf("\nID- %d\n", temp_ind->id);
        printf("\nCreation date :- %d/%d/%d\n", temp_ind->creation->tm_mday, temp_ind->creation->tm_mon, temp_ind->creation->tm_year);
        printf("145\n");
        printf("\nContent :- \n%s\n", temp_ind->content);

        // Checking if a valid birthday exists
        if (temp_ind->birthday->tm_mday == -1)
            printf("\nHas no valid birthday\n\n");
        else
            printf("Birthday :- %d/%d/%d\n\n", temp_ind->birthday->tm_mday, temp_ind->birthday->tm_mon, temp_ind->birthday->tm_year);
    }
    else if (strcmp(type, "Business") == 0) // If the given node is of Business type
    {
        struct business *temp_bus = (struct business *)node; // Temporary pointer to access the node data

        // Printing the attributes

        printf("\nName of the %s :- %s\n", type, temp_bus->name);
        printf("\nID- %d\n", temp_bus->id);
        printf("\nCreation date :- %d/%d/%d\n", temp_bus->creation->tm_mday, temp_bus->creation->tm_mon, temp_bus->creation->tm_year);
        printf("\nContent :-\n%s\n", temp_bus->content);

        printf("\nThe co-ordinates of the business are (%.3lf, %.3lf) \n", temp_bus->x_cord, temp_bus->y_cord);

        // Printing the owners and the customers
        if (temp_bus->owners != NULL)
        {
            struct linked_individual *temp = temp_bus->owners;

            int num = 1; // Count of nodes
            printf("\nList of owner(s)\n\n");

            while (temp != NULL)
            {
                printf("%d) %s\n", num++, temp->node_ind->name); // Printing the owner's names

                temp = temp->next;
            }
        }
        else
            printf("\nThere are no owners\n");

        if (temp_bus->customers != NULL)
        {
            struct linked_individual *temp = temp_bus->customers;

            int num = 1; // Count of nodes
            printf("\nList of customer(s)\n");

            while (temp != NULL)
            {
                printf("%d) %s\n", num++, temp->node_ind->name); // Printing the customer's name

                temp = temp->next;
            }
        }
        else
            printf("\nThere are no customers\n");
    }
    else if (strcmp(type, "Organisation") == 0) // If the given node is of Organisation type
    {
        struct organisation *temp_org = (struct organisation *)node; // Temporary pointer to access the node data

        // Printing the attributes

        printf("Name of the %s :- %s\n", type, temp_org->name);
        printf("ID- %d\n", temp_org->id);
        printf("Creation date :- %d/%d/%d\n", temp_org->creation->tm_mday, temp_org->creation->tm_mon, temp_org->creation->tm_year);
        printf("Content :-\n%s\n", temp_org->content);

        printf("The co-ordinates of the organisation are (%.3lf, %.3lf) \n", temp_org->x_cord, temp_org->y_cord);

        // Printing the Individual members

        if (temp_org->orgmember_head != NULL)
        {
            struct linked_individual *temp = temp_org->orgmember_head;

            int num = 1; // Count of nodes
            printf("\nList of Individual member(s)\n");

            while (temp != NULL)
            {
                printf("%d) %s\n", num++, temp->node_ind->name); // Printing the names

                temp = temp->next;
            }
        }
        else
            printf("\nThere are no Individual members\n");
    }
    else if (strcmp(type, "Group") == 0) // If the given node is of Group type
    {
        struct group *temp_grp = (struct group *)node; // Temporary pointer to access the node data

        // Printing the attributes

        printf("\nName of the %s :- %s\n", type, temp_grp->name);
        printf("\nID- %d\n", temp_grp->id);
        printf("\nCreation date :- %d/%d/%d\n", temp_grp->creation->tm_mday, temp_grp->creation->tm_mon, temp_grp->creation->tm_year);
        printf("\nContent :-\n%s\n", temp_grp->content);

        printf("The co-ordinates of the group are (%.3lf, %.3lf) \n", temp_grp->x_cord, temp_grp->y_cord);

        // Printing the Individual and Business members

        if (temp_grp->grpmember_head != NULL)
        {
            struct linked_individual *temp = temp_grp->grpmember_head;

            int num = 1; // Counts of nodes
            printf("\nList of individual member(s)\n");

            while (temp != NULL)
            {
                printf("%d) %s\n", num++, temp->node_ind->name); // Printing the Individual's name

                temp = temp->next;
            }
        }
        else
            printf("\nThere are no individual members\n\n");

        if (temp_grp->businessmember_head != NULL)
        {
            struct linked_business *temp2 = temp_grp->businessmember_head;

            int num = 1; // Count of nodes
            printf("List of business member(s)\n\n");

            while (temp2 != NULL)
            {
                printf("%d) %s\n", num++, temp2->node_bus->name); // Printing the Businesse's name

                temp2 = temp2->next;
            }
        }
        else
            printf("\nThere are no business members\n");
    }

    printf("\n*******************\n");
}

// Function search for a node with the given search_parameter
void search(char search_parameter[])
{

    int flag = 1;

    // Temporary iterators(pointers) to travel over the nodes

    struct individual *temp_ind = all_Individuals;
    struct business *temp_bus = all_business;
    struct organisation *temp_org = all_Organisation;
    struct group *temp_grp = all_Group;

    while (temp_ind != NULL)
    {

        if (!(strcmp(search_parameter, temp_ind->name)))
        {

            flag = 0;

            printf("\nThe node is:- \n\n");
            print_node(temp_ind, "Individual");
        }
        else if (!(strcmp(search_parameter, "Individual")))
        {

            if (flag)
            {
                flag = 0;
                printf("\nThe Individual node(s) are:-\n");
            }

            print_node(temp_ind, "Individual");
        }

        temp_ind = temp_ind->next;
    }
    while (temp_bus != NULL)
    {

        if (!(strcmp(search_parameter, temp_bus->name)))
        {

            flag = 0;

            printf("\nThe node is:- \n\n");
            print_node(temp_bus, "Business");
        }
        else if (!(strcmp(search_parameter, "Business")))
        {

            if (flag)
            {
                flag = 0;
                printf("\nThe Business node(s) are:-\n");
            }

            print_node(temp_bus, "Business");
        }

        temp_bus = temp_bus->next;
    }
    while (temp_org != NULL)
    {

        if (!(strcmp(search_parameter, temp_org->name)))
        {

            flag = 0;

            printf("\nThe node is:- \n\n");
            print_node(temp_org, "Organisation");
        }
        else if (!(strcmp(search_parameter, "Organisation")))
        {

            if (flag)
            {
                flag = 0;
                printf("\nThe Organisation node(s) are:-\n");
            }

            print_node(temp_org, "Organisation");
        }

        temp_org = temp_org->next;
    }
    while (temp_grp != NULL)
    {

        if (!(strcmp(search_parameter, temp_grp->name)))
        {

            flag = 0;

            printf("\nThe node is:- \n\n");
            print_node(temp_grp, "Group");
        }
        else if (!(strcmp(search_parameter, "Group")))
        {

            if (flag)
            {
                flag = 0;
                printf("\nThe Group node(s) are:-\n");
            }

            print_node(temp_grp, "Group");
        }

        temp_grp = temp_grp->next;
    }

    if (flag)
        printf("No match found\n");
}

// Function to search by id
void *search_by_id(int id)
{
    int flag = 1;

    // Temporary iterators over the global linked list to search

    struct individual *temp_ind = all_Individuals;
    struct business *temp_bus = all_business;
    struct organisation *temp_org = all_Organisation;
    struct group *temp_grp = all_Group;

    while (temp_ind != NULL)
    {
        if (temp_ind->id == id)
            return (struct individual *)temp_ind;

        temp_ind = temp_ind->next;
    }
    while (temp_bus != NULL)
    {
        if (temp_bus->id == id)
            return (struct business *)temp_bus;

        temp_bus = temp_bus->next;
    }
    while (temp_org != NULL)
    {
        if (temp_org->id == id)
            return (struct organsiation *)temp_org;

        temp_org = temp_org->next;
    }
    while (temp_grp != NULL)
    {
        if (temp_grp->id == id)
            return (struct group *)temp_grp;

        temp_grp = temp_grp->next;
    }

    if (flag)                               // There is no match
    {
        printf("No such node exists\n");
        return NULL;
    }
}

// Function to search by birthday
void search_by_birthday(struct tm *search_date)
{
    // A individual iterator since only individuals have birthdays
    struct individual *temp = all_Individuals;

    int flag = 1;
    while (temp != NULL)
    {

        if (temp->birthday->tm_mday == search_date->tm_mday && temp->birthday->tm_mon == search_date->tm_mon                        // Checking if the dates match and 
            && temp->birthday->tm_year == search_date->tm_year && search_date->tm_mday != -1 && temp->birthday->tm_mday != -1)      // neither of them are invalid
        {
            if (flag)
            {
                printf("The node(s) are :- \n\n");
                flag = 0;
            }

            print_node(temp, "Individual");                                                             // Printing all the nodes who match
        }

        temp = temp->next;                                                                              // Iterating through the lsilist
    }

    if (flag)
        printf("There are no nodes with the given birthday\n\n");                                       // If there are no matches 
}

// Function to print the content of a node
void print_content(int id)
{
    int flag = 1;

    // Temporary iterators to search

    struct individual *temp_ind = all_Individuals;
    struct business *temp_bus = all_business;
    struct organisation *temp_org = all_Organisation;
    struct group *temp_grp = all_Group;

    while (temp_ind != NULL)                                                        // Iterting over all the individuals
    {
        if (temp_ind->id == id)                                                     // If a match is found
        {
            printf("The content of the node with ID %d is:- \n", id);               // Printing the name and content
            printf("\n%s\n\n", temp_ind->content);                                  // of the node found

            return;
        }

        temp_ind = temp_ind->next;                                                  // Iterating over all the individuals
    }
    while (temp_bus != NULL)
    {
        if (temp_bus->id == id)                                                     // If a match is found
        {
            printf("The content of the node with ID %d is:- \n", id);               // Printing the name and content
            printf("\n%s\n\n", temp_bus->content);                                  // of the node found

            return;
        }

        temp_bus = temp_bus->next;                                                  // Iterating over all the bsuinesses
    }
    while (temp_org != NULL)
    {
        if (temp_org->id == id)                                                     // If a match is found
        {
            printf("The content of the node with ID %d is:- \n", id);               // Printing the name and content
            printf("\n%s\n\n", temp_org->content);                                  // of the node found

            return;
        }

        temp_org = temp_org->next;                                                  // Iterating over all the organisations
    }
    while (temp_grp != NULL)
    {
        if (temp_grp->id == id)                                                     // If a match is found
        {
            printf("The content of the node with ID %d is:- \n\n", id);             // Printing the name and content
            printf("\n%s\n\n", temp_grp->content);                                  // of the node found

            return;
        }

        temp_grp = temp_grp->next;                                                  // Iterating over all the organisations
    }

    printf("No such node exists\n");                                                // Checking if there is no node matching 
}

// Function to search nodes to link them
void *search_to_link(char search_parameter[], char type[])
{

    // Temporary iterators to search

    struct individual *temp_ind = all_Individuals;
    struct business *temp_bus = all_business;

    while (temp_ind != NULL && !(strcmp(type, "Individual")))                        // If type is of Individual
    {
        if (!(strcmp(search_parameter, temp_ind->name)))                             // Checking a match of the name
            return (struct individual *)temp_ind;

        temp_ind = temp_ind->next;                                                   // Iterating over the global list
    }

    while (temp_bus != NULL && !(strcmp(type, "Business")))                          // If the type is Business
    {
        if (!(strcmp(search_parameter, temp_bus->name)))                             // Chekcing for a match of the name
            return (struct business *)temp_bus;

        temp_bus = temp_bus->next;                                                   // Iterating over the global list
    }

    return NULL;                                                                     // NULL is returned if a node isn't found
}

// Function to create a new  node
void new_node(char type[])
{
    if (!(strcmp(type, "Individual")))
    {
        // Allocation memory for a new Individual type node
        struct individual *ind_node = (struct individual *)malloc(sizeof(struct individual));

        // Checking if allocation was successful
        if (ind_node == NULL)
        {
            printf("Memory allocation failed. Please try again\n");
        }

        // Setting the type to Individual
        strcpy(ind_node->type, "Individual");

        // Taking inputs for the common attributes

        printf("\nEnter the ID of the individual\n");
        scanf("%d%c", &(ind_node->id), &throwaway);

        printf("Enter the name\n");
        ind_node->name = name_input();

        printf("Enter the creation date in the format DD/MM/YYYY: \n");
        ind_node->creation = date_input();

        printf("Enter the content of the Individual\n");
        ind_node->content = content_input();

        // Input for unique attribute
        ind_node->birthday = birthday_input();

        // Initializing the back pointers to NULL

        ind_node->back_bus = NULL;
        ind_node->back_grp = NULL;
        ind_node->back_org = NULL;

        // Linking the created node to the global list
        ind_node->next = all_Individuals;
        all_Individuals = ind_node;

        printf("******** Node successfully created ********\n");
    }
    else if (!(strcmp(type, "Business")))
    {
        struct business *bus_node = (struct business *)malloc(sizeof(struct business));

        // Checking if allocation was successful
        if (bus_node == NULL)
        {
            printf("Memory allocation failed. Please try again\n");
        }

        // Setting the type to business
        strcpy(bus_node->type, "Business");

        // Taking inputs for the common attributes

        printf("\nEnter the ID of the business\n");
        scanf("%d%c", &(bus_node->id), &throwaway);

        printf("Enter the name of the business\n");
        bus_node->name = name_input("Business");

        printf("Enter the creation date in the format DD/MM/YYYY\n");
        bus_node->creation = date_input();

        printf("Enter the content of the business\n");
        bus_node->content = content_input();

        // Initializing the back pointer to NULL'
        bus_node->back_grp = NULL;

        // Inputs for the unique attributes

        printf("\nEnter the X Co-ordinate\n");
        scanf("%lf%c", &(bus_node->x_cord), &throwaway);

        printf("Enter the Y Co-ordinate\n");
        scanf("%lf%c", &(bus_node->y_cord), &throwaway);


        char check;                                             // Character used to check if there are any members

        bus_node->owners = NULL;                                // Initializing the owners list to NULL
        bus_node->customers = NULL;                             // Initializing the customers list to NULL

        printf("\nDo you want to enter any owner(s) (Y/N)\n");
        scanf("%c%c", &check, &throwaway);                      // Taking input from the user

        while (check != 'Y' && check != 'y' && check != 'N' && check != 'n')            // Checking whether a correct character has been used or not
        {
            printf("Error!! Please enter the correct characer (Y/N)\n");                // Iterating till the correct character is used
            scanf("%c%c", &check, &throwaway);
        }

        if (check == 'Y' || check == 'y')                                               // If the user has given a yes
        {
            while (check == 'Y' || check == 'y')                                        // Loop to add new owners
            {
                printf("Enter the name of owner\n");

                char *customer_name = name_input();

                struct individual *temp_ind = (struct individual *)search_to_link(customer_name, "Individual");     // Finding the owner name

                if (temp_ind == NULL)
                    printf("Such a name doesn't exist\n");
                else
                {
                    // Creating a new linked individual* node to store the pointer of the new owner found
                    struct linked_individual *new_owner = (struct linked_individual *)malloc(sizeof(struct linked_individual));

                    // Assigning the business as a back pointer to the temp_ind Individual
                    struct linked_business *bus_back = (struct linked_business *)malloc(sizeof(struct linked_business));
                    bus_back->node_bus = bus_node;
                    bus_back->next = temp_ind->back_bus;
                    temp_ind->back_bus = bus_back;

                    // Now assigning this Individual node's pointer to the business
                    new_owner->node_ind = temp_ind;
                    new_owner->next = bus_node->owners;
                    bus_node->owners = new_owner;

                    printf("Successfully added!!\n");
                }

                printf(" Do you want to enter any other names (Y/N) ??\n");             // Asking if there are any other names
                scanf("%c%c", &check, &throwaway);

                while (check != 'Y' && check != 'y' && check != 'N' && check != 'n')    // Iterating till the correct name ahs been entered
                {
                    printf("Error!! Please enter the correct characer (Y/N)\n");
                    scanf("%c ", &check);
                }
            }
        }

        printf("Do you want to enter any customer(s) (Y/N)\n");                          // Doing the same as owners for any customers
        scanf("%c%c", &check, &throwaway);

        while (check != 'Y' && check != 'y' && check != 'N' && check != 'n')             // Iterating till a cirrect character has been entered
        {
            printf("Error!! Please enter the correct characer (Y/N)\n");
            scanf("%c%c", &check, &throwaway);
        }

        if (check == 'Y' || check == 'y')                                                // If the ser has given a yes
        {
            while (check == 'Y' || check == 'y')                                         // Loop to add new customers
            {   
                printf("Enter the name of customer\n");

                char *customer_name = name_input();

                struct individual *temp_ind1 = (struct individual *)search_to_link(customer_name, "Individual");    // FInds the required node

                if (temp_ind1 == NULL)
                    printf("Such a name doesn't exist\n");
                else
                {
                    // Creating a new linked_individual* node to store the pointer to the required customer individual node
                    struct linked_individual *new_customer = (struct linked_individual *)malloc(sizeof(struct linked_individual));

                    // Assgning the business as a back pointer to the temp_ind1 Individual
                    struct linked_business *business_back = (struct linked_business *)malloc(sizeof(struct linked_business));
                    business_back->node_bus = bus_node;
                    business_back->next = temp_ind1->back_bus;
                    temp_ind1->back_bus = business_back;

                    // Now assigning the individual node to the customers list
                    new_customer->node_ind = temp_ind1;
                    new_customer->next = bus_node->owners;
                    bus_node->owners = new_customer;

                    printf("Successfully added!!\n");
                }

                printf("Do you want to enter any other names (Y/N) ??\n");                          // CHecking for any other customers
                scanf("%c%c", &check, &throwaway);

                while (check != 'Y' && check != 'y' && check != 'N' && check != 'n')                // Iterating till a correct character ahs been entered
                {
                    printf("Error!! Please enter the correct characer (Y/N)\n");
                    scanf("%c%c", &check, &throwaway);
                }
            }
        }

        // Linking the created node to the global linked list

        bus_node->next = all_business;
        all_business = bus_node;

        printf("******** Node successfully created ********\n");                                    // Indicates success of process
    }
    else if (!(strcmp(type, "Organisation")))
    {
        struct organisation *org_node = (struct organisation *)malloc(sizeof(struct organisation));

        // Checking if allocation was successful
        if (org_node == NULL)
        {
            printf("Memory allocation failed. Please try again\n");
        }

        // Setting the type to organisation
        strcpy(org_node->type, "Organisation");

        // Taking inputs for the common attributes

        printf("\nEnter the ID of the Organisation\n");
        scanf("%d%c", &(org_node->id), &throwaway);

        printf("Enter the name of the organisation\n");
        org_node->name = name_input("Organisation");

        printf("Enter the creation date of the organisation\n");
        org_node->creation = date_input();

        printf("Enter the content of the organisation\n");
        org_node->content = content_input("Organisation");

        // Inputs for the unique attributes

        printf("\nEnter the X Co-ordinate\n");
        scanf("%lf%c", &(org_node->x_cord), &throwaway);

        printf("Enter the Y Co-ordinate\n");
        scanf("%lf%c", &(org_node->y_cord), &throwaway);

        // Intializing the members list to NULL
        org_node->orgmember_head = NULL;

        char check;                                                             // Used to check for inputs from the user regarding members

        printf("Do you want to enter any member(s) (Y/N)\n");                   // Taking input from the user
        scanf("%c%c", &check, &throwaway);

        while (check != 'Y' && check != 'y' && check != 'N' && check != 'n')    // Iterating till a correct answer has been given
        {
            printf("Error!! Please enter the correct characer (Y/N)\n");
            scanf("%c%c", &check, &throwaway);
        }

        if (check == 'Y' || check == 'y')                                       // If the user inputs yes
        {
            while (check == 'Y' || check == 'y')                                // Loop to add more members
            {
                printf("Enter the name of member\n");

                char *member_name = name_input();

                struct individual *temp_ind = (struct individual *)search_to_link(member_name, "Individual");

                if (temp_ind == NULL)
                    printf("Such a name doesn't exist\n");
                else
                {
                    // Allocating memoruy for a new member
                    struct linked_individual *new_member = (struct linked_individual *)malloc(sizeof(struct linked_individual));

                    // Assigning the organisation as a back pointer to the individual
                    struct linked_organisation *org_back = (struct linked_organisation *)malloc(sizeof(struct linked_organisation));
                    org_back->node_org = org_node;
                    org_back->next = temp_ind->back_org;
                    temp_ind->back_org = org_back;

                    // Now assiging the indivudal to the organisation
                    new_member->node_ind = temp_ind;
                    new_member->next = org_node->orgmember_head;
                    org_node->orgmember_head = new_member;

                    printf("Successfully added!!\n");
                }

                printf(" Do you want to enter any other names??\n");                        // Asking for any more individuals
                scanf("%c%c", &check, &throwaway);

                while (check != 'Y' && check != 'y' && check != 'N' && check != 'n')        // Iterating till correct answer given
                {
                    printf("Error!! Please enter the correct characer (Y/N)\n");
                    scanf("%c%c", &check, &throwaway);
                }
            }
        }

        // Linking the created node to the global list

        org_node->next = all_Organisation;
        all_Organisation = org_node;

        printf("******** Node successfully created ********\n");                            // Successfully created!!!
    }
    else if (!(strcmp(type, "Group")))
    {
        // Allocating memory for a new node
        struct group *grp_node = (struct group *)malloc(sizeof(struct group));

        // Checking if allocation was successful
        if (grp_node == NULL)
        {
            printf("Memory allocation failed. Please try again\n");
        }

        // Setting the type to group
        strcpy(grp_node->type, "Group");

        // Taking inputs for the common attributes

        printf("\nEnter the ID of the Group\n");
        scanf("%d%c", &(grp_node->id), &throwaway);

        printf("Enter the name of the group\n");
        grp_node->name = name_input("Group");

        printf("Enter the creation date of the group\n");
        grp_node->creation = date_input();

        printf("Enter the content of the group");
        grp_node->content = content_input("Group");

        // Inputs for the unique attributes

        printf("\nEnter the X Co-ordinate\n");
        scanf("%lf%c", &(grp_node->x_cord), &throwaway);

        printf("Enter the Y Co-ordinate\n");
        scanf("%lf%c", &(grp_node->y_cord), &throwaway);

        // Initializing the members lists to NULL
        grp_node->businessmember_head = NULL;
        grp_node->grpmember_head = NULL;

        char check;

        printf("Do you want to enter any individual member(s) (Y/N)\n");            // Asking if there are any individual members
        scanf("%c%c", &check, &throwaway);

        while (check != 'Y' && check != 'y' && check != 'N' && check != 'n')        // Iterating till a correct answer is given
        {
            printf("Error!! Please enter the correct characer (Y/N)\n");
            scanf("%c%c", &check, &throwaway);
        }

        if (check == 'Y' || check == 'y')                                           // If the user inputs yes
        {   
            while (check == 'Y' || check == 'y')                                    // Loop to add more members
            {
                printf("Enter the name of individual member\n");                    

                char *member_name = name_input();

                struct individual *temp_ind = (struct individual *)search_to_link(member_name, "Individual");

                if (temp_ind == NULL)
                    printf("Such a name doesn't exist\n");
                else
                {
                    // Alloating memory for a new node
                    struct linked_individual *new_member = (struct linked_individual *)malloc(sizeof(struct linked_individual));

                    // Assigning this group as a back pointer to the individual
                    struct linked_group *grp_back = (struct linked_group *)malloc(sizeof(struct linked_group));
                    grp_back->node_grp = grp_node;
                    grp_back->next = temp_ind->back_grp;
                    temp_ind->back_grp = grp_back;

                    // Now assiging the individual node to the group
                    new_member->node_ind = temp_ind;
                    new_member->next = grp_node->grpmember_head;
                    grp_node->grpmember_head = new_member;

                    printf("Successfully added!!\n");
                }

                printf("Do you want to enter any other names (Y/N) ??\n");                      // Checking if there are any more nodes
                scanf("%c%c", &check, &throwaway);

                while (check != 'Y' && check != 'y' && check != 'N' && check != 'n')            // Iterating till correct answer is given
                {   
                    printf("Error!! Please enter the correct characer (Y/N)\n");
                    scanf("%c%c", &check, &throwaway);
                }
            }
        }

        printf("\nDo you want to enter any business member(s) (Y/N)\n");                        // ASKing for any business members
        scanf("%c%c", &check, &throwaway);

        while (check != 'Y' && check != 'y' && check != 'N' && check != 'n')                    // Iterating till a correct character is given
        {
            printf("Error!! Please enter the correct characer (Y/N)\n");
            scanf("%c%c", &check, &throwaway);
        }

        if (check == 'Y' || check == 'y')                                                       // If the user inputs yes
        {
            while (check == 'Y' || check == 'y')                                                // Loop to add more businesses
            {
                printf("Enter the name of member\n");

                char *member_name = name_input();

                struct business *temp_bus = (struct business *)search_to_link(member_name, "Business");

                if (temp_bus == NULL)
                    printf("Such a name doesn't exist\n");
                else
                {
                    // Allocating memory for a new node
                    struct linked_business *new_member = (struct linked_business *)malloc(sizeof(struct linked_business));

                    // Assigning this group as a back pointer
                    struct linked_group *grp_back = (struct linked_group *)malloc(sizeof(struct linked_group));
                    grp_back->node_grp = grp_node;
                    grp_back->next = temp_bus->back_grp;
                    temp_bus->back_grp = grp_back;

                    // Now assiging the business node to the group
                    new_member->node_bus = temp_bus;
                    new_member->next = grp_node->businessmember_head;
                    grp_node->businessmember_head = new_member;

                    printf("Successfully added!!\n");
                }

                printf("Do you want to enter any other names (Y/N) ??\n");                      // ASKing if there are any more business members
                scanf("%c%c", &check, &throwaway);

                while (check != 'Y' && check != 'y' && check != 'N' && check != 'n')            // Iterating till a correct character is given
                {
                    printf("Error!! Please enter the correct characer (Y/N)\n");
                    scanf("%c%c", &check, &throwaway);
                }
            }
        }

        // Adding this group node to the global list
        grp_node->next = all_Group;
        all_Group = grp_node;

        printf("******** Node successfully created ********\n");
    }
}

// Function to print one-hop nodes
void one_hop(int id)
{

    int flag = 1;

    // Temporary iterators(pointers) to traverse the global lists

    struct individual *all_ind = all_Individuals;
    struct business *all_bus = all_business;
    struct organisation *all_org = all_Organisation;
    struct group *all_grp = all_Group;

    while (all_ind != NULL && flag)                                                     // Traversing the global list
    {
        if (all_ind->id == id)                                                  // Checking for a match of id
        {
            struct individual *temp_ind = (struct individual *)all_ind;         // A match is found in individual so temporary pointer is pointed to it

            // Temporary iterators to the back pointers
            struct linked_business *bus_type = temp_ind->back_bus;
            struct linked_organisation *org_type = temp_ind->back_org;
            struct linked_group *grp_type = temp_ind->back_grp;

            while (bus_type != NULL || org_type != NULL || grp_type != NULL)        // Runs till all the back pinters become null
            {

                if (flag)                                                           // Runs if tehre is atleast one back node
                {
                    printf("The 1-hop nodes are:- \n\n");
                    flag = 0;
                }

                while (bus_type != NULL)                                            // Printing all the businesses the individual is a part of
                {
                    print_node(bus_type->node_bus, "Business");
                    bus_type = bus_type->next;
                }

                while (org_type != NULL)
                {
                    print_node(org_type->node_org, "Organisation");                 // Printing all the oragnisations the individual is a part of
                    org_type = org_type->next;
                }

                while (grp_type != NULL)
                {
                    print_node(grp_type->node_grp, "Group");                        // Printing all the groups the individual is a part of
                    grp_type = grp_type->next;
                }
            }
        }

        all_ind = all_ind->next;                                                    // Moving on to the next individual
    }
    while (all_bus != NULL && flag)                                                     // Traversing the global list
    {
        if (all_bus->id == id)                                                  // A match is found
        {
            struct business *temp = (struct business *)all_bus;                 // A temporary pointer created to point to the found business node

            // Temporary iterators for the back pointers
            struct linked_group *grp_type = temp->back_grp;                 

            while (grp_type != NULL)                                            
            {

                if (flag)
                {
                    printf("The 1-hop nodes are:- \n\n");
                    flag = 0;
                }

                while (grp_type != NULL)
                {
                    print_node(grp_type->node_grp, "Group");                      // Printing all the groups the business is a part of
                    grp_type = grp_type->next;
                }
            }

            // Printing the owners and customers

            // Creating temporary iterators for owners and customers
            struct linked_individual *temp_owners = temp->owners;
            struct linked_individual *temp_customers = temp->customers;

            while (temp_owners != NULL || temp_customers != NULL)                   // Runs till there are no more owners and customers left
            {

                if (flag)
                {
                    printf("The 1-hope nodes are:- \n\n");
                    flag = 0;
                }

                while (temp_owners != NULL)
                {
                    print_node(temp_owners->node_ind, "Individual");                // Printing all the owners of the business
                    temp_owners = temp_owners->next;
                }

                while (temp_customers != NULL)
                {
                    print_node(temp_customers->node_ind, "Individual");             // Printing all the customers of the business
                    temp_customers = temp_customers->next;
                }
            }
        }

        all_bus = all_bus->next;                                                    // Moving to the new 
    }
    while (all_org != NULL && flag)                                                     // Traversing the global list only if a match hasnt been found previously
    {
        if (all_org->id == id)                                                          // match has been found
        {

            struct organisation *temp = (struct organisation *)all_org;                 // Temporary pointer to the matched group

            struct linked_individual *temp_members = temp->orgmember_head;

            while (temp_members != NULL)                                                // Printing all the individual members of the group
            {

                if (flag)
                {
                    printf("The 1-hop nodes are:- \n\n");
                    flag = 0;
                }

                while (temp_members != NULL)
                {
                    print_node(temp_members->node_ind, "Individual");

                    temp_members = temp_members->next;
                }
            }
        }

        all_org = all_org->next;                                                          // Traversing the global list 
    }
    while (all_grp != NULL && flag)                                                     // Traversing over groups if a match hasn't been found earlier
    {
        if (all_grp->id == id)                                                          // Match has been found
        {
            struct group *temp = (struct group *)all_grp;                               // Temporary pointer to the matched group

            struct linked_individual *ind_members = temp->grpmember_head;
            struct linked_business *bus_members = temp->businessmember_head;

            while (ind_members != NULL || bus_members != NULL)                          // Runs till there are no more individual and business memebers left to be printed
            {

                if (flag)
                {
                    printf("The 1-hop nodes are:- \n\n");
                    flag = 0;
                }

                while (ind_members != NULL)
                {
                    print_node(ind_members->node_ind, "Individual");                    // Printing all the individual members
                    ind_members = ind_members->next;
                }

                while (bus_members != NULL)
                {
                    print_node(bus_members->node_bus, "Business");                      // Printing all the business members
                    bus_members = bus_members->next;
                }
            }
        }

        all_grp = all_grp->next;                                                        // Iterating over the global list
    }

    if (flag)
        printf("There are no 1-hop nodes\n");                                           // Case to chekc if there was no match or no 1-hop nodes
}

// Function to swap two 2-hop nodes
void swap_nodes(struct individual_hop *node_1, struct individual_hop *node_2)
{
    struct linked_individual *temp = node_1->lnkd_ind_node;                     // Temporary pinter to store the would be changed value
    node_1->lnkd_ind_node = node_2->lnkd_ind_node;                              // Just changing the individual they are linked to
    node_2->lnkd_ind_node = temp;
}

// Function to print two-hop nodes for a given INdividual node
void two_hop(struct individual *node)
{
    // Temporary iterators to the back pointers of the given node
    struct linked_organisation *temp_org = node->back_org;
    struct linked_group *temp_grp = node->back_grp;

    int flag = 1;

    // Iterators for the list of 2-hop individuals
    struct individual_hop *head = NULL;

    while (temp_org != NULL)
    {
        // Temporary iterator of linked_individual type to iterate over the individual nodes
        struct linked_individual *temp_ind = temp_org->node_org->orgmember_head;

        // Adding the individuals from the organisation member list
        while (temp_ind != NULL)
        {
            if (node->id == temp_ind->node_ind->id)                                 // Skipping if the node is the original node we are pritning for
            {
                temp_ind = temp_ind->next;
                continue;
            }

            struct individual_hop *curr = (struct individual_hop *)malloc(sizeof(struct individual_hop));    // Else creating a node to store the individual member present in it

            // Poiting the created node to the current individual member being examined
            curr->lnkd_ind_node = temp_ind;                                                                 
            curr->next = NULL;

            struct individual_hop *temp = head;                                         // Pointer to the head of the two-hop members list
            int check = 1;  

            while (temp != NULL)
            {
                if (temp->lnkd_ind_node->node_ind->id == curr->lnkd_ind_node->node_ind->id)     // Checking it the currrent individual exmained is already present in the two-hop lsit
                {
                    check = 0;                                                                  // If it is , skipping over it
                    free(curr);                                                                 // Freeing the memory sued as it container
                    break;      
                }

                temp = temp->next;
            }

            if (check)
            {
                if (flag)
                {
                    head = curr;                                                                 // If this is the frist wo - hop node, it becomes the head
                    flag = 0;
                }
                else
                {   
                    curr->next = head;                                                          // Adding the ndoe to the two-hop list
                    head = curr;
                }
            }

            temp_ind = temp_ind->next;
        }

        temp_org = temp_org->next;
    }

    while (temp_grp != NULL)
    {
        // Temporary iterator of linked_individual type to iterate over the individual nodes
        struct linked_individual *temp_ind = temp_grp->node_grp->grpmember_head;

        // Adding the individuals from the group member list
        while (temp_ind != NULL)
        {
            if (node->id == temp_ind->node_ind->id)
            {
                temp_ind = temp_ind->next;
                continue;
            }

            struct individual_hop *curr = (struct individual_hop *)malloc(sizeof(struct individual_hop));   // Creating a containeer node which pints to the current individual being examined

            curr->lnkd_ind_node = temp_ind;
            curr->next = NULL;

            struct individual_hop *temp = head;                                         // Pointer to the head of the two-hop members list
            int check = 1;

            while (temp != NULL)
            {
                if (temp->lnkd_ind_node->node_ind->id == curr->lnkd_ind_node->node_ind->id)         // If the current individual ndoe is already present, skip over it
                {
                    check = 0;
                    free(curr);                                                                     // Free memory allocated for the container
                    break;  
                }

                temp = temp->next;
            }

            if (check)
            {
                if (flag)
                {
                    head = curr;                                                                    // If the given node is the first two-hop member, it becomes the head
                    flag = 0;
                }
                else
                {   
                    curr->next = head;                                                          // Adding the current individual to the two-hop members list
                    head = curr;
                }
            }

            temp_ind = temp_ind->next;
        }

        temp_grp = temp_grp->next;                                                               // Moving onto the next group
    }

    // Checking if there are any two-hop nodes
    if (flag)
    {
        printf("There are no two-hop nodes\n"); 
        return;
    }

    // Printing the nodes now
    printf("The two-hop nodes are:-\n\n");

    struct individual_hop *curr = head;
    struct individual_hop *prev = NULL;

    while (curr != NULL)
    {

        printf("Name :- %s\n", curr->lnkd_ind_node->node_ind->name);                            // Printing the name and
        printf("Content:- \n%s\n", curr->lnkd_ind_node->node_ind->content);                     // content of all the two hop nodes

        prev = curr;
        curr = curr->next;
        free(prev);                                                                             // Freeing the nodes once we have printed their contents
    }
}

// Function to add content to already existing content
void add_content()
{
    printf("\nEnter the ID of the node you want to modify: ");
    int id;
    scanf("%d%c", &id, &throwaway);

    printf("\nEnter the content you want to add\n");
    char *new_content = content_input();

    if (new_content == NULL)
    {
        printf("Memory allocation failed. Please try again\n");
        return;
    }

    char *node_content;
    int flag = 1;

    // Temporary iterators (pointers) to traverse the global lists
    struct individual *temp_ind = all_Individuals;
    struct business *temp_bus = all_business;
    struct organisation *temp_org = all_Organisation;
    struct group *temp_grp = all_Group;

    // Iterating over the entire nodes to find a match with the given (unique)id
    while (temp_ind != NULL || temp_bus != NULL || temp_org != NULL || temp_grp != NULL)
    {
        if (temp_ind->id == id)
        {
            node_content = temp_ind->content;
            flag = 0;
            break;
        }
        if (temp_bus->id == id)
        {
            node_content = temp_bus->content;
            flag = 0;
            break;
        }
        if (temp_org->id == id)
        {
            node_content = temp_org->content;
            flag = 0;
            break;
        }
        if (temp_grp->id == id)
        {
            node_content = temp_grp->content;
            flag = 0;
            break;
        }

        if (temp_ind != NULL)
            temp_ind = temp_ind->next;
        if (temp_bus != NULL)
            temp_bus = temp_bus->next;
        if (temp_org != NULL)
            temp_org = temp_org->next;
        if (temp_grp != NULL)
            temp_grp = temp_grp->next;
    }

    if (flag)
    {
        printf("No such node exists\n");            // No node exists with the given id
    }
    else
    {
        int old_size = strlen(node_content); // Size of the previous content
        int new_size = strlen(new_content);  // Size of the content to be added

        // Checking how much free space is left in the old content string
        int free_space = ((int)sizeof(node_content) / (int)sizeof(char)) - old_size;

        if (free_space > (new_size + 2))
        {
            // Check if there is enough space to add new content and two '\n' characters
            if ((old_size + free_space) > (old_size + new_size + 2))
            {
                strcat(node_content, "\n\n"); // Adding two '\n' characters
                strcat(node_content, new_content);
                printf("\n******** New content successfully added ********\n");
            }
            else
            {
                // Not enough space, allocate new memory and copy old content
                char *temp = (char *)realloc(node_content, old_size + free_space + new_size + 7); // Adding 7 extra characters for safety

                if (temp == NULL)
                    printf("\n********* Error!! Memory allocation failed ********\n");
                else
                {
                    node_content = temp;
                    strcat(node_content, "\n\n"); // Adding two '\n' characters to differntiate betwwen different contents posted
                    strcat(node_content, new_content);
                    printf("\n******** New content successfully added ********\n");
                }
            }
        }
        else
        {
            // Not enough free space, allocate new memory
            node_content = (char *)realloc(node_content, old_size + new_size + 7); // Adding 7 extra characters for safety

            if (node_content == NULL)
                printf("\n********* Error!! Memory allocation failed ********\n");
            else
            {
                strcat(node_content, "\n\n"); // Adding two '\n' characters to differentiate between two different contents posted
                strcat(node_content, new_content);
                printf("\n******** New content successfully added ********\n");
            }
        }
    }

    // Free the memory allocated for new_content
    free(new_content);
}

// Function to search for and print content
void search_for_content(char string[])
{
    int flag = 1;

    // Temporary iterators to search

    struct individual *temp_ind = all_Individuals;
    struct business *temp_bus = all_business;
    struct organisation *temp_org = all_Organisation;
    struct group *temp_grp = all_Group;

    while (temp_ind != NULL)                            // Iterating over all the individuals                   
    {   
        if (strstr(temp_ind->content, string) != NULL)                  // Checking if the given string is a subtsring or not
        {
            if (flag)
            {
                printf("The node(s) with the given string present in their content are:- \n");
                flag = 0;
            }

            print_node(temp_ind, "Individual");                         //Printing if yes
        }

        temp_ind = temp_ind->next;
    }
    while (temp_bus != NULL)                            // Iterating over all the individuals                    
    {
        if (strstr(temp_bus->content, string) != NULL)                  // Checking if the given string is a subtsring or not                  
        {
            if (flag)
            {
                printf("The node(s) with the given string present in their content are:- \n");
                flag = 0;
            }

            print_node(temp_ind, "Business");                         //Printing if yes
        }

        temp_bus = temp_bus->next;
    }
    while (temp_org != NULL)                            // Iterating over all the individuals
    {
        if (strstr(temp_org->content, string) != NULL)                  // Checking if the given string is a subtsring or not
        {
            if (flag)
            {
                printf("The node(s) with the given string present in their content are:- \n");
                flag = 0;
            }

            print_node(temp_org, "Organisation");                         //Printing if yes
        }

        temp_org = temp_org->next;
    }
    while (temp_grp != NULL)                            // Iterating over all the individuals
    {
        if (strstr(temp_grp->content, string) != NULL)                  // Checking if the given string is a subtsring or not
        {
            if (flag)
            {
                printf("The node(s) with the given string present in their content are:- \n");
                flag = 0;
            }

            print_node(temp_grp, "Group");                         //Printing if yes
        }

        temp_grp = temp_grp->next;
    }

    if (flag)
        printf("There are no matches\n\n");
}

// Function to print all nodes
void print_all()
{
    int flag = 1;

    // Temporary iterators to search

    struct individual *temp_ind = all_Individuals;
    struct business *temp_bus = all_business;
    struct organisation *temp_org = all_Organisation;
    struct group *temp_grp = all_Group;

    while (temp_ind != NULL)                                // Iterating over all the individuals
    {
        print_node(temp_ind, "Individual");

        if (flag)
        {
            printf("\n All the nodes present are:-\n\n");
            flag = 0;
        }
        temp_ind = temp_ind->next;                           // Moving on to the next individual
    }
    while (temp_bus != NULL)                                 // Iterating over all the businesses
    {
        print_node(temp_bus, "Business");

        if (flag)
        {
            printf("\n All the nodes present are:-\n\n");
            flag = 0;
        }
        temp_bus = temp_bus->next;                           // Moving on to the next business
    }
    while (temp_org != NULL)                                // Iterating over all the organisations                            
    {
        print_node(temp_org, "Organisation");

        if (flag)
        {
            printf("\n All the nodes present are:-\n\n");
            flag = 0;
        }
        temp_org = temp_org->next;                           // Moving on to the next organisation
    }
    while (temp_grp != NULL)                                // Iterating over all the groups
    {
        print_node(temp_grp, "Group");

        if (flag)
        {
            printf("\n All the nodes present are:-\n\n");
            flag = 0;
        }
        temp_grp = temp_grp->next;                           // Moving on to the next group
    }

    if (flag)
    {
        printf("No nodes exist\n");                          // If no nodes exists currently in the system
    }
}

// Function to delete a node
void delete_node()
{
    printf("Enter the ID of the node you want to delete:- ");
    int id;
    scanf("%d%c", &id, &throwaway);

    int flag = 1;

    // Temporary iterators (pointers) to traverse the global lists
    struct individual *temp_ind = all_Individuals;
    struct business *temp_bus = all_business;
    struct organisation *temp_org = all_Organisation;
    struct group *temp_grp = all_Group;

    while (temp_ind != NULL && flag)  // Iterating over all the individuals to find a match
    {
        if (temp_ind->id == id)
        {
            flag = 0;
            break;
        }

        temp_ind = temp_ind->next;  // Moving to the next individual
    }
    while (temp_bus != NULL && flag)  // Iterating over all the businesses to find a match
    {
        if (temp_bus->id == id)
        {
            flag = 0;
            break;
        }

        temp_bus = temp_bus->next;  // Moving to the next individual
    }
    while (temp_org != NULL && flag)  // Iterating over all the organisations to find a match
    {
        if (temp_org->id == id)
        {
            flag = 0;
            break;
        }

        temp_org = temp_org->next;  // Moving to the next organisation
    }
    while (temp_grp != NULL && flag)  // Iterating over all the groups to find a match
    {
        if (temp_grp->id == id)
        {
            flag = 0;
            break;
        }

        temp_grp = temp_grp->next;  // Moving to the next organisation
    }

    if (flag)
    {
        printf("No such node exists\n");
    }
    else
    {
        if (temp_ind != NULL) // Means that the node to be deleted is of the type individual
        {
            // Temporary iterators(pointers) to the back nodes so as to free the given individual

            struct linked_business *bus = temp_ind->back_bus;
            struct linked_organisation *org = temp_ind->back_org;
            struct linked_group *grp = temp_ind->back_grp;

            while (bus != NULL) // Iterating over all the business(es) in which the node is present
            {   
                if(bus->node_bus->owners != NULL){
                    if (bus->node_bus->owners->node_ind->id == temp_ind->id) // If the head of the owner list is to be deleted
                    {
                        struct linked_individual* temp = bus->node_bus->owners; // A temporary pointer to the required node
                        bus->node_bus->owners = bus->node_bus->owners->next;    // Assigning the next element as the new head of the list
                        free(temp);                                             // Freeing the node, essentially removing the link between them
                    }
                    else
                    {
                        // Temporary iterators to iterate over
                        struct linked_individual *curr = bus->node_bus->owners->next; // Points to the current owner node being examined
                        struct linked_individual *prev = bus->node_bus->owners;       // Points to the recent node already examined to link

                        while (curr != NULL)
                        {
                            if (curr->node_ind->id == temp_ind->id)                     // Checking for a match
                            {
                                prev->next = curr->next;                                // Linking the prev node with the next node
                                free(curr);                                             // Free the link
                                break;
                            }

                            prev = curr;
                            curr = curr->next; // Traversing the list
                        }
                    }
                }

                // Checking in the customer's list
                if(bus->node_bus->customers != NULL){
                    if (bus->node_bus->customers->node_ind->id == temp_ind->id )    // If the head of the customer list is to be deleted
                    {
                        struct linked_individual *temp = bus->node_bus->customers; // A temporary pointer to the required node
                        bus->node_bus->customers = bus->node_bus->customers->next; // Assigning the next element as the new head of the list
                        free(temp);
                        printf("145\n");
                    }
                    else
                    {
                        // Temporary iterators to iterate over
                        struct linked_individual *curr = bus->node_bus->customers->next; // Points to the current owner node being examined
                        struct linked_individual *prev = bus->node_bus->customers;       // Points to the recnt node already examined to link

                        while (curr != NULL)
                        {
                            if (curr->node_ind->id == temp_ind->id) // Checking for a match
                            {
                                prev->next = curr->next; // Linking the prev node with the next node
                                free(curr);              // free the link
                                break;
                            }

                            prev = curr;
                            curr = curr->next; // Traversing the list
                        }
                    }
                }

                struct linked_business *free_the_bus = bus;
                bus = bus->next;    // Moving to the next business in which the node is present
                free(free_the_bus); // Freeing the back pointer to the current business
            }
            while (org != NULL) // Iterating over all the organisation(s) in which the node is present
            {
                // Deleting the link in the member's list
                if(org->node_org->orgmember_head != NULL){
                    if (org->node_org->orgmember_head->node_ind->id == temp_ind->id)
                    {
                        struct linked_individual *temp = org->node_org->orgmember_head;
                        org->node_org->orgmember_head = org->node_org->orgmember_head->next;
                        free(temp);
                    }
                    else
                    {
                        // Temporary iterators to iterate over
                        struct linked_individual *curr = org->node_org->orgmember_head->next; // Points to the current member being examined
                        struct linked_individual *prev = org->node_org->orgmember_head;       // Points to the recnt node already examined to link

                        while (curr != NULL)
                        {
                            if (curr->node_ind->id == temp_ind->id) // Checking for a match
                            {
                                prev->next = curr->next; // Linking the prev node with the next node
                                free(curr);              // free the link
                                break;
                            }

                            prev = curr;
                            curr = curr->next; // Traversing the list
                        }
                    }
                }

                struct linked_organisation *free_the_org = org;
                org = org->next;    // Moving to the next organisation
                free(free_the_org); // Freeing the back pointer to the current organisation
            }
            while (grp != NULL)
            {
                // Deleting the node link from the members list
                if(grp->node_grp->grpmember_head != NULL){
                    if (grp->node_grp->grpmember_head->node_ind->id == temp_ind->id) // If the head of the group list is to be deleted
                    {
                        struct linked_individual *temp = grp->node_grp->grpmember_head;
                        grp->node_grp->grpmember_head = grp->node_grp->grpmember_head->next;
                        free(temp);
                    }
                    else
                    {
                        // Temporary iterators to iterate over
                        struct linked_individual *curr = grp->node_grp->grpmember_head->next; // Points to the current member being examined
                        struct linked_individual *prev = grp->node_grp->grpmember_head;       // Points to the recnt node already examined to link

                        while (curr != NULL)
                        {
                            if (curr->node_ind->id == temp_ind->id) // Checking for a match
                            {
                                prev->next = curr->next; // Linking the prev node with the next node
                                free(curr);              // free the link
                                break;
                            }

                            prev = curr;
                            curr = curr->next; // Traversing the list
                        }
                    }
                }

                struct linked_group *free_the_grp = grp;
                grp = grp->next;    // Moving to the next group
                free(free_the_grp); // Freeing the back pointer to the current group
            }

            // Now freeing the node and it's inner data

            struct individual *temp = all_Individuals;

            if (all_Individuals->id == temp_ind->id) // The node is the head of global linked list
            {
                all_Individuals = all_Individuals->next; // Changing the head of the list
            }
            else
            {

                struct individual *prev = all_Individuals; // Tracks the previous node examined
                while (temp != NULL)
                {
                    if (temp->id == temp_ind->id) // If the node is found
                    {
                        prev->next = temp->next; // Linking the previous and next node
                        break;
                    }

                    prev = temp;       // Current node becomes prev
                    temp = temp->next; // Iterating through the list
                }
            }

            // Freeing each attribute
            free(temp->name);
            free(temp->creation);
            free(temp->content);
            free(temp->birthday);

            // Finally deleting the node
            free(temp_ind);

            printf("\n******** Successfully deleted ********\n");
        }
        else if (temp_bus != NULL) // The node to be deleted is of the type business
        {
            // Temporary iterator(pointer) to iterate over the back grp list

            struct linked_group *grp = temp_bus->back_grp;

            while (grp != NULL)
            {   
                if(grp->node_grp->businessmember_head != NULL){
                    if (grp->node_grp->businessmember_head->node_bus->id == temp_bus->id)
                    {
                        struct linked_business *temp = grp->node_grp->businessmember_head;             // Temporary pointer to the head
                        grp->node_grp->businessmember_head = grp->node_grp->businessmember_head->next; // Next element becomes the new head of the business member head
                        free(temp);                                                                    // Freeing the node
                    }
                    else
                    {
                        // Temporary iterators to iterate over
                        struct linked_business *curr = grp->node_grp->businessmember_head->next; // Points to the current owner being examined
                        struct linked_business *prev = grp->node_grp->businessmember_head;       // Points to the recent node already examined

                        while (curr != NULL)
                        {
                            if (curr->node_bus->id == temp_bus->id)
                            {
                                prev->next = curr->next; // Linking the previous node with the next node
                                free(curr);              // Free the link
                                break;
                            }

                            prev = curr;
                            curr = curr->next;
                        }
                    }
                }

                struct linked_group *free_the_grp = grp;
                grp = grp->next;    // Moving to the next group
                free(free_the_grp); // Freeing the back pointer link
            }

            // Freeing each attribute

            free(temp_bus->name);
            free(temp_bus->creation);
            free(temp_bus->content);

            // Freeing the links in customer and owner lists

            struct linked_individual *member_curr = temp_bus->owners; // Pointer to the head of the owner list
            struct linked_individual *member_prev;                    // Points to the previous node link so as to be freed

            while (member_curr != NULL)
            {
                member_prev = member_curr;
                member_curr = member_curr->next; // Moving on to the next link
                free(member_prev);               // Freeing the iterated node link
            }

            // Now freeing the customers list
            member_curr = temp_bus->customers;

            while (member_curr != NULL)
            {
                member_prev = member_curr;
                member_curr = member_curr->next; // Moving on to the next link
                free(member_prev);               // Freeing the iterated node link
            }

            // Freeing the node from the global list
            struct business *temp = all_business;

            if (all_business->id == temp_bus->id) // The node is the head of the global list
            {
                all_business = all_business->next; // Changing the head of the list
            }
            else
            {
                struct business *prev = all_business;
                while (temp != NULL)
                {
                    if (temp->id == temp_bus->id) // If the node is found
                    {
                        prev->next = temp->next; // Linking the previous and next node
                        break;
                    }

                    prev = temp;       // Current node becomes prev
                    temp = temp->next; // Iterating through the list
                }
            }

            // Finally freeing the node
            free(temp_bus);

            printf("\n******** Successfully deleted ********\n");
        }
        else if (temp_org != NULL) // The node to be deleted is of organisation type
        {
            // Freeing the members in the organisation

            struct linked_individual *curr = temp_org->orgmember_head;
            struct linked_individual *prev;

            while (curr != NULL)
            {
                prev = curr;
                curr = curr->next;
                free(prev);
            }

            // Deleting the node from the global list
            struct organisation *temp = all_Organisation;

            if (all_Organisation->id == temp_org->id)
            {
                all_Organisation = all_Organisation->next;
            }
            else
            {
                struct organisation *prev = all_Organisation;
                while (temp != NULL)
                {
                    if (temp->id == temp_org->id)
                    {
                        prev->next = temp->next;
                        break;
                    }

                    prev = temp;
                    temp = temp->next;
                }
            }

            // Freeing the attributes of the node
            free(temp_org->name);
            free(temp_org->creation);
            free(temp_org->content);

            // Finally deleting the node
            free(temp_org);

            printf("\n******** Successfully deleted ********\n");
        }
        else if (temp_grp != NULL) // The node to be deleted is a group
        {
            // Freeing the individual member links

            struct linked_individual *curr = temp_grp->grpmember_head;
            struct linked_individual *prev;

            while (curr != NULL)
            {
                prev = curr;
                curr = curr->next;
                free(prev);
            }

            // Freeing the business member links

            struct linked_business *curr_bus = temp_grp->businessmember_head;
            struct linked_business *prev_bus;

            while (curr_bus != NULL)
            {
                prev_bus = curr_bus;
                curr_bus = curr_bus->next;
                free(prev_bus);
            }

            // Removing the node from the global list
            struct group *temp = all_Group;

            if (all_Group->id == temp_grp->id)
            {
                all_Group = all_Group->next;
            }
            else
            {
                struct group *prev = all_Group;
                while (temp != NULL)
                {
                    if (temp->id == temp_grp->id)
                    {
                        prev->next = temp->next;
                        break;
                    }

                    prev = temp;
                    temp = temp->next;
                }
            }

            // Freeing the attributes of the node
            free(temp_grp->name);
            free(temp_grp->creation);
            free(temp_grp->content);

            // Finally deleting the node
            free(temp_grp);

            printf("\n******** Successfully deleted ********\n");
        }
    }
}

int main() {
    while (1) {
        // Display menu options
        printf("\n******** Enter your choice ********\n\n"
               "1 ==> Create a node\n"
               "2 ==> Search for a node\n"
               "3 ==> Print 1-hop nodes\n"
               "4 ==> Modify content of a node\n"
               "5 ==> Print content by a node\n"
               "6 ==> Search for content\n"
               "7 ==> Print two-hop individual nodes\n"
               "8 ==> Delete a node\n"
               "-1 ==> Exit\n\n");

        int input;
        scanf("%d", &input);

        // Input buffer clear
        char throwaway;
        scanf("%c", &throwaway);

        switch (input) {
            case 1:
                // Node creation menu
                printf("\nEnter the type you want to enter\n"
                       "1 ==> Individual\n"
                       "2 ==> Business\n"
                       "3 ==> Organisation\n"
                       "4 ==> Group\n\n");

                scanf("%d%c", &input, &throwaway);

                if (input >= 1 && input <= 4) {
                    // Valid type input
                    char nodeType[20];

                    // Map user input to node type
                    switch (input) {
                        case 1:
                            strcpy(nodeType, "Individual");
                            break;
                        case 2:
                            strcpy(nodeType, "Business");
                            break;
                        case 3:
                            strcpy(nodeType, "Organisation");
                            break;
                        case 4:
                            strcpy(nodeType, "Group");
                            break;
                    }

                    new_node(nodeType);
                } else {
                    printf("\nInvalid input. Please enter a number between 1 and 4.\n");
                }
                break;

            case 2:
                // Node search menu
                printf("\nChoose the parameter to search\n"
                       "1 ==> Name\n"
                       "2 ==> Type\n"
                       "3 ==> Birthday\n\n");

                int parameter;
                scanf("%d%c", &parameter, &throwaway);

                switch (parameter) {
                    case 1:
                        printf("\nEnter the name\n");
                        char *name = name_input();
                        search(name);
                        break;

                    case 2:
                        printf("\nEnter the type\n");
                        char *type = name_input();
                        search(type);
                        break;

                    case 3:
                        printf("\nEnter the birthday\n");
                        struct tm *bday = date_input();
                        search_by_birthday(bday);
                        break;

                    default:
                        printf("\nInvalid input. Please enter a number between 1 and 3.\n");
                        break;
                }
                break;

            case 3:
                // Print 1-hop nodes
                printf("\nEnter the node's ID\n");
                int id;
                scanf("%d%c", &id, &throwaway);
                one_hop(id);
                break;

            case 4:
                // Modify content of a node
                add_content();
                break;

            case 5:
                // Print content by a node
                printf("\nEnter the ID of the node\n");
                scanf("%d%c", &id, &throwaway);
                print_content(id);
                break;

            case 6:
                // Search for content
                printf("\nEnter the string you want to search\n");
                char *sub_string = content_input();
                search_for_content(sub_string);
                break;

            case 7:
                // Print two-hop individual nodes
                printf("\nEnter the ID of the Individual node\n");
                scanf("%d%c", &id, &throwaway);
                two_hop((struct individual *)search_by_id(id));
                break;

            case 8:
                // Delete a node
                delete_node();
                break;

            case -1:
                // Exit the program
                printf("\nExiting the program.\n");
                return 0;

            default:
                // Invalid input
                printf("\nInvalid choice. Please enter a valid option.\n");
                break;
        }
    }

    return 0;
}