/**
 *	@file
 *	@brief class description file vector
 *	@author Den
 *	@version 1.0
 *	@date March 2019
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <fstream>
using namespace std;
#include <assert.h>

//{========================================================================================================
/**
 * 	@class Vector
 * 	@brief Type Vector. Effective in speed, but spends a lot of memory.
 */
template <typename data>
class Vector
	{
		private:

			data* buffer_;	///< pointer to data buffer
			int size_;			///< number of elements in the buffer
			int capacity_;	///< buffer capacity

			int cap_increase = 2;			///< buffer increase ratio
			int cap_decrease = 0.5;		///< buffer decrease ratio

			bool increase();
			bool decrease();

		public:

			Vector();
			Vector(int size);
			Vector(int size, int value);
			Vector(int size, data* arr);
			Vector(const Vector& arr);
			Vector(Vector&& arr);
			~Vector();

			data& operator[](int index) const;
			Vector& operator=(const Vector& array);
			Vector& operator=(Vector&& array);

			void push_back(data elem);
			data pop_back(void);

			void clear(void);
			int size(void) const;
			bool empty(void);

			void *operator new(size_t size, const char* file, const char* func, int line, ofstream& os);
			void operator delete(void *pointer);
	};
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief increases buffer
 *	@detailed increases buffer by cap_increase, if there is not enough space
 *	@return true if increase success
 *					false if increase error
 */
template <typename data>
bool Vector<data>::increase()
	{
		data* ptr = (data* )realloc(buffer_, sizeof(data)*cap_increase*size_);

		if(ptr != NULL)
			{
				buffer_ = ptr;
				capacity_ = cap_increase * size_;
				return true;
			}
		else	return false;
	}
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief decrease buffer
 *	@detailed decrease buffer by cap_decrease, if a lot of free space
 *	@return true if decrease success
 *					false if decrease error
 */
template <typename data>
bool Vector<data>::decrease()
	{
		data* ptr = (data* )realloc(buffer_, sizeof(data)*cap_decrease*size_);

		if(ptr != NULL)
			{
				buffer_ = ptr;
				capacity_ = cap_decrease * size_;
				return true;
			}
		else	return false;
	}
//}========================================================================================================


//{}========================================================================================================
/**
 * 	@brief constructor
 *	@detailed create a Vector with size = 0
 */
template <typename data>
Vector<data>::Vector()
	{
		size_ = 0;
		buffer_ = NULL;
	}

/**
 * 	@brief constructor
 *	@detailed creates a vector with a defined size
 *	@param[in] size size of Vector
 */
template <typename data>
Vector<data>::Vector(int size)
	{
		size_ = size;
		capacity_ = size*cap_increase;
		buffer_ = (data*) calloc(capacity_, sizeof(data));
	}

/**
 * 	@brief constructor
 *	@detailed creates a vector with a defined size. All numbers in the vector are equal value
 *	@param[in] size size of Vector
 * 	@param[in] value the value that fills the Vector
 */
template <typename data>
Vector<data>::Vector(int size, int value)
	{
		size_ = size;
		capacity_ = size*cap_increase;
		buffer_ = (data*) calloc(capacity_, sizeof(data));

		for (int i = 0; i < size; i++)
			buffer_[i] = value;
	}

/**
 * 	@brief constructor
 *	@detailed creates a vector with a defined size. Numbers in the vector are equal numbers in the array arr
 *	@param[in] size size of Vector
 * 	@param[in] arr array that fills the Vector
 */
template <typename data>
Vector<data>::Vector(int size, data* arr)
	{
		size_ = size;
		capacity_ = size*cap_increase;
		buffer_ = (data*) calloc(capacity_, sizeof(data));

		for (int i = 0; i < size; i++)
			buffer_[i] = arr[i];
	}

/**
 * 	@brief copy constructor
 *	@detailed deeply copies one vector to another
 *	@param[in] Vector copy Vector
 */
template <typename data>
Vector<data>::Vector(const Vector& vec)
	{
		size_ = vec.size_;
		capacity_ = size_*cap_increase;
		buffer_ = (data*) calloc(capacity_, sizeof(data));

		for (int i = 0; i < vec.size(); i++)
			buffer_[i] = vec.buffer_[i];

		cout << "copy construct" << endl;
	}

/**
 * 	@brief move constructor
 *	@detailed superficially copies the temporary vector
 *	@param[in] Vector copy Vector
 */
	template <typename data>
	Vector<data>::Vector(Vector&& vec)
		{
			size_ = vec.size();
			capacity_ = size_*cap_increase;
			buffer_ = vec.buffer_;

			vec.size_ = 0;
			vec.buffer_ = NULL;

			cout << "move construct" << endl;
		}
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief destructor
 *	@detailed free Vector
 */
template <typename data>
Vector<data>::~Vector()
	{
		free(buffer_);

		cout << "destruct" << endl;
	}
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief index operator
 *	@detailed returns the value of an item by its index
 *	@param[in] index index
 *	@return value
 */
template <typename data>
data& Vector<data>::operator[](int index) const
	{
		return buffer_[index];
	}
//}========================================================================================================


//{========================================================================================================
/**
 * 	@brief copy operator
 *	@detailed deeply copies one vector to another
 *	@param[in] Vector copy Vector
 */
template <typename data>
Vector<data>& Vector<data>::operator=(const Vector &vector)
	{
		size_ = vector.size_;
		buffer_ = (data* )realloc(buffer_, sizeof(vector.buffer_));

		for(int i = 0; i < vector.size_; i++) buffer_[i] = vector.buffer_[i];

		cout << "copy operator =" << endl;

		return *this;
	}

/**
 * 	@brief move operator
 *	@detailed superficially copies the temporary vector
 *	@param[in] Vector copy Vector
 */
template <typename data>
Vector<data>& Vector<data>::operator=(Vector &&vector)
		{
			size_ = vector.size_;
			buffer_ = vector.buffer_;

			vector.size_ = 0;
			vector.buffer_= 0;

			cout << "move operator =" << endl;

			return *this;
		}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief push
 *	@detailed inserts an element at the end of a Vector
 *	@param[in] elem insert element
 */
template <typename data>
void Vector<data>::push_back(data elem)
	{
		if(size_ < capacity_) buffer_[size_++] = elem;
		else
			if(increase() == true)  buffer_[size_++] = elem;
			else					cout << "Increase error" << endl;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief pop
 *	@detailed returns an element from the end of a vector
 *	@return element
 */
template <typename data>
data Vector<data>::pop_back(void)
	{
		if(size_ < capacity_ / 4)
			if(decrease() == true)  return buffer_[size_--];
			else
				{
					cout << "Decrease error" << endl;
					return NULL;
				}

		return buffer_[size_--];
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief clear Vector
 */
template <typename data>
void Vector<data>::clear(void)
	{
		free(buffer_);
		buffer_ = NULL;
		size_ = 0;
		capacity_ = 0;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@return Vector size
 */
template <typename data>
int Vector<data>::size(void) const
	{
		return size_;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief checks if Vector is empty
 *	@return true if Vector is empty
 *					false if Vector isn't empty
 */
template <typename data>
bool Vector<data>::empty(void)
	{
		return size_ == 0 ? true : false;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief operator NEW
 *	@detailed Made to check for memory leaks. Prints detailed information about its use in a file.
 *	@param[in] size the number of bytes to initialize
 *	@param[in] file the name of the file from which it is called NEW
 *	@param[in] func the name of the function from which it is called NEW
 *	@param[in] line the name of the line from which it is called NEW
 *	@param[in] os information stream
 *	@return pointer to the alloсated place in memory
 */

template <typename data>
void* Vector<data>::operator new(size_t size, const char* file, const char* func, int line, ofstream& os)
	{
		void* pointer = calloc(size, sizeof(char));

		os << "N " << file << "|" << func << "|" << line << " " << pointer << endl;

		return pointer;
	}

	ofstream memory_leak("memory_leak/memory_leak.txt");
	#define NEW new(__FILE__, __func__, __LINE__, memory_leak)
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief operator DELETE
 *	@detailed Made to check for memory leaks. Prints detailed information about its use in a file.
 *	@param[in] pointer pointer to free data
 *	@param[in] file the name of the file from which it is called DELETE
 *	@param[in] func the name of the function from which it is called DELETE
 *	@param[in] line the name of the line from which it is called DELETE
 */

void Vector<data>::operator delete(void *pointer)
	{
		free(pointer);
	}

#define DELETE(x)  memory_leak << "D " << __FILE__ << "|" << __func__ << "|" << __LINE__ << " " << x << endl; \
	 			delete x;
template <typename data>
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief operator Vector + Vector
 * 	@param[in] v1 Vector1
 * 	@param[in] v2 Vector2
 *	@return result Vector
 */
template <typename data>
Vector<data> operator+(const Vector<data> &v1, const Vector<data> &v2)
	{
		assert(v1.size() == v2.size());
		Vector<data> copy(v1.size());

		for(int i = 0; i < v1.size(); i++) copy[i] = v1[i] + v2[i];

		return copy;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief operator Vector - Vector
 * 	@param[in] v1 Vector1
 * 	@param[in] v2 Vector2
 *	@return result Vector
 */
template <typename data>
Vector<data> operator-(const Vector<data> &v1, const Vector<data> &v2)
	{
		assert(v1.size() == v2.size());
		Vector<data> copy(v1.size());

		for(int i = 0; i < v1.size(); i++) copy[i] = v1[i] - v2[i];

		return copy;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief operator Vector * const
 * 	@param[in] v1 Vector1
 * 	@param[in] num const
 *	@return result Vector
 */
template <typename data>
Vector<data> operator*(const Vector<data> &v1, double num)
	{
		Vector<data> copy(v1.size());

		for(int i = 0; i < v1.size(); i++) copy[i] = v1[i] * num;

		return copy;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief operator const * Vector
 * 	@param[in] num const
 * 	@param[in] v1 Vector1
 *	@return result Vector
 */
template <typename data>
Vector<data> operator*(double num, const Vector<data> &v1)
	{
		return v1 * num;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief operator Vector / const
 * 	@param[in] v1 Vector1
 * 	@param[in] num const
 *	@return result Vector
 */
template <typename data>
Vector<data> operator/(const Vector<data> &v1, double num)
	{
		Vector<data> copy(v1.size());

		for(int i = 0; i < v1.size(); i++) copy[i] = v1[i] / num;

		return copy;
	}
//}========================================================================================================


//{========================================================================================================
/**
 *	@brief output operator
 *	@detailed print Vector to os stream
 *	@param[in] os print stream
 *	@param[in] v1 Vector to print
 */
template <typename data>
ostream& operator << (ostream& os, const Vector<data> &v1)
	{
		for(int i = 0; i < v1.size(); ++i)
			os << v1[i] << ' ';
		return os;
	}
//}========================================================================================================

#endif
