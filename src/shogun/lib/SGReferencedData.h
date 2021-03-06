/*
 * This software is distributed under BSD 3-clause license (see LICENSE file).
 *
 * Authors: Soeren Sonnenburg, Sergey Lisitsyn, Yuyu Zhang, 
 *          Evangelos Anagnostopoulos
 */
#ifndef __SGREFERENCED_DATA_H__
#define __SGREFERENCED_DATA_H__

#include <shogun/lib/config.h>

#include <shogun/lib/common.h>

namespace shogun
{
class RefCount;

/** @brief shogun reference count managed data */
class SGReferencedData
{
	public:
		/** default constructor */
		SGReferencedData(bool ref_counting=true);

		/** copy constructor */
		SGReferencedData(const SGReferencedData &orig);

		/** move constructor */
		SGReferencedData(SGReferencedData&& orig) noexcept;

		/** override assignment operator to increase refcount on assignments */
		SGReferencedData& operator= (const SGReferencedData &orig);

		/** empty destructor
		 *
		 * NOTE: unref() has to be called in derived classes
		 * to avoid memory leaks.
		 */
		virtual ~SGReferencedData();

		/** display reference counter
		 *
		 * @return reference count
		 */
		int32_t ref_count();

	protected:
		/** copy refcount */
		void copy_refcount(const SGReferencedData &orig);

		/** increase reference counter
		 *
		 * @return reference count
		 */
		int32_t ref();

		/** decrement reference counter and deallocate object if refcount is zero
		 * before or after decrementing it
		 *
		 * @return reference count
		 */
		int32_t unref();

		/** needs to be overridden to copy data */
		virtual void copy_data(const SGReferencedData &orig)=0;

		/** needs to be overridden to initialize empty data */
		virtual void init_data()=0;

		/** needs to be overridden to free data */
		virtual void free_data()=0;

	private:

		/** reference counter */
		RefCount* m_refcount;
};
}
#endif // __SGREFERENCED_DATA_H__
