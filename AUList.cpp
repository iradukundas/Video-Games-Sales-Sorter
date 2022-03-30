// Implementation file for AUList
#include <iostream>
#include <stdexcept>
#include "AUList.h"

//Many AUList Operations are unaffected!
AUList::AUList() {
  length = 0; 
}
bool AUList::IsFull() const {
  return (length == MAXSIZE); 
}
int AUList::GetLength() const {
  return length;
}

Sales_Data AUList::GetItem(int gitem) { //Get first CCRecord in list with matching time
  int searchiter;
  for (searchiter = 0; searchiter<length; searchiter++) {  
	if (ListItems[searchiter].Platform_count == gitem) 
  	  break;  
  } 
  if (searchiter==length)
  	throw std::runtime_error("No item with corresponding time in list.");
  else
    return ListItems[searchiter];
}
void AUList::MakeEmpty() {
  length = 0; //as with the constructor, we need do nothing to the actual array, as it now "junk" data
}
void AUList::PutItem(Sales_Data item) { //This function assumes the "IsFull" condition hasn't been met.
  ListItems[length] = item; //Remember that C++ uses 0-indexing.
  length++;
}
void AUList::DeleteItem(int item) { //Delete first item in list with matching "time" 
  bool indexfound=false;
  for (int loc=0; loc<length; loc++) {
  	if (ListItems[loc].Platform_count==item) 
  	  indexfound=true;
  	if (indexfound)
  	  ListItems[loc]=ListItems[loc+1];	
  }
  length--;
}

void AUList::ResetList() {
  currentPos = -1; //We want the position BEFORE the first element, since incrementation in GetNextItems happens first
}

bool AUList::HasNextItem() {
  return currentPos<(length-1);
}

Sales_Data AUList::GetNextItem() {
  currentPos++; //Remember that currentPos is a class member variable
  return ListItems[currentPos];
}

void AUList::PrintList() { //simple function to print a list's items in stored order
  for (int loc=0; loc<length; loc++) 
  {
  	Sales_Data curitem=ListItems[loc];
	std::cout<<curitem.Platform_count<<", "<<curitem.Platform <<", "<< curitem.Name << ", " << curitem.NA_Sales << ", "<< curitem.EU_Sales <<std::endl;
  }
}
