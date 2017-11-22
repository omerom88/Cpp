//============================================================================
// Name : Matrix.h
// Author : omer rom
// Version :
// Copyright : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef MATRIX_H_
#define MATRIX_H_
#include <iostream>
#include <vector>
#include <exception>
#include <math.h>
#include "MatrixSquareException.h"
#include "IlegalUseException.h"
#define FIRST 1
#define SECONDE 2
using namespace std;

template<typename T>
class Matrix;
template<typename T>
/**
 * operator << print a matrix assume that type T has << operator by itself. print each cell in the matrix,
 * with a tab ('\t') between cells, and new line between columns (and at the end of the matrix) except for Matrix<char>,
 * than this operator prints no spaces between cells, and a single space between columns.
 */
std::ostream& operator<<(std::ostream&, const Matrix<T>&);
template <class T>
/**
 * The Matrix class this class holds a matrix.
 */
class Matrix
{
public:
	vector<T> vec;
	unsigned int length;
	/**
	 * Default constructor for the class
	 */
	Matrix()
	{
		cols = FIRST;
		rows = FIRST;
		T defaultVal = T();
		vec.push_back(defaultVal);
		length = rows * cols;
	}
	/**
	 * Construct a matrix by size rowsXcols using values from cells.
	 */
	Matrix(unsigned int newRows, unsigned int newColoms, const vector<T> cells)
	{
		if(newRows == FIRST || newColoms == FIRST)
		{
			throw IlegalUseException();
		}
		cols = newColoms;
		rows = newRows;
		vec = cells;
		length = rows * cols;
	}
	/**
	 * Copy constructor for Matrix class performs deep copy of the matrix.
	 */
	Matrix(const Matrix<T> &other)
	{
		cols = other.cols;
		rows = other.rows;
		vec = other.vec;
		length = rows * cols;
	}
	/**
	 * Move constructor for Matrix class copy the matrix.
	 */
	Matrix(Matrix<T> && other)
	{
		rows = other.rows;
		cols = other.cols;
		vec = other.vec;
		length = rows * cols;
		other.rows = FIRST;
		other.cols = FIRST;
		other.length = FIRST;
		other.vec.clear();
	}
	/**
	 * Calc the trace of the matrix the trace of a matrix is the sum of it's main diagonal,
	 * the diagonal from the upper left to the lower right.
	 * if can't calc trace throws an exeption.
	 */
	T trace() const
	{
		if (cols != rows)
		{
			throw MatrixSquareException();
		}
		T init = T();
		for(unsigned int i = 0 ; i < rows ; ++i)
		{
			T temporary = vec.at(i * cols + i);
			init = init + temporary;
		}
		return init;
	}
	/**
	 * Calc the determinant of the matrix.
	 * I didn't have time to build this function. see attached README.
	 */
	T det() const 
	{
		T temp = T();
		return temp;	
	}
	
	/**
	 * Returns the transpose of the matrix.
	 */
	Matrix transpose() const
	{
		vector<T> tempVec;
		for(unsigned int i = 0; i < cols; ++i)
		{
			for(unsigned int j = 0; j < rows; ++j)
			{
				T temporary = vec.at(j * cols + i);
				tempVec.push_back(temporary);
			}
		}
		return Matrix(cols, rows, tempVec);
	}
	/**
	 * Operator- returns val by val differnce of matrixes
	 */
	Matrix operator-(const Matrix& other)const
	{
		if(cols != other.cols || rows != other.rows)
		{
			throw IlegalUseException();
		}
		vector<T> tempVec;
		for(unsigned int i = 0; i < length; i++)
		{
			tempVec.push_back(vec.at(i) - other.vec.at(i));
		}
		return Matrix(rows, cols, tempVec);
	}
	/**
	 * Operator-= val by val differnce of matrixes
	 */
	Matrix& operator-=(const Matrix& other)
	{
		Matrix temp = *this - other;
		*this = temp;
		return *this;
	}
	/**
	 * operator+ returns val by val addition of matrixes
	 */
	Matrix operator+(const Matrix& other)const
	{
		vector<T> tempVec;
		if(cols != other.cols || rows != other.rows)
		{
			throw IlegalUseException();
		}
		for(unsigned int i = 0; i < length; i++)
		{
			tempVec.push_back(vec.at(i) + other.vec.at(i));
		}
		return Matrix(rows, cols, tempVec);
	}
	/**
	 * Operator+= val by val addition of matrixes
	 */
	Matrix& operator+=(const Matrix& other)
	{
		Matrix temp = *this + other;
		*this = temp;
		return *this;
	}
	/**
	 * Operator* returns dot product of matrixes each cell in the resulting matrix is the sum of
	 * multiplies any cell in the equivalent column in the cell of the equivalent row.
	 * if the matrixes can't be multiply throws an exception.
	 */
	Matrix operator*(const Matrix& other) const
	{
		T temp = T();
		vector<T> tempVec(length);
		if(cols != other.rows)
		{
			throw IlegalUseException();
		}
		for(unsigned int i = 0; i < other.cols; ++i)
		{
			for(unsigned int j = 0; j < rows; j++)
			{
				T sum = temp;
				for(unsigned int k = 0; k < cols; ++k)
				{
					T temporary = vec.at(j * cols + k);
					T temporary2 = other.vec.at(k * other.cols + i);
					sum = sum + (temporary * temporary2);
				}
				tempVec.at(j * other.cols + i) = sum;
			}
		}
		return Matrix(rows, other.cols, tempVec);
	}
	/**
	 * Operator= do a deep copy of another matrix into this one
	 */
	Matrix operator= (Matrix &other)
	{
		rows = other.getNumOfRows();
		cols = other.getNumOfCols();
		vec = other.vec;
		return *this;
	}
	/**
	 * Operator*= dot product of matrixes
	 */
	Matrix& operator*=(const Matrix& other)
	{
		Matrix temp = *this * other;
		*this = temp;
		return *this;
	}
	/**
	 * Operator!= returns true iff two matrixes are different
	 */
	bool operator!= (const Matrix &other) const
	{
		return (!(*this == other));
	}
	/**
	 * Operator== returns true iff both matrixes are equal
	 */
	bool operator== (const Matrix &other) const
	{
		if(cols != other.cols || rows != other.rows)
		{
			throw IlegalUseException();
		}
		for(unsigned int i = 0; i < vec.size(); i++)
		{
			if(vec[i] != other.vec[i])
			{
				return false;
			}
		}
		return true;
	}
	/**
	 * Get the number of rows in this matrix
	 */
	unsigned int getNumOfRows() const
	{
		return rows;
	}
	/**
	 * Get the number of columns in this matrix
	 */
	unsigned int getNumOfCols() const
	{
		return cols;
	}
	/**
	 * Operator() returns the value in the [row, col] cell of the matrix
	 */
	T operator()(int row, int col) const
	{
		return vec.at(row * cols + col);
	}
	/**
	 * Operator() returns a reference to the value in the [row, col] cell of the matrix
	 */
	T& operator()(int row, int col)
	{
		return vec.at(row * cols + col);
	}
	/**
	 * Map run function on every item of the matrix. returns a matrix of item item result.
	 */
	Matrix map (T(*func)(const T)) const
	{
		vector<T> tempVec;
		for(unsigned int i = 0; i < rows * cols ; ++i)
		{
			tempVec.push_back(func(vec.at(i)));
		}
		return Matrix(rows, cols, tempVec);
	}
	/**
	 * Nested iterator class
	 */
	class iterator
	{
	public:
		/**
		 * iterator default ctor
		 */
		iterator():location(){}
		/**
		 * iterator ctor
		 */
		iterator(T* loc): location(loc){}
		/**
		 * Operator ++i for moving forward in the iterator
		 */
		iterator operator++(int)
		{
			iterator temp = this;
			location++;
			return temp;
		}
		/**
		 * Operator i++ for moving forward in the iterator
		 */
		iterator operator++()
		{
			location++;
			return *this;
		}
		/**
		 * Operator* for de-reference.
		 */
		T& operator*()
		{
			return *location;
		}
		/**
		 * Operator-> to return the location in the memory of the iterator.
		 */
		T* operator->()
		{
			return location;
		}
		/**
		 * Operator== to compare iterators.
		 */
		bool operator==(const iterator& toCompare)
		{
			return location == toCompare.location;
		}
		/**
		 * Operator!= compare iterators (Not).
		 */
		bool operator!=(const iterator& toCompare)
		{
			return !(location == toCompare.location);
		}
	private:
		T* location;
	};
	/**
	 * Return an iterator over all the matrix cells, start from the first row.
	 * this iterator support the copy, assignment, increment, equality/inequality
	 * this and dereferencing operators.
	 */
	iterator begin()
	{
		return iterator(&this->vec[0]);
	}
	/**
	 * Returns an iterator pointing to the past-the-end cell in the matrix
	 */
	iterator end()
	{
		return &this->vec[this->vec.size()];
	}
	/**
	 * Nested constant iterator class
	 */
	class const_iterator
	{
	public:
		/**
		 * const_iterator default ctor
		 */
		const_iterator():location() , temp(), jump(), cnt(){}
		/**
		 * const_iterator ctor
		 */
		const_iterator(T* loc, int rowSize, int jum)
		{
			location = loc;
			if(jum == 1)
			{
				jump = 1;
				temp = rowSize;
				rowsIterator();
			}
			else
			{
				jump = rowSize;
				temp = jum;
				T* loc = location;
				colIterator();
				location = loc + 1;
			}
			cnt = 1;
		}
		/**
		 * Operator ++i for moving forward in the iterator
		 */
		const_iterator operator++(int)
		{
			const_iterator temp = *this;
			if(jump == 1)
			{
				rowsIterator();
			}
			else
			{
				cnt++;
				T* loc = location;
				location = colIterator();
				if(cnt == jump)
				{
					location++;
				}
				else
				{
					location = loc + 1;
				}

			}
			return temp;
		}
		/**
		 * Operator i++ for moving forward in the iterator
		 */
		const_iterator operator++()
		{
			if(jump == 1)
			{
				rowsIterator();
			}
			else
			{
				cnt++;
				T* loc = location;
				location = colIterator();
				if(cnt == jump)
				{
					location++;
				}
				else
				{
					location = loc + 1;
				}

			}
			return *this;
		}
		/**
		 * Operator* for de-reference
		 */
		const vector<T> operator*()
		{
			return constVec;
		}
		/**
		 * Operator-> to return the location in the memory of the iterator.
		 */
		const vector<T>* operator->()
		{
			return &constVec;
		}
		/**
		 * Operator== to compare iterators.
		 */
		bool operator==(const const_iterator& toCompare)
		{
			return location == toCompare.location;
		}
		/**
		 * Operator!= compare iterators (Not).
		 */
		bool operator!=(const const_iterator& toCompare)
		{
			return !(location == toCompare.location);
		}
		/**
		 * Function for iterate on rows
		 */
		void rowsIterator()
		{
			constVec.clear();
			for(int j = 0; j < temp ; j++)
			{
				T temp = *location;
				constVec.push_back(temp);
				location++;
			}
		}
		/**
		 * Function for iterate on columns
		 */
		T* colIterator()
		{
			constVec.clear();
			for(int j = 0; j < temp; j++)
			{
				T temp = *location;
				constVec.push_back(temp);
				location += jump;
			}
			location -= jump;
			return location;
		}
		vector<T> constVec;
		T* location;
	private:
		int jump;
		int temp;
		int cnt;
	};
	/**
	 * Returns an iterator over all the matrix cells, start from the first
	 */
	const_iterator rowIteratorBegin ()
	{
		return const_iterator(&vec[0], cols, 1);
	}
	/**
	 * Returns an iterator over all the matrix cells, start from the past-end
	 */
	const_iterator rowIteratorEnd ()
	{
		return const_iterator(&vec[vec.size()], cols, 1);
	}
	/**
	 * Returns an iterator over all the matrix cells by colls, start from the first
	 */
	const_iterator colIteratorBegin ()
	{
		return const_iterator(&vec[0], cols, rows);
	}
	/**
	 * Returns an iterator over all the matrix cells by colls, start from the past-end
	 */
	const_iterator colIteratorEnd ()
	{
		return const_iterator(&vec[vec.size()], cols, rows);
	}
	/**
	 * operator- returns val by val negatives of a matrix
	 */
	friend Matrix<T> operator- (const Matrix< T > & self)
	{
		vector<T> tempVec ;
		for( unsigned int i = 0 ; i < self.vec.size(); ++i)
		{
			tempVec.push_back(self.vec.at(i) * -1);
		}
		return Matrix(self.getNumOfRows() , self.getNumOfCols() , tempVec);
	}
private:
	unsigned int rows;
	unsigned int cols;
};
/**
 * operator << print a matrix assume that type T has << operator by itself. print each cell in the matrix,
 * with a tab ('\t') between cells, and new line between columns (and at the end of the matrix) except for Matrix<char>,
 * than this operator prints no spaces between cells, and a single space between columns.
 */
template< typename T>
ostream& operator<<(ostream& os, const Matrix<T>& toprint)
{
	for(unsigned i = 0; i < toprint.getNumOfRows() ; ++i)
	{
		for(unsigned j = 0; j < toprint.getNumOfCols(); ++j)
		{
			if(i == toprint.getNumOfRows() - 1 && j == toprint.getNumOfCols() - 1)
			{
				T temporary = toprint.vec.at(i * toprint.getNumOfCols() + j);
				os << temporary;
			}
			else
			{
				T temporary = toprint.vec.at(i * toprint.getNumOfCols() + j);
				os << temporary;
				if(j + 1 != toprint.getNumOfCols())
				{
					os << "\t";
				}
			}
		}
		os << "\n";
	}
	return os;
}
/**
 * operator<< for Char to print a matrix.
 */
template <>
ostream& operator<<(ostream& os, const Matrix<char>& toprint)
{
	for(unsigned i = 0; i < toprint.getNumOfRows() ; ++i)
	{
		for(unsigned j = 0; j < toprint.getNumOfCols(); ++j)
		{
			os << toprint(i, j);
		}
		if(toprint.getNumOfRows() != i + 1)
		{
			os << " ";
		}
	}
	os << "\n";
	return os;
}

#endif // MATRIX_H_
