/**
 * @file social.h
 * @brief Header file for the Social Network program.
 * @details This file contains structure definitions and function prototypes for implementing
 * functionalities related to nodes in a social network.
 *
 * Program Overview:
 * -----------------
 * The Social Network program manages nodes representing individuals, groups, businesses, and organizations.
 * It provides functionalities for creating and deleting nodes, searching for nodes, posting content, and
 * exploring relationships between nodes.
 *
 * Structures:
 * -----------
 * - individual: Represents an individual node with attributes like ID, name, creation date, content, and birthday.
 * - group, business, organization: Similar structures with additional attributes as per their types.
 * - date: Structure for representing a date with day, month, and year.
 *
 * Functions:
 * -----------
 * - name_input(): Takes user input for the name string.
 * - date_input(): Takes user input for a date structure.
 * - content_input(): Takes user input for the content string.
 * - birthday_input(): Takes user input for a birthday structure.
 * - print_node(): Prints the attributes of a given node.
 * - search(): Searches and prints nodes based on a given parameter.
 * - search_by_id(): Searches and returns a node based on its ID.
 * - search_by_birthday(): Searches and prints nodes based on a given birthday.
 * - print_content(): Prints the content of a node with a given ID.
 * - search_to_link(): Searches for a node with matching parameters and links it.
 * - new_node(): Creates a new node of all types.
 * - one_hop(): Prints one-hop nodes for a node with a given ID.
 * - swap_nodes(): Swaps content between two nodes.
 * - two_hop(): Prints two-hop nodes for a given individual node.
 * - add_content(): Adds content to a node.
 * - search_for_content(): Searches and prints nodes with content containing a given string.
 * - print_all(): Prints all nodes in the system.
 * - delete_node(): Deletes a node from the system.
 *
 * @note All structures and function prototypes are defined in this header file.
 */

#ifndef SOCIAL_H
#define SOCIAL_H

// Used headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Forward Declarations
struct linked_individual;
struct linked_business;
struct linked_organisation;
struct linked_group;


/**
 * @struct date
 * @brief Structure for representing a date.
 *
 * This structure contains attributes for the day, month, and year of a date.
 */
struct date
{

    int date;
    int month;
    int year;
};

/**
 * @struct individual
 * @brief Structure that containes the required attributes of a business type node
 * 
 * 
 * Contains back pointers of heads of lists to group,organisations and business along with it's own attributes, with a unique birthday attribute.
 * Also has a next pointer of the same type to be linked in a global list and a type string to know it's type
*/
struct individual
{

    char type[20];

    // Back pointers

    struct linked_business *back_bus;
    struct linked_organisation *back_org;
    struct linked_group *back_grp;

    // Basic Attributes

    int id;
    char *name;
    struct tm *creation;
    char *content;

    // Unique Attribute(s)

    struct tm *birthday;

    struct individual *next;
};

/**
 * @struct linked_individual
 * @brief Structure that stores a pointer to a indvidual node
 * 
 * It acts as a container to an individual node, thereby used in linking and preventing duplication
*/
struct linked_individual
{

    struct individual *node_ind; // The individual to which it points

    struct linked_individual *next;
};

/**
 * @struct business
 * @brief Structure that containes the required attributes of a business type node
 * 
 * Containes back pinter to the head of a list of groups in which the business is present as a member, along with it it's own attributes.
 * Some unique attrbiutes are the Co-ordinates of the business, along with the heads of list of customers and owners.
 * Has a next pointer to be linked to differnet business nodes and a type string to know it's type
*/
struct business
{

    char type[20];

    // Back pointers

    struct linked_group *back_grp;

    // Basic Attributes

    int id;
    char *name;
    struct tm *creation;
    char *content;

    // Unique Attribute(s)

    double x_cord;
    double y_cord;
    struct linked_individual *owners;
    struct linked_individual *customers;

    struct business *next;
};

/**
 * @struct linked_business
 * @brief Structure that stores a pointer to a business node
 * 
 * It acts as a container to an business node, thereby used in linking and preventing duplication
*/
struct linked_business
{

    struct business *node_bus;

    struct linked_business *next;
};

/**
 * @struct organisation
 * @brief Structure that containes the required attributes of a organisation type node
 * 
 * Doesn't have nay back pointers as they are not required. contains the basic attributes, along with Co-ordinates,
 * and the had pointer to a list of Indvidual type members it ahs, stored through the linked_individual type. 
 * Also has a next pointer used to link it with other organisations and a type string to know it's type
*/
struct organisation
{

    char type[20];

    // Basic Attributes

    int id;
    char *name;
    struct tm *creation;
    char *content;

    // Unique Attribute(s)

    double x_cord;
    double y_cord;
    struct linked_individual *orgmember_head;

    struct organisation *next;
};

/**
 * @struct linked_organisation
 * @brief Structure that stores a pointer to a business node.
 * 
 * It acts as a container to an business node, thereby used in linking and preventing duplication.
*/
struct linked_organisation
{

    struct organisation *node_org;

    struct linked_organisation *next;
};

/**
 * @struct group
 * @brief Structure that containes the required attributes of a group type node.
 * 
 * Has the basic attributes along with Co-ordinates and two lists of members, one of the type individual and the other 
 * of business. ALso has a next pointer to link with other groups and a type string to know it's type.
*/
struct group
{

    char type[20];

    // Basic Attributes

    int id;
    char *name;
    struct tm *creation;
    char *content;

    // Unique Attribute(s)

    double x_cord;
    double y_cord;
    struct linked_individual *grpmember_head;
    struct linked_business *businessmember_head;

    struct group *next;
};

/**
 * @struct linked_organisation
 * @brief Structure that stores a pointer to a business node.
 * 
 * It acts as a container to an business node, thereby used in linking and preventing duplication.
*/
struct linked_group
{

    struct group *node_grp;

    struct linked_group *next;
};

/**
 * @struct individual_hop
 * @brief Structure that contains the pinter to a container of a individual node
 * 
 * Used exclusivley to print out the two hop ndoes by storing the addresses of various containers it's linked with.
 * hAs a pointer of type linked_individual i.e the container and a next pointer to link.
*/
struct individual_hop
{
    struct linked_individual *lnkd_ind_node;
    struct individual_hop *next;
};

/*
 * Takes input from the user character by character so that spaces are included too.
 * -----------
 * 
 * Parameters : None
 * -----------
 * 
 * Returns : A char pointer(array) with the name string
 * -----------
 * 
 * The string ends when a new line character is detected
 */
char *name_input();

/*
 * Function to take input of date from the user
 * -----------
 * 
 * Parameters : None
 * -----------
 * 
 * Returns : A struct tm type pointer of a structure containing the date
 * -----------
 *
 * If the date entered is wrong, -1 is returned for the day,month and year
 */
struct tm *date_input();

/*
 * Takes input for the "Content" attribute of a node
 * -----------
 * 
 * Parameters : None
 * -----------
 * 
 * Returns : A char type pointer(array) of the content string
 * -----------
 * 
 * Works similar to the name_input function
 */
char *content_input();

/*
 * Function to take input of birthday from the user
 * -----------
 * 
 * Parameters : None
 * -----------
 * 
 * Returns : A struct tm type pointer of a structure containing the birthday
 * -----------
 * 
 * Uses the name-input function if the user want's to input a birthday, otherwise a known invalid date is given
 */
struct tm *birthday_input();

/*
 * Function to print a given node
 * -----------
 * 
 * Parameters :
 *          1) A node pointer of the type Void so that it can be typecasted to the required type
 *          2) A string type, to know which type of node has been given
 * -----------
 * 
 * Returns :
 *          Prints out the content of the node
 * -----------
 * 
 * Searches the global linked list for a match with the node, and Prints it's attributes
 */
void print_node(void *node, char type[]);

/*
 * Function to search for a given node and print it
 * -----------
 * 
 * Parameters :
 *          A string search_parameter, i.e the parameter the user wants to search for
 * -----------
 * 
 * Returns :
 *          Prints out the content of the node if it's required parameter matches with the given search_parameter
 * -----------
 * 
 * Used to print nodes if the user gives name or type as the search parameter.
 * Iterates over all the nodes and prints any nodes that match 𝘪𝘯 𝘴𝘪𝘵𝘶
 */
void search(char search_parameter[]);

/*
 * Function to search for a given node and print it
 * -----------
 * 
 * Parameters :
 *          An integer id, which is unique to each node
 * -----------
 * 
 * Returns :
 *          returns a pointer of the the type void*, i.e it can be typecasted later
 * -----------
 * 
 * Runs over the global linked lists to find a macth between the given id and the id present in the node
 */
void *search_by_id(int id);

/*
 * Function that searches for a given birthday
 * -----------
 * 
 * Parameters :
 *          A struct tm (time) search_date, that contains the date to be searched
 * -----------
 * 
 * Returns :
 *          Prints out all the (individual) nodes with the given birthday
 * -----------
 * 
 * Since individuals are the only ones with a birthday iterates over the
 * global individual list and searches for a match
 *
 */
void search_by_birthday(struct tm *search_date);

/*
 * Function to print the content of a node with a given id
 * -----------
 * 
 * Parameters :
 *          A integer id, which is unique for each node
 * -----------
 * 
 * Returns ;
 *          Prints out the content (attributes) in an orderly fashion
 * -----------
 * 
 * AS the id is unique for each node, we can just iterate over the global
 * lists and search for a match with the id. No match is taken care of.
 */
void print_content(int id);

/*
 * Funtion that returns nodes with the matching search_parameeter and type,
 * which are then linked in
 * -----------
 * 
 * Parameters :
 *          1) A string search_parameter, which is checked for within nodes of a given type
 *          2) A string type, which indicates the type of node
 * -----------
 * 
 * Returns :
 *          A void* pointer pointing to the ndeo with the given match, or NULL if not found
 * -----------
 * 
 * This function is primarily used during cerating a new node to link various types of
 * nodes as members. Checks only business and individual types since they are the only ones
 * that are used as members
 */
void *search_to_link(char search_parameter[], char type[]);

/*
 * Primary function that creates a new node, of all types
 * -----------
 * 
 * Paramters :
 *           A string type, indicating the type of the node
 * -----------
 * 
 * Returns :
 *          Does not return anything but creates a new node and adds it to the global list
 * -----------
 * 
 * Function can take input of all types and required functions are used to do so.
 */
void new_node(char type[]);

/*
 * Function to print one-hop nodes for a node witha  given id
 * -----------
 * 
 * Parameters :
 *          A interger id, which is checked over all nnodes to find a match
 * -----------
 * 
 * Returns :
 *          Prints out all the one-hop nodes to a given nodes
 * -----------
 * 
 * One-hop nodes are the nodes that have a direct connection to the given node
 * Since we maintiain back pointers too, printing all the abck pointed nodes and
 * members if any present in the node will give all the nodes that are firectly linked
 * to the given node
 */
void one_hop(int id);

/*
 *
 * Function to swap two nodes
 * ------------
 *
 * Parameters :
 *          Two nodes individual_hop* type nods(pointers) that are to be swapped
 * ------------

 * Returns :
 *          Doesn't return anything but just swaps the two given nodes
 * -----------
 * 
 * Since we use this function to swap just the content present in them, we swap their inner contents
 */
void swap_nodes(struct individual_hop *node_1, struct individual_hop *node_2);

/*
 * Function that prints the two-hop individual nodes for a given individual node
 * ------------
 *
 * Parameters :
 *          A single pointer to the requires individual node
 * ------------
 *
 * Returns :
 *          Prints out all the two-hop nodes to the given individual node. Returns nothing as such
 * ------------
 *
 * Two - hop individual nodes are the ones which have a common group or organisation with the given individual node
 * Since we have back pointers to the given node, we can iterate through them to create a linked list of all the individuals
 * present as members in them.
 *
 * Linked list is used so that there is no duplication of two-hop nodes
 */
void two_hop(struct individual *node);

/*
 * Function that adds content , i.e posts, to already present content of a node
 * ------------
 *
 * Parameters :
 *          There are no required parameters
 * ------------
 *
 * Returns :
 *          Returns nothing but modifies the content of the node required
 * ------------
 *
 * The function takes the input of id inside it and iterates over all ndoes to find a match.
 * Once a match is foudn, it takes the input for the new content, and add it to the already
 * pre- existing content .
 *
 * Two new-line characters are added to differatiate betwwen various posts. Memory allocation
 * and size issues are completely taken care of while concatenating them.
 *
 */
void add_content();

/*
 * Function that searches if the given parameter is a substring of the content of any nodes
 * ------------
 *
 * Parameters :
 *          A string named string is the substring that we wish to find superstrings for
 * ------------
 *
 * Returns :
 *          Prints out all the nodes which have the given string as a substring in their content
 * ------------
 *
 * The function uses the 'strstr' function from the string.h library to check is the given string is a
 * substring of a node's content. If so, the node is then printed out
 *
 */
void search_for_content(char string[]);

/*
 * Function that prints out all the nodes present in the system now
 * ------------
 *
 * Parameters :
 *          Doesn't have any parameters.
 * ------------
 *
 * Returns :
 *          Prints all the nodes present now in the system
 * ------------
 *
 * The function iterates over all the nodes present in the global lists and prints them out
 *
 */
void print_all();

/*
 * Function that deletes a given node
 * ------------
 *
 * Parameters :
 *          Doesn't have nay parameters as such
 * ------------
 *
 * Returns :
 *          Deletes a node entirely from the system. DOesn't return anything as such
 * ------------
 *
 * The function takes the input of ID 𝘪𝘯 𝘴𝘪𝘵𝘶 and checks for the node with that id.
 * Then, it first freees the link to the ndoe with it's back pointers, i.e, it removes itself from any
 * nodes it is present as a member. Then , the attrbiutes of a node are freed, allong with any link to the members inside it.
 * 
 * Finally, the node is removed from the global list and completely freed. This ensures that all the freed up memory can be used again
 *
 */
void delete_node();

#endif // SOCIAL_H