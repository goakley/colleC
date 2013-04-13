#ifndef STACK_H
#define STACK_H


/** \brief Stack (LIFO) data structure
 *
 * A LIFO Stack.  The Stack will store values of a certain size, determined 
 * upon the Stack's creation.
 */
typedef struct Stack Stack;


/** \brief Creates an empty Stack
 * 
 * Creates an empty Stck, which will hold elements of a certain size.
 * \param[in] size The size of the values that will be stored in this Stack.
 * \return A pointer to an empty Stack; NULL if size is 0
 */
Stack* stack_malloc(size_t size);

/** \brief Destroys a Stack
 *
 * Destroys a Stack.  Note that the Stack does not have to be empty in order 
 * to be eligable for destruction.
 * \param[in,out] stack The Stack to destroy
 */
void stack_free(Stack *stack);

/** \brief Get the number of elements in a Stack
 *
 * \param[in] stack The Stack to query
 * \return The number of elements inside of the Stack
 */
size_t stack_count(const Stack *stack);

/** \brief Get the expected size of the elements in the Stack
 *
 * \param[in] stack The Stack to query
 * \return The expected size of an element in the Stack
 */
size_t stack_esize(const Stack *stack);

/** \brief Pushes a value onto a Stack
 *
 * Pushes a given value onto the top of the given Stack.  The value is 
 * copied into the Stack, so modifying it after pushing will not change what 
 * is stored in the Stack.
 *
 * \param[in,out] stack The Stack that will hold the value
 * \param[in] value The value to push onto the Stack
 * \return 0 on success
 */
int stack_push(Stack *stack, const void *value);

/** \brief Tells the top of a Stack
 *
 * \param[in] stack The Stack to peek at
 * \param[out] value The memory location to copy the top value into
 * \return 0 on success, non-zero if a NULL stack is passed or the stack is 
 *         empty
 */
int stack_peek(const Stack *stack, void *value);

/** \brief Pops the head off a Stack
 *
 * Pops the head off of the given Stack, copying its value into the given 
 * memory location.
 *
 * \param[in,out] stack The Stack to pop off of
 * \param[out] value The memory location to copy the popped value into.
 *             If NULL is passed, the value still be popped.
 * \return 0 on success, non-zero if a NULL stack is passed or the stack is 
 *         empty
 */
int stack_pop(Stack *stack, void *value);


#endif
