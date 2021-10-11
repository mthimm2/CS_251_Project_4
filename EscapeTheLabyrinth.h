#include <random>
#include <set>
#include <utility>

#include "grid.h"
#include "maze.h"
using namespace std;

/* Change this constant to contain your full first and last name (middle is ok
 * too).
 *
 * WARNING: Once you've set set this constant and started exploring your maze,
 * do NOT edit the value of kYourName. Changing kYourName will change which
 * maze you get back, which might invalidate all your hard work!
 */
const string kYourName = "Max Thimmig";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze =
    "TO DO: Replace this string with your path out of the normal maze.";
const string kPathOutOfTwistyMaze =
    "TO DO: Replace this string with your path out of the twisty maze.";

bool checkMove(MazeCell* currCell, const char& move) {

  // When a direction is an invalid move
  bool badNorth = currCell->north == nullptr;
  bool badSouth = currCell->south == nullptr;
  bool badEast = currCell->east == nullptr;
  bool badWest = currCell->west == nullptr;

  // Only valid moves in this set
  set<char> validDirections {'N', 'E', 'S', 'W'};

  // No invalid moves allowed
  if(!validDirections.count(move)) {
    return false;
  }

  if(move == 'N') {
    if(badNorth) {
      return false;
    }
  } else if(move == 'S') {
    if(badSouth) {
      return false;
    }
  } else if(move == 'E') {
    if(badEast) {
      return false;
    }
  } else if(move == 'W') {
    if(badWest) {
      return false;
    }
  }
  // If we made it past all of the above statements, our move is legal and can be made!
  return true;
}

void makeMove(const char& move, MazeCell*& currCell) {
  
  // If we're here, then the move has been vetted to be legal
  // Therefore, just move in the given direction
  if(move == 'N') {
    currCell = currCell->north;
  } else if(move == 'S') {
      currCell = currCell->south;
  } else if(move == 'E') {
      currCell = currCell->east;
  } else if(move == 'W') {
      currCell = currCell->west;
  } 
}

void checkCurrentTileForLoot(MazeCell* currCell, set<string>& itemsAcquired) {
  // Basic check for present loot
  if(currCell->whatsHere == "Spellbook") {
    itemsAcquired.insert("Spellbook");
  } else if(currCell->whatsHere == "Potion") {
    itemsAcquired.insert("Potion");
  } else if(currCell->whatsHere == "Wand") {
    itemsAcquired.insert("Wand");
  }
}

bool isPathToFreedom(MazeCell* start, const string& moves) {
  /* TO DO: Delete this comment and the next few lines, then implement
   * this function.
   */

  // All of the items we've found so far
  set<string> itemsAcquired;

  // Constants for bad moves
  bool badNorth = start->north == nullptr;
  bool badSouth = start->south == nullptr;
  bool badEast = start->east == nullptr;
  bool badWest = start->west == nullptr;

  // Check if we're in a maze that's pure garbage
  bool badMaze = (badNorth && badSouth && badEast && badWest);
  if(badMaze) {
    return false;
  }

  // Check to see if we're standing on the item to start
  checkCurrentTileForLoot(start, itemsAcquired);


  // Now, try to make our way through the maze and spot illegal moves along the way.
  for(const char& move : moves) {
    // If we try to make a move and it's a bad one, then the escape path isn't valid.
    if(!checkMove(start, move)){
      return false;
    } else {
      // Otherwise, make the legal move
      makeMove(move, start);
      // Then check if we've hit the motherlode
      checkCurrentTileForLoot(start, itemsAcquired);
    }
  }
  // After we make all legal moves
  // Check if we have all of the items we need
  bool potion = itemsAcquired.count("Potion");
  bool wand = itemsAcquired.count("Wand");
  bool spellbook = itemsAcquired.count("Spellbook");

  // If we have all three items, we've escaped
  if(potion && wand && spellbook) {
    return true;
  } else {
    // Otherwise, we're doomed to wander the halls of the maze for eternity.
    return false;
  }
}
