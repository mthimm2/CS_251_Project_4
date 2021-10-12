#include <gtest/gtest.h>

#include <map>
#include <set>
#include <sstream>
#include <vector>
#include "maze.h"
#include "grid.h"
#include "EscapeTheLabyrinth.h"

TEST(grid, defaultConstructor) {
  // TO DO:  Write 100s of asserts per member function.

  // Instantiate a grid using the default constructor
  Grid<int> g;

  // Number of rows should be 4 for the default constructor.
  ASSERT_EQ(g.numrows(), 4);
  ASSERT_TRUE(!(g.numrows() < 4));
  ASSERT_TRUE(!(g.numrows() > 4));

  // Number of columns check with good behavior
  ASSERT_EQ(g.numcols(0), 4);
  ASSERT_EQ(g.numcols(1), 4);
  ASSERT_EQ(g.numcols(2), 4);
  ASSERT_EQ(g.numcols(3), 4);

  // Another way to make sure the number of columns is 4
  ASSERT_TRUE(!(g.numcols(0) > 4) && !(g.numcols(0) < 4));
  ASSERT_TRUE(!(g.numcols(1) > 4) && !(g.numcols(1) < 4));
  ASSERT_TRUE(!(g.numcols(2) > 4) && !(g.numcols(2) < 4));
  ASSERT_TRUE(!(g.numcols(3) > 4) && !(g.numcols(3) < 4));

  // Bad access attempt for NumCols check.
  ASSERT_ANY_THROW(!(g.numcols(4) > 4) && !(g.numcols(4) < 4));

  // A bad index check of the number of columns
  ASSERT_ANY_THROW(g.numcols(4));

  // A good index check for the number of columns
  // shouldn't produce a throw.
  ASSERT_NO_THROW(g.numcols(3));

  // Now, some grids of different data types
  Grid<double> d;
  Grid<string> s;

  // A composed data type grid.
  Grid<map<int, int> > crazy;

  // Make sure that any data type gets treated the same.
  // NumCols should = 4
  ASSERT_EQ(d.numcols(0), 4);
  ASSERT_EQ(s.numcols(0), 4);
  ASSERT_EQ(crazy.numcols(0), 4);

  // Number of rows should = 4
  ASSERT_EQ(d.numrows(), 4);
  ASSERT_EQ(s.numrows(), 4);
  ASSERT_EQ(crazy.numrows(), 4);
}

TEST(grid, parameterizedConstructorInt) {
  // create a mix of grids with varying dimensions.
  // Some of these should produce bad behavior
  Grid<int> a(1, 1);
  Grid<int> b(1, 2);
  Grid<int> c(2, 2);
  Grid<int> d(0, 1);
  Grid<int> e(1, 0);

  // Check certain aspects of grid a
  // cout << "Starting Paramerized Constructor Tests" << endl;
  // cout << "testing a" << endl;
  ASSERT_EQ(a.numrows(), 1);
  ASSERT_EQ(a.numcols(0), 1);
  ASSERT_NE(a.numcols(0), 4);
  ASSERT_NE(a.numrows(), 4);
  ASSERT_ANY_THROW(a.numcols(1));

  // check aspects of grid b
  // cout << "testing b" << endl;
  ASSERT_EQ(b.numrows(), 1);
  ASSERT_EQ(b.numcols(0), 2);
  ASSERT_NE(b.numcols(0), 4);
  ASSERT_NE(b.numrows(), 2);
  ASSERT_ANY_THROW(b.numcols(2));

  // // Check aspects of grid c
  // cout << "testing c" << endl;
  ASSERT_EQ(c.numrows(), 2);
  ASSERT_EQ(c.numcols(0), 2);
  ASSERT_EQ(c.numcols(1), 2);
  ASSERT_NE(c.numrows(), 3);
  ASSERT_ANY_THROW(c.numcols(2));

  // Check aspects of grid d
  // cout << "testing d" << endl;
  ASSERT_EQ(d.numrows(), 0);
  ASSERT_ANY_THROW(d.numcols(0));
  ASSERT_ANY_THROW(d.numcols(1));
  ASSERT_NE(d.numrows(), 1);

  // cout << "testing e" << endl;
  ASSERT_EQ(e.numrows(), 1);
  ASSERT_NE(e.numrows(), 4);
  ASSERT_EQ(e.numcols(0), 0);
  ASSERT_ANY_THROW(e.numcols(1));
  // cout << "Finished Parameterized Constructor int tests" << endl;
}

TEST(grid, parameterizedConstructor) {
  // Grids of different data types with wild dimensions
  Grid<string> a(57, 12);
  Grid<double> b(498, 861);
  Grid<float> c(41, 0);
  Grid<char> d(0, 8345);
  Grid<vector<map<int, int> > > crazy(19, 62);

  // cout << "Starting Varied Paramerized Constructor Tests" << endl;

  // tests for grid a
  // cout << "testing varied a" << endl;
  ASSERT_EQ(a.numrows(), 57);
  ASSERT_EQ(a.numcols(0), 12);
  ASSERT_EQ(a.numcols(1), 12);
  ASSERT_EQ(a.numcols(2), 12);
  ASSERT_EQ(a.numcols(3), 12);
  ASSERT_EQ(a.numcols(4), 12);
  ASSERT_EQ(a.numcols(5), 12);
  ASSERT_EQ(a.numcols(6), 12);
  ASSERT_EQ(a.numcols(7), 12);
  ASSERT_EQ(a.numcols(8), 12);
  ASSERT_EQ(a.numcols(11), 12);
  ASSERT_NE(a.numrows(), 4);
  ASSERT_ANY_THROW(a.numcols(58));

  // tests for b
  // cout << "testing varied b" << endl;
  ASSERT_EQ(b.numrows(), 498);
  ASSERT_EQ(b.numcols(0), 861);
  ASSERT_EQ(b.numcols(200), 861);
  ASSERT_EQ(b.numcols(497), 861);
  ASSERT_ANY_THROW(b.numcols(498));
  ASSERT_NE(b.numrows(), 4);
  ASSERT_NE(b.numcols(0), 4);

  // tests for c
  // cout << "testing varied c" << endl;
  ASSERT_EQ(c.numrows(), 41);
  ASSERT_NE(c.numrows(), 4);
  ASSERT_EQ(c.numcols(0), 0);
  ASSERT_EQ(c.numcols(20), 0);
  ASSERT_EQ(d.numrows(), 0);
  ASSERT_NE(d.numrows(), 4);
  ASSERT_ANY_THROW(d.numcols(0));
  ASSERT_ANY_THROW(d.numcols(1));

  // tests for crazy
  // cout << "testing varied crazy" << endl;
  ASSERT_EQ(crazy.numrows(), 19);
  ASSERT_NE(crazy.numrows(), 4);
  ASSERT_EQ(crazy.numcols(0), 62);
  ASSERT_EQ(crazy.numcols(10), 62);
  ASSERT_EQ(crazy.numcols(18), 62);
  ASSERT_ANY_THROW(crazy.numcols(19));
  // cout << "Finished Parameterized Constructor Varied tests" << endl;
}

TEST(grid, numRows) {
  Grid<set<int>*> a(57, 12);
  Grid<unsigned int> b(498, 861);
  Grid<long long> c(41, 0);
  Grid<short> d(0, 8345);
  Grid<map<int, vector<set<string> > > > crazy(19, 62);
  Grid<int> plainJane;

  // cout << "Testing numrows" << endl;

  // test a
  // cout << "testing numrows a" << endl;
  ASSERT_EQ(a.numrows(), 57);
  ASSERT_NE(a.numrows(), 4);
  ASSERT_FALSE(a.numrows() != 57);

  // test b
  // cout << "testing numrows b" << endl;
  ASSERT_EQ(b.numrows(), 498);
  ASSERT_NE(b.numrows(), 4);
  ASSERT_FALSE(b.numrows() != 498);

  // test c
  // cout << "testing numrows c" << endl;
  ASSERT_EQ(c.numrows(), 41);
  ASSERT_NE(c.numrows(), 4);
  ASSERT_FALSE(c.numrows() != 41);

  // test d
  // cout << "testing numrows d" << endl;
  ASSERT_EQ(d.numrows(), 0);
  ASSERT_NE(d.numrows(), 4);
  ASSERT_FALSE(d.numrows() != 0);

  // test crazy
  // cout << "testing numrows crazy" << endl;
  ASSERT_EQ(crazy.numrows(), 19);
  ASSERT_NE(crazy.numrows(), 4);
  ASSERT_FALSE(crazy.numrows() != 19);

  // test plainJane
  ASSERT_EQ(plainJane.numrows(), 4);
  ASSERT_FALSE(plainJane.numrows() != 4);
  // cout << "Finished numrows tests" << endl;
}

TEST(grid, numCols) {
  // Default constructor grids
  Grid<int> plainA;
  Grid<string> plainB;
  Grid<double> plainC;

  // Parameterized constructor grids
  Grid<set<float> > a(21, 94);
  Grid<map<vector<int>, string> > b(258, 703);
  Grid<short*> c(0, 1);
  Grid<vector<int> > d(23422, 0);
  Grid<char> e(0, 0);

  // cout << "Testing numcols" << endl;

  // test plainA
  // cout << "testing numcols plainA" << endl;
  ASSERT_EQ(plainA.numcols(0), 4);
  ASSERT_EQ(plainA.numcols(1), 4);
  ASSERT_EQ(plainA.numcols(2), 4);
  ASSERT_EQ(plainA.numcols(3), 4);
  ASSERT_ANY_THROW(plainA.numcols(4));
  ASSERT_FALSE(plainA.numcols(0) != 4);

  // test plainB
  // cout << "testing numcols plainB" << endl;
  ASSERT_EQ(plainB.numcols(0), 4);
  ASSERT_EQ(plainB.numcols(1), 4);
  ASSERT_EQ(plainB.numcols(2), 4);
  ASSERT_EQ(plainB.numcols(3), 4);
  ASSERT_ANY_THROW(plainB.numcols(4));
  ASSERT_FALSE(plainB.numcols(0) != 4);

  // test plainC
  // cout << "testing numcols plainC" << endl;
  ASSERT_EQ(plainC.numcols(0), 4);
  ASSERT_EQ(plainC.numcols(1), 4);
  ASSERT_EQ(plainC.numcols(2), 4);
  ASSERT_EQ(plainC.numcols(3), 4);
  ASSERT_ANY_THROW(plainC.numcols(4));
  ASSERT_FALSE(plainC.numcols(0) != 4);

  // test a
  // cout << "testing numcols a" << endl;
  ASSERT_EQ(a.numcols(0), 94);
  ASSERT_EQ(a.numcols(10), 94);
  ASSERT_EQ(a.numcols(20), 94);
  ASSERT_NE(a.numcols(0), 4);
  ASSERT_FALSE(a.numcols(0) > 94 || a.numcols(0) < 94);
  ASSERT_ANY_THROW(a.numcols(21));
  ASSERT_ANY_THROW(a.numcols(-1));

  // test b
  // cout << "testing numcols b" << endl;
  ASSERT_EQ(b.numcols(0), 703);
  ASSERT_EQ(b.numcols(129), 703);
  ASSERT_EQ(b.numcols(257), 703);
  ASSERT_NE(b.numcols(0), 4);
  ASSERT_FALSE(b.numcols(0) > 703 || b.numcols(0) < 703);
  ASSERT_ANY_THROW(b.numcols(258));
  ASSERT_ANY_THROW(b.numcols(-1));

  // test c
  // cout << "testing numcols c" << endl;
  ASSERT_ANY_THROW(c.numcols(0));
  ASSERT_ANY_THROW(c.numcols(1));

  // test d
  // cout << "testing numcols d" << endl;
  ASSERT_EQ(d.numcols(0), 0);
  ASSERT_EQ(d.numcols(12000), 0);
  ASSERT_EQ(d.numcols(23421), 0);
  ASSERT_NE(d.numcols(0), 4);
  ASSERT_ANY_THROW(d.numcols(23422));

  // test e
  // cout << "testing numcols e" << endl;
  ASSERT_ANY_THROW(e.numcols(0));
  ASSERT_ANY_THROW(e.numcols(1));

  // Finished this test
  // cout << "Finished numcols tests" << endl;
}

TEST(grid, sizeOf) {
  // cout << "Testing grid size" << endl;

  // Default constructor grids
  Grid<int> plainA;
  Grid<string> plainB;
  Grid<double> plainC;

  // Parameterized constructor grids
  Grid<set<float> > a(21, 94);
  Grid<map<vector<int>, string> > b(258, 703);
  Grid<short*> c(0, 1);
  Grid<vector<int> > d(23422, 0);
  Grid<char> e(0, 0);

  // test plainA
  // cout << "testing size plainA" << endl;
  ASSERT_EQ(plainA.size(), 16);
  ASSERT_FALSE(plainA.size() > 16);
  ASSERT_FALSE(plainA.size() < 16);
  ASSERT_NE(plainA.size(), 0);

  // test plainB
  // cout << "testing size plainB" << endl;
  ASSERT_EQ(plainB.size(), 16);
  ASSERT_FALSE(plainB.size() > 16);
  ASSERT_FALSE(plainB.size() < 16);
  ASSERT_NE(plainB.size(), 0);

  // testing plainC
  // cout << "testing size plainC" << endl;
  ASSERT_EQ(plainC.size(), 16);
  ASSERT_FALSE(plainC.size() > 16);
  ASSERT_FALSE(plainC.size() < 16);
  ASSERT_NE(plainC.size(), 0);

  // test a
  // cout << "testing size a" << endl;
  ASSERT_EQ(a.size(), 1974);
  ASSERT_FALSE(a.size() > 1974);
  ASSERT_FALSE(a.size() < 1974);
  ASSERT_NE(a.size(), 0);

  // test b
  // cout << "testing size b" << endl;
  ASSERT_EQ(b.size(), 181374);
  ASSERT_FALSE(b.size() > 181374);
  ASSERT_FALSE(b.size() < 181374);
  ASSERT_NE(b.size(), 0);

  // test c
  // cout << "testing size c" << endl;
  ASSERT_EQ(c.size(), 0);
  ASSERT_FALSE(c.size() > 0);
  ASSERT_FALSE(c.size() < 0);
  ASSERT_NE(c.size(), 1);

  // test d
  // cout << "testing size d" << endl;
  ASSERT_EQ(d.size(), 0);
  ASSERT_FALSE(d.size() > 0);
  ASSERT_FALSE(d.size() < 0);
  ASSERT_NE(d.size(), 1);

  // test e
  // cout << "testing size e" << endl;
  ASSERT_EQ(e.size(), 0);
  ASSERT_FALSE(e.size() > 0);
  ASSERT_FALSE(e.size() < 0);
  ASSERT_NE(e.size(), 1);

  // cout << "Finished size tests" << endl;
}

TEST(grid, gridAccessOperator) {
  // Default constructor grids
  Grid<int> plainA;

  // Parameterized constructor grids
  Grid<set<float> > a(21, 94);
  Grid<int> b(258, 703);
  Grid<string> c(0, 1);
  Grid<vector<int> > d(23422, 0);

  // cout << "Testing operator()" << endl;

  // test plainA
  // cout << "testing operator() plainA" << endl;
  ASSERT_EQ(plainA(0, 0), 0);
  ASSERT_EQ(plainA(0, 1), 0);
  ASSERT_EQ(plainA(0, 2), 0);
  ASSERT_EQ(plainA(0, 3), 0);
  ASSERT_EQ(plainA(1, 0), 0);
  ASSERT_EQ(plainA(1, 1), 0);
  ASSERT_EQ(plainA(1, 2), 0);
  ASSERT_EQ(plainA(1, 3), 0);
  ASSERT_EQ(plainA(2, 0), 0);
  ASSERT_EQ(plainA(2, 1), 0);
  ASSERT_EQ(plainA(2, 2), 0);
  ASSERT_EQ(plainA(2, 3), 0);
  ASSERT_EQ(plainA(3, 0), 0);
  ASSERT_EQ(plainA(3, 1), 0);
  ASSERT_EQ(plainA(3, 2), 0);
  ASSERT_EQ(plainA(3, 3), 0);
  ASSERT_ANY_THROW(plainA(4, 0));
  ASSERT_NE(plainA(0, 0), 1);
  ASSERT_FALSE(plainA(0, 0) > 0);
  ASSERT_FALSE(plainA(0, 0) < 0);
  plainA(0, 0) = 2;
  plainA(1, 1) = 4;
  plainA(2, 2) = 8;
  plainA(3, 3) = 16;
  ASSERT_ANY_THROW(plainA(0, -1) = 2);
  ASSERT_ANY_THROW(plainA(0, 4) = 2);
  ASSERT_ANY_THROW(plainA(4, 0) = 2);
  ASSERT_ANY_THROW(plainA(4, -1) = 2);
  ASSERT_ANY_THROW(plainA(4, 4) = 2);

  // test a
  // cout << "testing operator() a" << endl;
  ASSERT_EQ(a(0, 0), set<float>());
  ASSERT_EQ(a(10, 93), set<float>());
  ASSERT_EQ(a(20, 48), set<float>());
  ASSERT_ANY_THROW(a(21, 0));
  ASSERT_ANY_THROW(a(21, -1));

  // test b
  // cout << "testing operator() b" << endl;
  ASSERT_EQ(b(0, 0), 0);
  ASSERT_EQ(b(129, 351), 0);
  ASSERT_EQ(b(257, 702), 0);
  ASSERT_NE(b(257, 702), 1);
  ASSERT_ANY_THROW(b(258, -1));
  ASSERT_ANY_THROW(b(0, -1));

  // test c
  // cout << "testing operator() c" << endl;
  ASSERT_ANY_THROW(c(-1, 0));
  ASSERT_ANY_THROW(c(0, 1));
  ASSERT_ANY_THROW(c(1, 1));
  ASSERT_ANY_THROW(c(2, 1));

  // test d
  // cout << "testing operator() d" << endl;
  ASSERT_ANY_THROW(d(0, 1));
  ASSERT_ANY_THROW(d(23422, 0));

  // cout << "Finished operator() tests" << endl;
}

// TEST(grid, _output) {
//     Grid<int> a;
//     a(0,0) = 2;
//     a(1,1) = 4;
//     a(2,2) = 8;
//     a(3,3) = 16;
//     ASSERT_ANY_THROW(a(0,-1) = 2);
//     ASSERT_ANY_THROW(a(0, 4) = 2);
//     ASSERT_ANY_THROW(a(4, 0) = 2);
//     ASSERT_ANY_THROW(a(4,-1) = 2);
//     ASSERT_ANY_THROW(a(4, 4) = 2);
//     a._output();
// }

TEST(grid, copyConstructor) {
  // Set up a default grid and modify its diagonal
  Grid<int> a;
  a(0, 0) = 2;
  a(1, 1) = 4;
  a(2, 2) = 8;
  a(3, 3) = 16;
  // a._output();

  // Copy that grid via the copy constructor
  Grid<int> b(a);
  // b._output();

  // Ensure that b and a are identical
  ASSERT_EQ(a(0, 0), b(0, 0));
  ASSERT_EQ(a(1, 1), b(1, 1));
  ASSERT_EQ(a(2, 2), b(2, 2));
  ASSERT_EQ(a(3, 3), b(3, 3));
  ASSERT_EQ(a.numrows(), 4);
  ASSERT_EQ(a.numcols(0), 4);
  ASSERT_EQ(a.numcols(1), 4);
  ASSERT_EQ(a.numcols(2), 4);
  ASSERT_EQ(a.numcols(3), 4);
  ASSERT_EQ(a.size(), 16);

  // Grids with precarious dimensions
  Grid<int> onebyzero(1, 0);
  Grid<int> zerobyone(0, 1);
  Grid<int> zerobyzero(0, 0);

  // Copy into the odd dimensioned grids
  Grid<int> x(onebyzero);
  ASSERT_ANY_THROW(x(0, 0));
  ASSERT_ANY_THROW(x(-1, 0));
  ASSERT_ANY_THROW(x(0, -1));
  ASSERT_ANY_THROW(x(-1, -1));

  // Next wonk grid
  Grid<int> y(zerobyone);
  ASSERT_ANY_THROW(y(0, 0));
  ASSERT_ANY_THROW(y(-1, 0));
  ASSERT_ANY_THROW(y(0, -1));
  ASSERT_ANY_THROW(y(-1, -1));

  // Dimensionless
  Grid<int> z(zerobyzero);
  ASSERT_ANY_THROW(z(0, 0));
  ASSERT_ANY_THROW(z(-1, 0));
  ASSERT_ANY_THROW(z(0, -1));
  ASSERT_ANY_THROW(z(1, -1));

  // Another grid of fine, italian delicacies
  Grid<string> c(31, 59);
  c(15, 28) = "Gabagool";

  // Basic stuff
  ASSERT_EQ(c.numrows(), 31);
  ASSERT_EQ(c.numcols(0), 59);
  ASSERT_EQ(c.numcols(4), 59);
  ASSERT_EQ(c.numcols(12), 59);
  ASSERT_EQ(c.numcols(30), 59);
  ASSERT_EQ(c.size(), 31 * 59);

  // Copy the string grid
  Grid<string> d(c);

  // String grid equivalence
  ASSERT_EQ(d(15, 28), c(15, 28));
  ASSERT_EQ(d(0, 0), c(0, 0));
  ASSERT_ANY_THROW(c(31, 0));
  ASSERT_ANY_THROW(d(31, 0));

  // Test bad indices for original string grid
  ASSERT_ANY_THROW(c(30, 59));
  ASSERT_ANY_THROW(c(30, -1));
  ASSERT_ANY_THROW(c(30, 425));
  ASSERT_ANY_THROW(c(-1, 0));
  ASSERT_ANY_THROW(c(-1, -1));

  // bad indices for other string grid
  ASSERT_ANY_THROW(d(30, 59));
  ASSERT_ANY_THROW(d(30, -1));
  ASSERT_ANY_THROW(d(30, 425));
  ASSERT_ANY_THROW(d(-1, 0));
  ASSERT_ANY_THROW(d(-1, -1));

  // Chain copy
  Grid<string> chain(d);

  // Make sure the data is still intact
  ASSERT_EQ(d(15, 28), chain(15, 28));
  ASSERT_EQ(d(0, 0), chain(0, 0));

  // Try bad indices for the chain copy
  ASSERT_ANY_THROW(chain(30, 59));
  ASSERT_ANY_THROW(chain(30, -1));
  ASSERT_ANY_THROW(chain(30, 425));
  ASSERT_ANY_THROW(chain(-1, 0));
  ASSERT_ANY_THROW(chain(-1, -1));
}

TEST(grid, copyAssignmentOperator) {
  // default grid
  Grid<int> a;

  // Alter its diagonal
  a(0, 0) = 2;
  a(1, 1) = 4;
  a(2, 2) = 8;
  a(3, 3) = 16;

  // Try some bad accesses of the original
  ASSERT_ANY_THROW(a(0, -1) = 2);
  ASSERT_ANY_THROW(a(0, 4) = 2);
  ASSERT_ANY_THROW(a(4, 0) = 2);
  ASSERT_ANY_THROW(a(4, -1) = 2);
  ASSERT_ANY_THROW(a(4, 4) = 2);

  // New default grid
  Grid<int> b;

  // Copy a over to b
  b = a;

  // Verify the diagonal
  ASSERT_EQ(b(0, 0), 2);
  ASSERT_EQ(b(1, 1), 4);
  ASSERT_EQ(b(2, 2), 8);
  ASSERT_EQ(b(3, 3), 16);

  // Bad accesses on the copy
  ASSERT_ANY_THROW(b(-1, -1));
  ASSERT_ANY_THROW(b(0, 124));
  ASSERT_ANY_THROW(b(0, -1));
  ASSERT_ANY_THROW(b(-1, 3));

  // Assign the copy to itself to make sure it doesn't break
  b = b;

  // Verify the diagonal
  ASSERT_EQ(b(0, 0), 2);
  ASSERT_EQ(b(1, 1), 4);
  ASSERT_EQ(b(2, 2), 8);
  ASSERT_EQ(b(3, 3), 16);

  // Bad accesses on the copy
  ASSERT_ANY_THROW(b(-1, -1));
  ASSERT_ANY_THROW(b(0, 124));
  ASSERT_ANY_THROW(b(0, -1));
  ASSERT_ANY_THROW(b(-1, 3));

  Grid<int> c;
  c = b;

  // Verify that c matches b, which matches a
  ASSERT_EQ(c(0, 0), 2);
  ASSERT_EQ(c(1, 1), 4);
  ASSERT_EQ(c(2, 2), 8);
  ASSERT_EQ(c(3, 3), 16);

  // bad accesses on c
  ASSERT_ANY_THROW(c(-1, -1));
  ASSERT_ANY_THROW(c(0, 124));
  ASSERT_ANY_THROW(c(0, -1));
  ASSERT_ANY_THROW(c(-1, 3));

  // Grids with precarious dimensions
  Grid<int> onebyzero(1, 0);
  Grid<int> zerobyone(0, 1);
  Grid<int> zerobyzero(0, 0);

  // Copy into the odd dimensioned grids
  b = onebyzero;
  ASSERT_ANY_THROW(b(0, 0));
  ASSERT_ANY_THROW(b(-1, 0));
  ASSERT_ANY_THROW(b(0, -1));
  ASSERT_ANY_THROW(b(-1, -1));

  // Next wonk grid
  b = zerobyone;
  ASSERT_ANY_THROW(b(0, 0));
  ASSERT_ANY_THROW(b(-1, 0));
  ASSERT_ANY_THROW(b(0, -1));
  ASSERT_ANY_THROW(b(-1, -1));

  // Dimensionless
  b = zerobyzero;
  ASSERT_ANY_THROW(b(0, 0));
  ASSERT_ANY_THROW(b(-1, 0));
  ASSERT_ANY_THROW(b(0, -1));
  ASSERT_ANY_THROW(b(1, -1));
}

// Provided Test: sample maze from handout, make lots more yourself!
TEST(maze, basic) {
   vector<string> textMaze;

   textMaze.push_back("* *-W *");
   textMaze.push_back("| |   |");
   textMaze.push_back("*-* * *");
   textMaze.push_back("  | | |");
   textMaze.push_back("S *-*-*");
   textMaze.push_back("|   | |");
   textMaze.push_back("*-*-* P");

   Maze m(textMaze);

   MazeCell* start = m.getStart(2, 2);

   /* These paths are the ones in the handout. They all work. */
   EXPECT_TRUE(isPathToFreedom(start, "ESNWWNNEWSSESWWN"));
   EXPECT_TRUE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES"));
   EXPECT_TRUE(isPathToFreedom(start, "WNNEWSSESWWNSEENES"));

   /* These paths don't work, since they don't pick up all items. */
   EXPECT_FALSE(isPathToFreedom(start, "ESNW"));
   EXPECT_FALSE(isPathToFreedom(start, "SWWN"));
   EXPECT_FALSE(isPathToFreedom(start, "WNNE"));

   /* These paths don't work, since they aren't legal paths. */
   EXPECT_FALSE(isPathToFreedom(start, "WW"));
   EXPECT_FALSE(isPathToFreedom(start, "NN"));
   EXPECT_FALSE(isPathToFreedom(start, "EE"));
   EXPECT_FALSE(isPathToFreedom(start, "SS"));
}

// Provided Test: don't allow going through walls
TEST(maze, tryingToGoThroughWalls) {
   vector<string> textMaze;

   textMaze.push_back("* S *");
   textMaze.push_back("     ");
   textMaze.push_back("W * P");
   textMaze.push_back( "     ");
   textMaze.push_back( "* * *");

   Maze m(textMaze);

   MazeCell* start = m.getStart(1, 1);

   EXPECT_FALSE(isPathToFreedom(start, "WNEES"));
   EXPECT_FALSE(isPathToFreedom(start, "NWSEE"));
   EXPECT_FALSE(isPathToFreedom(start, "ENWWS"));
   EXPECT_FALSE(isPathToFreedom(start, "SWNNEES"));
}

// Provided Test: Works when starting on an item
TEST(maze, startOnItem) {
   vector<string> textMaze;

   textMaze.push_back("P-S-W");

   Maze m(textMaze);
   MazeCell* start = m.getStart(0, 0);

   EXPECT_TRUE(isPathToFreedom(start, "EE"));
   start = m.getStart(0, 1);
   EXPECT_TRUE(isPathToFreedom(start, "WEE"));
   start = m.getStart(0, 2);
   EXPECT_TRUE(isPathToFreedom(start, "WW"));

}

// Provided Test: Reports errors if given illegal characters.
TEST(maze, invalidChar) {
   vector<string> textMaze;

   textMaze.push_back("* *-W *");
   textMaze.push_back("| |   |");
   textMaze.push_back("*-* * *");
   textMaze.push_back("  | | |");
   textMaze.push_back("S *-*-*");
   textMaze.push_back("|   | |");
   textMaze.push_back("*-*-* P");

   Maze m(textMaze);
   MazeCell* start = m.getStart(0, 0);

   /* These paths contain characters that aren't even close to permissible.
   */ EXPECT_FALSE(isPathToFreedom(start, "Q"));
   EXPECT_FALSE(isPathToFreedom(start, "X"));
   EXPECT_FALSE(isPathToFreedom(start, "!"));
   EXPECT_FALSE(isPathToFreedom(start, "?"));

   EXPECT_FALSE(isPathToFreedom(start, "n"));
   EXPECT_FALSE(isPathToFreedom(start, "s"));
   EXPECT_FALSE(isPathToFreedom(start, "e"));
   EXPECT_FALSE(isPathToFreedom(start, "w"));

   // These are tricky - they're legal paths that happen to have an unexpected
   // character at the end.
   start = m.getStart(2, 2);
   EXPECT_FALSE(isPathToFreedom(start, "ESNWWNNEWSSESWWNQ"));
   EXPECT_FALSE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES!!!"));
   EXPECT_FALSE(isPathToFreedom(start, "WNNEWSSESWWNSEENES??"));

}

// Provided Test: This tests your personalized regular maze to see if you were
// able to escape.
TEST(maze, escapeRegularMaze) {
   Maze m(4, 4);
   MazeCell* start = m.mazeFor(kYourName);
   EXPECT_TRUE(isPathToFreedom(start, kPathOutOfRegularMaze));
}

// Provided Test: This tests your personalized twisty maze to see if you were
// able to escape.
TEST(maze, escapeTwistyMaze) {
   Maze m(4, 4);
   MazeCell* start = m.twistyMazeFor(kYourName);
   EXPECT_TRUE(isPathToFreedom(start, kPathOutOfTwistyMaze));
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  int result = RUN_ALL_TESTS();
  return result;
}