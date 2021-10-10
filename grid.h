// TO DO:  Write file header.

// TO DO:  Update the member function comments to reflect your own style.

#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Grid {
private:
  struct CELL {

    // Member variables of a cell in a grid
    CELL* Next;      // pointer to the next cell in the row
    T Val;           // templated data type that the cell will hold
    size_t NumCols;  // total # of columns (0..NumCols-1)

    // Constructor for a cell with default values if needed
    CELL(CELL* _Next = nullptr, T _Val = T(), size_t _NumCols = 0) {
      
      // Initialize local variables
      Next = _Next;
      Val = _Val;
      NumCols = _NumCols;
    }
  };

  size_t NumRows;  // total # of rows (0..NumRows-1)
  CELL** Rows;     // C array of linked lists

public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 Grid.  All
  // elements are initialized to the default value of T.
  //
  Grid() {
    // initialize 4 rows
    Rows = new CELL*[4];
    NumRows = 4;

    // allocate the first cell of the linked list with default value:
    for (size_t r = 0; r < NumRows; ++r) {
        // The first cell in each row is given the NumCols value of 4
        Rows[r] = new CELL(nullptr, T(), 4);

        // Set a pointer to the current cell in the current row
        CELL* cur = Rows[r];

        // create the linked list for this row.
        for(size_t c = 1; c < Rows[r]->NumCols; ++c) {
            // create the second cell and beyond
            cur->Next = new CELL(nullptr, T());

            // Move to the cell we just created so we can repeat the process.
            cur = cur->Next;
        }
    }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a Grid with R rows,
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  Grid(size_t R, size_t C) {
    
    if(R < 0 || C < 0) {
      throw runtime_error("Grid(R,C): Invalid Dimensions Supplied!");
    }

    // Start by setting the number of rows and the size variable
    Rows = new CELL*[R];
    NumRows = R;

    // Now, create each row
    for(size_t r = 0; r < NumRows; ++r) {
      // Only the first cell in each row gets the NumCols attribute set to a non-default value
      Rows[r] = new CELL(nullptr, T(), C);

      // Get ready to traverse
      CELL* curr = Rows[r];

      for(size_t c = 1; c < Rows[r]->NumCols; ++c) {
        // Create a new cell without the NumCols value
        curr->Next = new CELL(nullptr, T());

        // Advance to the next cell
        curr = curr->Next;
      }
    } 
  }
    
  //
  // destructor:
  //
  // Called automatically by C++ to free the memory associated by the vector.
  //
  virtual ~Grid() {
      // Delete the grid
      deleteGrid();
  }


  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a Grid that contains a
  // copy of an existing Grid.  Example: this occurs when passing
  // Grid as a parameter by value
  //
  //   void somefunction(Grid<int> G2)  <--- G2 is a copy:
  //   { ... }
  //
  Grid(const Grid<T>& other) {
    // Copy the data from the incoming other grid to a new grid
    copyData(other);    
  }
    
  //
  // copy operator=
  //
  // Called when you assign one vector into another, i.e. this = other;
  //
  Grid& operator=(const Grid& other) {
      
      // Assigning us to ourselves check
      if(this == &other) {
        return *this;
      }

      // Free up memory if the grid's size is > 0
      deleteGrid();

      // Now copy the data over from the other grid to this grid
      copyData(other);

      // Return the completed copy
      return *this;
  }

  void copyData(const Grid<T>& other) {
    
    // New up memory for the incoming spec
    this->Rows = new CELL* [other.NumRows];
    this->NumRows = other.NumRows;

    // Copy over all data
    for(size_t r = 0; r < this->NumRows; ++r) {

      // Get two parallel pointers ready for the copy
      this->Rows[r] = other.Rows[r];

      // Parallel pointers for each grid
      CELL* otherCurr = other.Rows[r];
      CELL* thisCurr = this->Rows[r];

      for(size_t c = 1; c < this->Rows[r]->NumCols; ++c) {
        
        // Copy all remaining cells in the row
        thisCurr->Next = otherCurr->Next;
        thisCurr->Next->Val = otherCurr->Next->Val;
        thisCurr->Next->NumCols = otherCurr->Next->NumCols;

        // Advance both pointers
        thisCurr = thisCurr->Next;
        otherCurr = otherCurr->Next;
      }
    }
  }

  void deleteRow(size_t& r) {
    
    while(this->Rows[r]->NumCols > 1) {
      // Parallel pointers that we can walk down the list.
      CELL* prev = nullptr;
      CELL* curr = this->Rows[r];

      // Go through each column
      while(curr->Next != nullptr) {
        // Walk to the end of the row
        prev = curr;
        curr = curr->Next;
      }
      // Delete the current node
      delete curr;
      // Set the prior node's next pointer to nullptr;
      prev->Next = nullptr;
      --this->Rows[r]->NumCols;
    }
    // Delete the final cell in the row.
    delete this->Rows[r];
    this->Rows[r] = nullptr;
  }

  void deleteGrid() {

    // Check if there's any data at all. If not, we don't need to do anything.
    if(this->NumRows > 0) {
      // Delete each row in the grid
      for(size_t r = 0; r < this->NumRows; ++r) {
        deleteRow(r);
      }
      // Delete the Rows as well.
      delete[] Rows;
    } else {
      // If the size was zero, just delete the empty rows array
      delete[] Rows;
    }    
  }

  //
  // numrows
  //
  // Returns the # of rows in the Grid.  The indices for these rows
  // are 0..numrows-1.
  //
  size_t numrows() const {
    // The number of rows should be a safe bet.
    return this->NumRows;
  }
  

  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  For now, each row will have the same number of columns.
  //
  size_t numcols(size_t r) const {
      // Make sure there's no funny business going on.
      if(r >= this->NumRows || r < 0) {
        throw runtime_error("Row index out of bounds!");
      } else {
        return this->Rows[r]->NumCols;
      }
  }


  //
  // size
  //
  // Returns the total # of elements in the grid.
  //
  size_t size() const {
      
      // If there's no rows, then there's no elements
      if(this->NumRows == 0) {
        return 0;
      } else if(this->NumRows > 0 && this->Rows[0] == nullptr) {
        // If there's rows, but no columns, there's no elements
        return 0;
      } else if (this->NumRows > 0 && this->Rows[0]->NumCols == 0) {
        // If there's rows and zero columns explicitly, there's not elements
        return 0;
      } else if (this->NumRows > 0 && this->Rows[0]->NumCols != 0) {
        // If there's rows and columns, there's elements
        return this->NumRows * this->Rows[0]->NumCols;
      } else {
        throw runtime_error("Cannot obtain size for given grid!");
      }
  }


  //
  // ()
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    grid(r, c) = ...
  //    cout << grid(r, c) << endl;
  //
  T& operator()(size_t r, size_t c) {
      
      // How we know that the user is requesting a bad row.
      bool invalidRow = (r >= NumRows || r < 0);

      // Defense, first and foremost.
      if(invalidRow) {
        throw runtime_error("Error: Invalid Row Index!");
      } else {
        // How we know the user is requesting a bad column.
        bool invalidCol = (c >= this->Rows[0]->NumCols || c < 0);
        
        if (invalidCol) {
          throw runtime_error("Error: Invalid Column Index!");
        } else {
        // Set up access to the first cell in the row that the user wanted.
        // The -1 is to compensate for the fact that the grid is 0 indexed
        CELL* curr = Rows[r];

        // The -1 is to compensate for the fact that the columns are 0 indexed.
        for(int x = 0; x < c; ++x) {
          // Walk until we hit the column the user wants.
          curr = curr->Next;
        }
        // Return the value stored in that cell.
        return curr->Val;
      }
    }
  }

  //
  // _output
  //
  // Outputs the contents of the grid; for debugging purposes.  This is not
  // tested.
  //-1
  void _output() {

    // Check the number of rows
    if(this->NumRows > 0) {

      // Check the number of columns
      if(this->Rows[0]->NumCols > 0) {

        // Header
        cout << "Grid Contents:" << endl;
        cout << "Columns:\t";

        // Print out the column numbers
        for(int y = 0; y < this->Rows[0]->NumCols; ++y) {
          cout << y << " ";
        }

        // Formatting
        cout << endl;

        // Start printing out all of the row contents
        for(int x = 0; x < NumRows; ++x) {
          
          // Start of the row
          CELL* curr = this->Rows[x];

          // More formatting          
          cout << x << ":\t\t";

          // Traverse the row.
          for(int j = 0; j < this->Rows[x]->NumCols; ++j) {
            cout << curr->Val << " ";
            curr = curr->Next;
          }
          // New line for each row
          cout << endl;
        }
      }
    }
  }
};
