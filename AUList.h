#define MAXSIZE 1000
#include <string>

struct Sales_Data {
int Platform_count;
std::string Platform;
std::string Name;  
double NA_Sales;
double EU_Sales;
};

class AUList
{
public:
  
  AUList(); // Constructor
  
  void MakeEmpty();  // Returns the list to the empty state.
    
  bool IsFull() const; //Determines whether list is full. (Precondition -- list has been initialized).  Return value of "True" indicates class is full.
  
  int GetLength() const; //Determines the number of elements in list.

  Sales_Data GetItem(int); //Retrieves position of list element matching input item (if present).  If not present, null is returned.

  void PutItem(Sales_Data); //Adds the item to the list.
  
  void DeleteItem(int); //Deletes the element whose key matches item's key.
  
  void ResetList();  //Initializes iterator's current position for an iteration through the list.

  Sales_Data GetNextItem(); //Gets the next element in the list.

  bool HasNextItem();
  
  void PrintList();  //Print all elements of the list in a readable format.
  
    

private:
  int length;
  Sales_Data ListItems[MAXSIZE];
  int currentPos;
};

