#include "stack.h"
#include <fstream>
#include <string>
//-----------------------------------------------------------
// Constructor function.
//-----------------------------------------------------------
Stack::Stack()
{
   Head = NULL;
   Length = 0;
}

//----------------------------------------------
// Constructor function.
//----------------------------------------------
Stack::Stack(const Stack & stack)
{
   // Create first node
   StackNode *copy = new StackNode();
   Head = copy;

   // Walk list to copy nodes
   StackNode *ptr = stack.Head;
   while (ptr != NULL)
   {
      copy->Next = new StackNode();
      copy = copy->Next;
      copy->Number = ptr->Number;
      copy->Next = NULL;
      ptr = ptr->Next;
   }

   // Tidy first node
   copy = Head;
   Head = copy->Next;
   delete copy;
}

//-----------------------------------------------------------
// Destructor function.
//-----------------------------------------------------------
Stack::~Stack()
{
   // Walk stack deleting data
   while (Head != NULL)
   {
      StackNode *Temp = Head;
      Head = Head->Next;
      delete Temp;
   }

   // Reset head
   Head = NULL;
   Length = 0;
}

//-----------------------------------------------------------
// Check to see if stack is full.
//-----------------------------------------------------------
bool Stack::IsFull()
{
   return (false);
}

//-----------------------------------------------------------
// Check to see if stack is empty.
//-----------------------------------------------------------
bool Stack::IsEmpty()
{
   return (Length == 0);
}

//-----------------------------------------------------------
// Push data into the stack.
//-----------------------------------------------------------
void Stack::Push(DataType Number)
{
   // Check for full stack
   if (IsFull())
      return;

   // Allocate space for data
   StackNode *Temp = new StackNode;
   if (Temp == NULL)
      return;

   // Insert data at head of list
   Temp->Number = Number;
   Temp->Next = Head;
   Head = Temp;
   Length++;
}

//-----------------------------------------------------------
// Pop data from the stack.
//-----------------------------------------------------------
void Stack::Pop(DataType &Number)
{
   // Check for empty stack
   if (IsEmpty())
      return;

   // Extract information from node
   Number = Head->Number;

   // Pop item from linked list
   StackNode *Temp = Head;
   Head = Head->Next;
   delete Temp;
   Length--;
}

//-----------------------------------------------------------
// Return data from top of stack.
//-----------------------------------------------------------
void Stack::Top(DataType &Number)
{
   // Check for empty stack
   if (IsEmpty())
      return;

   // Return information from node
   Number = Head->Number;
}

//-----------------------------------------------------------
// Return the number of elements in stack.
//-----------------------------------------------------------
int Stack::GetLength()
{
   return Length;
}

//-----------------------------------------------------------
// Print all records in the stack.
//-----------------------------------------------------------
void Stack::Print()
{
   // Walk the stack printing data
   cout << "stack: ";
   StackNode *Temp = Head;
   while (Temp != NULL)
   {
      cout << Temp->Number << " ";
      Temp = Temp->Next;
   }
   cout << endl;
}

#ifdef STACK_MAIN
//-----------------------------------------------------------
// Main program.
//-----------------------------------------------------------
int main()
{
   Stack s;
   const int SIZE = 16;
   //array of tags that do not have end tags
   string voidElements[SIZE] = {"area", "base", "br", "col", "command", "embed",
                               "hr", "img", "input", "keygen", "link", "meta",
                               "param", "source", "track", "wbr"};
   string fileName;
   cout << "Please enter the name of the html file" << endl;
   cin >> fileName;
   ifstream din;
   //opening the file
   din.open(fileName.c_str());
   if (!din)
      return 0;
   char character;
   string htmlTag;
   string topTag;
   //flag to tell if it is an end tag or not
   bool endTag = false;
   //flag to tell if the tag does not have an end tag
   bool voidElementTag = false;
   //flag to tell if the tag is a comment
   bool comment = false;
   //integer to get the position of the find method of the string class
   int find = 0;
   //integer to get the position of the find method of the string class
   int numElementTag = 0;
   //while loop that loops until the end of the file
   while(!din.eof())
   {
      //resetting endTag to false
      endTag = false;
      //reintializing the comment flag
      comment = false;
      //read in a character
      din >> character;
      //if statement to read in the rest of a tag
      if(character == '<')
      {
         //reintialized the htmlTag string
         htmlTag = "";
         //concatenate the characters
         htmlTag += character;
         //loop until the end of the tag
         while(character != '>')
         {
            din >> character;
            htmlTag += character;
         }
         //cout << htmlTag[1] << endl;
         //if statment to determine if it is a comment
         if(htmlTag[1] == '!')
            comment = true;
         //if statement to determine if it is an endTag
         else if(htmlTag[1] == '/')
         {
            //setting flag to true
            endTag = true;
            //erasing the '<' '/' '>' characters from the end tag
            find = htmlTag.find('<');
            htmlTag.erase(find, 1);
            find = htmlTag.find('/');
            htmlTag.erase(find, 1);
            find = htmlTag.find('>');
            htmlTag.erase(find, 1);
            //cout << htmlTag << endl;
            //reading from the top of the stack
            s.Top(topTag);
            //reintializing the find variable
            find = 0;
            //finding the end tag in the tag on top of the stack
            find = topTag.find(htmlTag);
            //cout << find << endl;
            //if it finds the correct tag it pops it off
            if(find == 1)
            {
               s.Pop(topTag);
            }
            //telling the user that there is an error
            else
            {
               cout << "WARNING! NESTING ERROR!" << endl;
               cout << "The tag " << topTag << " does not have an end tag" << endl;
            }
         }
         //reintializing the element tag flag
         voidElementTag = false;
         //loop to go through all of the self ending tags
         for(int i = 0; i < SIZE; i++)
         {
            numElementTag = htmlTag.find(voidElements[i]);
            if(numElementTag == 1)
               voidElementTag = true;

         }
         //push the tag on the stack if it is not an end tag and not a self ending tag
         if(!endTag && !voidElementTag && !comment)
            s.Push(htmlTag);
         //s.Print();
      }
   }
   //if the stack is not empty after the loop then there is an error
   if(!s.IsEmpty())
   {
      cout << "WARNING! NESTING ERROR!" << endl;
      cout << "There is a missing end tag" << endl;
   }
   //Printing the stack at the ends
   s.Print();
   din.close();
}
#endif
