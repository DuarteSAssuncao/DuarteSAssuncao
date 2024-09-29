/**
 * @file vector.h
 * @brief Declaration of a C++ std::vector in C
 * @author T17_G1
 * @date 29/05/2024
 */

#ifndef LCOM_PROJ_VECTOR_H
#define LCOM_PROJ_VECTOR_H

#include <stddef.h>

#define vector(T)\
    struct\
    {\
        T *at;\
        size_t cap,size;\
    }

/**
 * @brief Initializes a vector with some initial atributes
 * @param void* self : a pointer to the new vector
 * @param size_t type_size : size of each element of the vector
 * @param size_t init_cap : initial capacity
 * @return int : 0 on success
 */
int vector_init_(void *self, size_t type_size, size_t init_cap);
#define vector_init_cap(self,init_cap) vector_init_(self,sizeof(*(self)->at),init_cap)
#define vector_init(self) vector_init_cap(self,8)

/**
 * @brief Destroys the vector by freeing its memory
 * @param void *self : the vector to destroy
 * @return void
 */
void vector_destruct(void *self);
//#define vector_destruct(self) vector_destruct_(self, sizeof(*(self)->at))

/**
 * @brief Adds an element. It is not initialized.
 * @return A pointer to the added element on success, NULL otherwise.
 * @note In case of failure, the vector remains unchanged.
 */
void* vector_extend_(void *self, size_t type_size);
#define vector_extend(self) vector_extend_(self, sizeof(*(self)->at))
#define vector_next vector_extend

/**
 * @brief Adds a new element to the end of the vector
 * @param void *self : vector to add the element to
 * @param size_t type_size : size of the element to add
 * @param void *from : the element to add
 * @return int : 0 on success
 */
int vector_push_(void *self, size_t type_size, void *from);
#define vector_push(self,from) vector_push_(self,sizeof(*(self)->at),from)

/**
 * @brief Reserves some capacity for the vector
 * @param void *self : the vector to reserve capacity
 * @param size_t type_size : size of each element in the vector
 * @param size_t size : how many elements should the new capacity be consisted of
 * @return int : 0 on success
 */
int vector_reserve_(void *self, size_t type_size, size_t size);
#define vector_reserve(self,size) vector_reserve_(self,sizeof(*(self)->at),size)

/**
 * @brief Resizes the vector to the given size.
 *        If the new size is bigger than the vector's size, the new elements are not initialized.
 *        If the new size is equal or smaller than the vector's capacity, the capacity remains unchanged.
 * @param void *self : vector to resize
 * @param size_t type_size : size of each element in the vector
 * @param size_t size : new size
 * @return int : 0 on success
 */
int vector_resize_(void *self, size_t type_size, size_t size);
#define vector_resize(self,size) vector_resize_(self,sizeof(*(self)->at),size)

/**
 * @brief Remove an element from the vector
 * @param void *self : vector from which to remove an element
 * @param size_t type_size : size of each element in the vector
 * @param size_t idx : index of element to remove
 * @return int : 0 on success
 */
int vector_remove_(void *self, size_t type_size, size_t idx);
#define vector_remove(self,idx) vector_remove_(self,sizeof(*(self)->at),idx)

/**
 * @brief Removes all elements of the vector. Its capacity is not altered, nor the buffer contents.
 * @param void *self : self The vector to clear
 * @param size_t type_size : size of each element in the vector
 * @return int : 0 on success, non-zero otherwise
 */
void vector_clear_(void* self, size_t type_size);
#define vector_clear(self) vector_clear_(self,sizeof(*(self)->at))

#endif /* LCOM_PROJ_VECTOR_H */
