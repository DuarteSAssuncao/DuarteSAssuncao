/**
 * @file vector.c
 * @brief Implementation of a C++ std::vector in C
 * @author T17_G1
 * @date 29/05/2024
 */

#include "vector.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//#define DEBUG
#include <auxiliary/debug.h>

typedef vector(void) aux_vector_t;

/**
 * @brief Calculates the address of an element at index 'idx', for a vector 'self' with elements of size type_size
 */
#define vector_at__(this, type_size, idx) ((void*)(((uint8_t*)(this)->at) + (type_size) * (idx)))

/**
 * @brief Initializes a vector with some initial atributes
 * @param void* self : a pointer to the new vector
 * @param size_t type_size : size of each element of the vector
 * @param size_t init_cap : initial capacity
 * @return int : 0 on success
 */
int vector_init_(void *self, size_t type_size, size_t init_cap) {
    if (init_cap == 0) return 1;
    aux_vector_t *this = self;

    this->at = malloc(init_cap * type_size);
    if (this->at == NULL) return 1;

    this->cap = init_cap;
    this->size = 0;
    return 0;
}

/**
 * @brief Destroys the vector by freeing its memory
 * @param void *self : the vector to destroy
 * @return void
 */
void vector_destruct(void *self) {
    if (self == NULL) return;
    free(((aux_vector_t*) self)->at);
}

/**
 * @brief Adds an uninitialized new element and doubles the capacity of the vector if size is greater or equal than its capacity
 * @param void *self : the vector to expand
 * @param size_t type_size : size of each element in the vector
 * @return void* : the new extended vector
 */
void* vector_extend_(void *self, size_t type_size) {
    aux_vector_t *this = self;
    if (this->size >= this->cap) {
        void *tmp = realloc(this->at, 2 * this->cap * type_size);
        if (tmp == NULL) return NULL;
        this->at = tmp;
        this->cap *= 2;
    }

    ++this->size;
    return vector_at__(this, type_size, this->size - 1);
}

/**
 * @brief Adds a new element to the end of the vector
 * @param void *self : vector to add the element to
 * @param size_t type_size : size of the element to add
 * @param void *from : the element to add
 * @return int : 0 on success
 */
int vector_push_(void *self, size_t type_size, void *from) {
    aux_vector_t *this = self;
    if (vector_extend_(self, type_size)) return 1;

    uint8_t *new_element = ((uint8_t*)this->at) + type_size * (this->size - 1);
    memcpy(new_element, from, type_size);
    return 0;
}

/**
 * @brief Reserves some capacity for the vector
 * @param void *self : the vector to reserve capacity
 * @param size_t type_size : size of each element in the vector
 * @param size_t size : how many elements should the new capacity be consisted of
 * @return int : 0 on success
 */
int vector_reserve_(void *self, size_t type_size, size_t size) {
    aux_vector_t *this = self;
    if (size > this->cap) {
        void *tmp = realloc(this->at, size * type_size);
        if (tmp == NULL) return 1;
        this->at = tmp;
        this->cap = size;
    }
    return 0;
}

/**
 * @brief Resizes the vector to the given size.
 *        If the new size is bigger than the vector's size, the new elements are not initialized.
 *        If the new size is equal or smaller than the vector's capacity, the capacity remains unchanged.
 * @param void *self : vector to resize
 * @param size_t type_size : size of each element in the vector
 * @param size_t size : new size
 * @return int : 0 on success
 */
int vector_resize_(void *self, size_t type_size, size_t size) {
    aux_vector_t *this = self;
    if (vector_reserve_(self,type_size,size))
        return -1;
    this->size = size;
    return 0;
}

/**
 * @brief Remove an element from the vector
 * @param void *self : vector from which to remove an element
 * @param size_t type_size : size of each element in the vector
 * @param size_t idx : index of element to remove
 * @return int : 0 on success
 */
int vector_remove_(void *self, size_t type_size, size_t idx) {
    aux_vector_t *this = self;
    if (idx >= this->size)
        return 1;
    uint8_t *dest = vector_at__(this,type_size,idx);
    uint8_t *src = dest + type_size;
    memmove(dest, src, type_size * (this->size - idx - 1));
    --this->size;
    return 0;
}

/**
 * @brief Removes all elements of the vector. Its capacity is not altered, nor the buffer contents.
 * @param void *self : self The vector to clear
 * @param size_t type_size : size of each element in the vector
 * @return int : 0 on success, non-zero otherwise
 */
void vector_clear_(void* self, size_t type_size) {
    ((aux_vector_t*)self)->size = 0;
}
