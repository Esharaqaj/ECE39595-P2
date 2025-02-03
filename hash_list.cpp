#include "hash_list.h"
#include <iostream>

hash_list::hash_list(){head = NULL; iter_ptr = NULL; size = 0;}
// struct node* head = NULL;

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

void hash_list::insert(int key, float value) {
    if(head == NULL)
    {   
        head = new node{key, value, NULL};
        // std::cout << "NODE:" << head->key << "VALUE:" << head->value << "\n";
        iter_ptr = 0;
        size++;
        return;
    }

    node *current = head;

    while(current != NULL)
    {
        if(current->key == key) 
        {
            current->value = value;
            return;
        }

        current = current->next;
    }

    node* new_node = new node{key, value, head};
    head = new_node;
    size++;
    return;

}

std::optional<float> hash_list::get_value(int key) const { 
    
    node* current = head;

    while((current != NULL))
    {
        if(current->key == key) return current->value;
        current = current->next;
    }

    return std::nullopt; }

bool hash_list::remove(int key) { 
    
    if (head == NULL) return false;

    node* current = head;

    if (current->key == key)
    {
        head = current->next;
        delete current;
        size--;
        return true;
    }

    node* temp = current->next;

    while(temp != NULL)
    {
        if(temp->key == key)
        {
            current->next = temp->next;
            delete temp;
            size--;
            return true;
        }

        current = current -> next;
        temp = temp -> next;
    }   


    
    return false; }

size_t hash_list::get_size() const { return size;}

hash_list::~hash_list() {

    node* current = head;
    node* temp;

    while(current != NULL)
    {
        temp = current;
        current = current -> next;
        delete temp;
    }

    size = 0;
}

/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/

hash_list::hash_list(const hash_list &other) {

    head = NULL;
    iter_ptr = NULL;
    size = other.size;

    if (other.head == NULL) return;

    head = new node{other.head->key, other.head->value, NULL};
    node *current = head;
    node *other_current = other.head->next;

    while (other_current != NULL) {
        current->next = new node{other_current->key, other_current->value, NULL};
        current = current->next;
        other_current = other_current->next;
    }


}

hash_list &hash_list::operator=(const hash_list &other) {
    
    if (this == &other) return *this;

    this->~hash_list();
    size = other.size;

    if(other.head == NULL)
    {
        head = NULL;
        return *this;
    }
    
    head = new node{other.head->key, other.head->value, NULL};
    node * current = head;
    node * forward = other.head->next;

    while(forward != NULL)
    {
        current->next = new node{forward->key, forward->value, NULL};
        current = current->next;
        forward = forward->next;

    }


    
     return *this; }

void hash_list::reset_iter() {
    if(head == NULL) return;
    else iter_ptr = head;
    return;
}


void hash_list::increment_iter() {
    if(iter_at_end()) return;

    if(iter_ptr->next == NULL)
    {
        iter_ptr = NULL;
        return;
    }

    iter_ptr = iter_ptr->next;
}


std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() { 
    if(iter_ptr == NULL) return std::nullopt;

     return std::make_pair(&(iter_ptr->key), &(iter_ptr->value)); }


bool hash_list::iter_at_end() { 
    if(iter_ptr == NULL) return true;
    return false; }
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
