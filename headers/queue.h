#ifndef QUEUE_H
#define QUEUE_H


/** \brief FIFO Queue data structure
 *
 * A FIFO Queue.  The Queue will store values of a certain size, determined 
 * upon the Queue's creation.
 */
typedef struct Queue Queue;


/** \brief Creates an empty Queue
 * 
 * Creates an empty Queue, which will hold elements of a certain size.
 * \param[in] size The size of the values that will be stored in this Queue.
 * \return A pointer to an empty Queue; NULL if size is 0
 */
Queue* queue_malloc(size_t size);

/** \brief Destroys a Queue
 *
 * Destroys a Queue.  Note that the Queue does not have to be empty in order 
 * to be eligable for destruction.
 * \param[in,out] queue The Queue to destroy
 */
void queue_free(Queue *queue);

/** \brief Get the number of elements in a Queue
 *
 * \param[in] queue The Queue to query
 * \return The number of elements inside of the Queue
 */
size_t queue_count(const Queue *queue);

/** \brief Get the expected size of the elements in the Queue
 *
 * \param[in] queue The Queue to query
 * \return The expected size of an element in the Queue
 */
size_t queue_esize(const Queue *queue);

/** \brief Enqueues a value onto a Queue
 *
 * Enqueues a given value onto the end of the given Queue.  The value is 
 * copied into the Queue; modifying the value after enqueuing it will not 
 * change its value in the Queue.
 *
 * \param[in,out] queue The Queue that will hold the value
 * \param[in] value The value that wil be added to the end of the Queue.
 * \return 0 on success
 */
int queue_enqueue(Queue *queue, const void *value);

/** \brief Tells the head of a Queue
 *
 * \param[in] queue The Queue to peek at
 * \param[out] value The memory location to copy the head value into.
 * \return 0 on success, non-zero if a NULL queue is passed or the queue is 
 *         empty
 */
int queue_peek(const Queue *queue, void *value);

/** \brief Removes the head of a Queue
 *
 * Dequeues the head of the given Queue, copying its value into the given 
 * memory location.
 *
 * \param[in,out] queue The Queue to dequeue a value from
 * \param[out] value The memory location to copy the dequeued value into.
 *             If NULL is passed, the value still be dequeued.
 * \return 0 on success, non-zero if a NULL queue is passed or the queue is 
 *         empty
 */
int queue_dequeue(Queue *queue, void *value);


#endif
