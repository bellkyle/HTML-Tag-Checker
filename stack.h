
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

typedef string DataType;
//-----------------------------------------------------------
// Stack data node definition
//-----------------------------------------------------------
struct StackNode
{
   DataType Number;
   StackNode *Next;
};

//-----------------------------------------------------------
// Define the Stack class interface
//-----------------------------------------------------------
class Stack
{
 public:
   // Constructors
   Stack();
   Stack(const Stack & stack);
   ~Stack();

   // Methods
   bool IsFull();
   bool IsEmpty();
   void Push(DataType Number);
   void Pop(DataType &Number);
   void Top(DataType &Number);
   int GetLength();
   void Print();

 private:
   StackNode *Head;
   int Length;
};
