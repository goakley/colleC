#ifndef SORTEDLIST_H
#define SORTEDLIST_H


/** \brief A sorted list of values
 *
 * A list that will hold similar values in sorted order, smallest to 
 * largest.  The size of the list's elements is determined on creation, as is 
 * the method of sorting them.
 */
typedef struct SortedList SortedList;


/** \brief Creates a new SortedList
 *
 * Creates a new SortedList that holds elements of a specified size.  The 
 * order of elements will be determined by the passed in comparison function.
 * \param[in] size The size of a single element
 * \param[in] compar The comparator function, which takes two arguments that 
 *            correspond to pointers to two items that could be in the list.  
 *            If the first item goes before the second, the function should 
 *            return <0.  If the first item goes after the second, the 
 *            function should return >0.  If the order of the two items does 
 *            not matter (equivalent), the function should return 0.
 * \return Pointer to an empty SortedList, NULL if a size of 0 was given or 
 *         a NULL function pointer was given
 */
SortedList* sortedlist_malloc(size_t size, 
			      int (*compar)(const void*,const void*));

/** \brief Destroys a SortedList
 *
 * Destroys a SortedList.  The SortedList does not have to be empty to be 
 * eligible for destruction.
 * \param[in,out] sortedlist The SortedList to destroy
 */
void sortedlist_free(SortedList *sortedlist);

/** \brief Get the number of elements in a SortedList
 *
 * \param[in] sortedlist The SortedList to query
 * \return The number of elements inside of the SortedList
 */
size_t sortedlist_count(const SortedList *sortedlist);

/** \brief Get the expected size of the elements in the SortedList
 *
 * \param[in] sortedlist The SortedList to query
 * \return The expected size of an element in the SortedList
 */
size_t sortedlist_esize(const SortedList *sortedlist);

/** \brief Add an element to the SortedList
 *
 * Add an element to the given SortedList.  Duplicate elements are allowed.  
 * NULL values are not accepted into the list.
 * \param[in,out] sortedlist The SortedList to add a value to
 * \param[in] value The value to add to the SortedList.  If NULL, the 
 *            SortedList will not change.
 * \param[out] index The index at which the value resides upon completion of 
 *             this function.  If NULL, the index will not be passed out.
 * \return 0 on success, non-zero if a NULL list/value is passed or if there 
 *         is no room in memory to store the value
 */
int sortedlist_add(SortedList *sortedlist, const void *value, size_t *index);

/** \brief Find an element in the SortedList
 *
 * \param[in] sortedlist The SortedList to query for a value
 * \param[in] key A pointer to the value to search for.  If NULL, the function 
 *            will fail.
 * \param[out] value The value found in the SortedList.  If there are 
 *             multiple results within the list, an arbitrary one is chosen.  
 *             If NULL is passed, the value will not be passed out.
 * \param[out] index The index at which the found value resides.  If NULL is 
 *             passed, the index will not be passed out.
 * \return 0 on success, non-zero if a NULL list/value is passed or if both 
 *         the \p value and \p index pointers are NULL or if no value was 
 *         found.
 */
int sortedlist_find(const SortedList *sortedlist, const void *key, 
		    void *value, size_t *index);

/** \brief Locate an element by its index
 *
 * \param[in] sortedlist The SortedList to query
 * \param[in] index The index of the element
 * \param[out] value The value located in the SortedList
 * \return 0 on success, non-zero if a NULL list is passed or \p index is 
 *         outside the bounds of the list
 */
int sortedlist_element(const SortedList *sortedlist, size_t index, 
		       void *value);

/** \brief Remove an element by its index
 *
 * \param[in] sortedlist The SortedList to modify
 * \param[in] index The index of the element to remove
 * \param[out] value The value being removed from the SortedList
 * \return 0 on success, non-zero if a NULL list is passed or \p index is 
 *         outside the bounds of the list
 */
int sortedlist_remove(SortedList *sortedlist, size_t index, void *value);


#endif
