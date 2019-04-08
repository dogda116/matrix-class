# matrix-class
C++ matrix class. Elements are stored in std::vector<std::vector<T>>.

**Features:**
  * Template type of elements
  * Constructs new matrix from correct std::vector<std::vector<T>>
  * Function *size* returns std::pair<size_t, size_t> of (number of rows, number of columns).
  * Function *transpose* (changes given argument)
  * Function *transposed* (doesn't change given argument but returns new matrix)
  * Arithmetic operators +, * and respective +=, *=
  * Operator << prints matrix in output stream
  
  ##### MatrixIterator class:
  * begin() and end() to iterate through elements of matrix by rows
  * Comparison operators == and != for iterators
  * Operator ++
