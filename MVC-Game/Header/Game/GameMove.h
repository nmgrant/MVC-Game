#ifndef __BOARDGAMEMOVE_H
#define __BOARDGAMEMOVE_H
#include <string>

/*
Every game represents "moves" in a different way, so we don't define any member
variables for a GameMove. Instead we declare several pure virtual functions
that all Move-derived types need to implement in order to support input, output,
and comparisons.
*/
class GameMove {
public:
   // Virtual destructors are important for class hierarchies. Add a virtual 
   // destructor to all your classes; the destructor can be empty like this.
   virtual ~GameMove() {}
   /*
   Assigns a string-formatted value to this GameMove. The string value should
   be formatted in the same way that operator std::string returns.
   */
   virtual GameMove &operator=(const std::string &) = 0;

   /*
   Converts the GameMove to a string for output.
   */
   virtual operator std::string() const = 0;

   /*
   Compares one GameMove to another, assuming they are of the same derived type.
   */
   virtual bool Equals(const GameMove &other) const = 0;

   /*
   Helper method for doing == comparison on derived GameMove types. This method
   will be called any time you use == to compare two GameMove objects; the 
   operator will in turn call the virtual Equals method to support base-class
   comparisons.
   */
   friend bool operator==(const GameMove &lhs, const GameMove &rhs) {
      return lhs.Equals(rhs);
   }
};

#endif