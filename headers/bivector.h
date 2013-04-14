#ifndef BIVECTOR_H
#define BIVECTOR_H


/** \brief Bit Vector (array of binaries) data type
 *
 * A vector that holds binary values; each entry in the vector is either a 1 
 * or a 0.
 */
typedef struct Bivector Bivector;


/** \brief Create a Bivector either set or cleared
 *
 * Creates a new bit vector with a specific size, either completely set or 
 * completely cleared.
 * \param[in] count The number of binary values the vector can hold
 * \param[in] set 0 to initialize the vector as cleared, non-zero to 
 *            to initialize as set
 * \return A pointer to a new Bivector; NULL if count is 0
 */
Bivector* bivector_malloc(size_t count, unsigned char set);

/** \brief Destroy a Bivector
 *
 * \param[in,out] biv The bivector to free from memory
 */
void bivector_free(Bivector *biv);

/** \brief Change the capacity of a bivector
 *
 * \param[in,out] biv The Bivector whose capacity to alter
 * \param[in] count The new capacity of the Bivector
 * \param[in] set If \p count is greater than the old capacity, set the new 
 *            elements if non-zero / clear if 0
 * \return 0 on success, 1 if a NULL Bivector was passed or \p count is 0
 */
int bivector_resize(Bivector *biv, size_t count, unsigned char set);

/** \brief Set a range of bits in a Bivector
 *
 * Sets (1s) a range of bits in a Bivector, starting at index \p min and 
 * going up to and including index \p max.  If max is less than min, nothing 
 * will change.
 * \param[in,out] biv The Bivector to alter
 * \param[in] min The index at which to begin setting bits (inclusive)
 * \param[in] max The index at which to stop setting bits (inclusive)
 */
void bivector_set(Bivector *biv, size_t min, size_t max);

/** \brief Clear a range of bits in a Bivector
 *
 * Clears (0s) a range of bits in a Bivector, starting at index \p min and 
 * going up to and including index \p max.  If max is less than min, nothing 
 * will change.
 * \param[in,out] biv The Bivector to alter
 * \param[in] min The index at which to begin clearing bits (inclusive)
 * \param[in] max The index at which to stop clearing bits (inclusive)
 */
void bivector_clear(Bivector *biv, size_t min, size_t max);

/** \brief Toggle a range of bits in a Bivector
 *
 * Toggles (flips) a range of bits in a Bivector, starting at index \p min and 
 * going up to and including index \p max.  If max is less than min, nothing 
 * will change.
 * \param[in,out] biv The Bivector to alter
 * \param[in] min The index at which to begin toggling bits (inclusive)
 * \param[in] max The index at which to stop toggling bits (inclusive)
 */
void bivector_toggle(Bivector *biv, size_t min, size_t max);

/** \brief Extract a range of bits from a Bivector
 *
 * Extracts (tests) bits from a Bivector.
 * \param[in] biv The Bivector to extract from
 * \param[in] min The index at which to start the extraction (inclusive)
 * \param[in] max The index at which to stop the extraction (inclusive)
 * \param[out] result The memory location at which to place the values 
 *             extracted from the Bivector
 * \return The value of the first bit in the vector (0 or 1), 0 if the range 
 *         is invalid or a valid Bivector was not passed
 */
unsigned char bivector_test(const Bivector *biv, size_t min, size_t max, 
			    unsigned char* result);


#endif
