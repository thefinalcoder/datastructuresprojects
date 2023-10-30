#include <iostream>

using namespace std;

// Data Class : Holds all the data that goes inside the Node
class Data {
public:
  int value;
  string name;
  Data(int value, string name) {
    this->value = value;
    this->name = name;
  }
  void print() {
    cout << value << " " << endl;
    cout << name << " " << endl;
  }

  int getValue() const {
    return value;
  }
};

// Node Class : Node for the LinkedList
template <typename T> class Node {
public:
  T *value;
  Node<T> *next;
  Node<T> *prev;
  Node(T *value) {
    this->value = value;
    next = nullptr;
    prev = nullptr;
  }
  void print() { value->print(); }

};

// LinkedList Class : Container for Nodes
template <typename T> class DoubleLinkedList {
private:
  Node<T> *head;
  Node<T> *tail;
  int length;

public:
  // Constructor
  DoubleLinkedList(T *value) {
    Node<T> *newNode = new Node<T>(value);
    head = newNode;
    tail = newNode;
    length = 1;
  }

  // Destructor
  ~DoubleLinkedList() {
    Node<T> *temp = head;
    while (head) {
      head = head->next;
      delete temp;
      temp = head;
    }
  }

  void printList() {
    Node<T> *temp = head;
    while (temp != nullptr) {
      temp->print();
      temp = temp->next;
    }
  }

  // get and set
  Node<T> *getHead() {
    if (head == nullptr) {
      cout << "Head: nullptr" << endl;
    } else {
      cout << "Head: " << head->value << endl;
    }
    return head;
  }

  Node<T> *getTail() {
    if (tail == nullptr) {
      cout << "Tail: nullptr" << endl;
    } else {
      cout << "Tail: " << tail->value << endl;
    }
    return tail;
  }

  int getLength() {
    cout << "Length: " << length << endl;
    return length;
  }

  Node<T> *get(int index) {
    if (index < 0 || index >= length)
      return nullptr;
    Node<T> *temp = head;
    for (int i = 0; i < index; ++i) {
      temp = temp->next;
    }
    return temp;
  }

  bool set(int index, T *value) {
    Node<T> *temp = get(index);
    if (temp) {
      temp->value = value;
      return true;
    }
    return false;
  }

  // All insert methods
  // Insert at end
  void append(T *value) {
    Node<T> *newNode = new Node<T>(value);
    if (length == 0) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
    length++;
  }

  // Insert at beginning

  void prepend(T *value) {
    Node<T> *newNode = new Node<T>(value);
    if (length == 0) {
      head = newNode;
      tail = newNode;
    } else {
      newNode->next = head;
      head->prev = newNode;
      head = newNode;
    }
    length++;
  }

  // Insert at Index

  bool insert(int index, T *value) {
    if (index < 0 || index > length)
      return false;
    if (index == 0) {
      prepend(value);
      return true;
    }
    if (index == length) {
      append(value);
      return true;
    }
    Node<T> *newNode = new Node<T>(value);
    Node<T> *prev1 = get(index - 1);
    Node<T> *next1 = prev1->next;
    newNode->prev = prev1;
    newNode->next = next1;
    prev1->next = newNode;
    next1->prev = newNode;
    length++;
    return true;
  }

  //prints and deletes head of DLL
  void deleteAtHead(){
    if(head == nullptr)
    {
      cout << "List Empty" << endl;
      return;
    }

    cout << "Deleted Node: ";
    head->print();

    Node<T> *temporary = head;
    head = head->next;

    if(head != nullptr)
    {
      head->prev = nullptr;
    }
    else
    {
      tail = nullptr;
    }

    delete temporary;
  }

  //prints and deletes tail of DLL
  void deleteAtTail(){
    if(tail == nullptr)
    {
      cout << "List Empty" << endl;
      return;
    }

    cout << "Deleted Node: ";
    tail->print();

    Node<T> *temporary = tail;
    tail = tail->prev;

    if(tail != nullptr)
    {
      tail->next = nullptr;
    }
    else
    {
      head = nullptr;
    }

    delete temporary;
  }

  //prints and deltes node at index
  void deleteAtIndex(int index)
  {
    if(head == nullptr || index < 0 || index >= length)
    {
      cout << "List is Empty or Index out of Bounds" << endl;
      return;
    }

    Node<T> *currentNode = head;
    int currentNodeIndex = 0;

    while(currentNode != nullptr && currentNodeIndex < index)
      {
        currentNode = currentNode->next;
        currentNodeIndex++;
      }

    if(currentNode == nullptr)
    {
      cout << "Index out of Bounds" << endl;
    }

    cout << "Node Deleted: " ;
    currentNode->print();


    if(currentNode->prev != nullptr)
    {
      currentNode->prev->next = currentNode->next;
    }
    else
    {
      head = currentNode->next;
    }

    if(currentNode->next != nullptr)
    {
      currentNode->next->prev = currentNode->prev;
    }
    else
    {
      tail = currentNode->prev;
    }

    delete currentNode;
  }

  void sortList()
{
    if (head == nullptr)
    {
        cout << "List Empty" << endl;
        return;
    }

    bool swap;
    Node<T> *lastNode = nullptr;
    Node<T> *currentNode;

    do
    {
        swap = false;
        currentNode = head;

        while (currentNode->next != lastNode)
        {
            if (currentNode->value->getValue() > currentNode->next->value->getValue())
            {
                T *temp = currentNode->value;
                currentNode->value = currentNode->next->value;
                currentNode->next->value = temp;
                swap = true;
            }

            currentNode = currentNode->next;
        }
        lastNode = currentNode;
    } while (swap);
    printList();
}

  void removeMultiples(int val) {
        Node<T> *currentNode = head;
        while (currentNode) 
        {
            if (currentNode->value->getValue() == val) 
            {
                Node<T> *nodeToRemove = currentNode;
                if (currentNode->prev) 
                {
                    currentNode->prev->next = currentNode->next;
                } 
                else 
                {
                    head = currentNode->next;
                }
                if (currentNode->next) 
                {
                    currentNode->next->prev = currentNode->prev;
                } 
                else 
                {
                    tail = currentNode->prev;
                }
                currentNode = currentNode->next;
                delete nodeToRemove;
            } 
            else 
            {
                currentNode = currentNode->next;
            }
        }
      printList();
    }


  int countMultiples(int valueToCount) {
    int count = 0;
    Node<Data>* currentNode = head;

    while (currentNode != nullptr) {
        if (currentNode->value->getValue() == valueToCount) {
            count++;
        }
        currentNode = currentNode->next;
    }

    return count;
}

  void headTailSplit() {
    if (!head || !head->next) {
        cout << "List is too short" << endl;
        return;
    }

    Node<T> *middle = findMiddle();
    Node<T> *listA = head;
    Node<T> *listB = middle->next;
    middle->next = nullptr; 

    tail = middle;

    // Print List A
    cout << "List A: ";
    Node<T> *currentNodeA = listA;
    while (currentNodeA) {
        cout << currentNodeA->value->getValue() << " ";
        Node<T> *temp = currentNodeA;
        currentNodeA = currentNodeA->next;
        delete temp; 
    }
    cout << endl;

    // Print List B
    cout << "List B: ";
    Node<T> *currentNodeB = listB;
    while (currentNodeB) {
        cout << currentNodeB->value->getValue() << " ";
        Node<T> *temp = currentNodeB;
        currentNodeB = currentNodeB->next;
        delete temp; 
    }
    cout << endl;

    head = nullptr;
    tail = nullptr;
}
  void reverseList() {
        if (!head || !head->next) {
            cout<< "Nothing to reverse" << endl;
            return;
        }

        Node<T> *currentNode = head;
        Node<T> *temp = nullptr;

        
        while (currentNode) {
            temp = currentNode->prev;
            currentNode->prev = currentNode->next;
            currentNode->next = temp;
            currentNode = currentNode->prev; 
        }

        
        temp = head;
        head = tail;
        tail = temp;

        
        cout << "Reversed List: " << endl;
        printList();
    }

  Node<T> *findMiddle() {
        Node<T> *slow = head;
        Node<T> *fast = head;
        while (fast && fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};

int main() {
  Data item1(1, "Item1");
  Data item2(2, "Item2");
  Data item3(3, "Item3");
  Data item4(4, "Item4");

  DoubleLinkedList<Data> myList(&item1);
  myList.append(&item2);
  myList.append(&item3);
  myList.append(&item4);

  int userInput;
  while (true) {
    cout << "Menu:" << endl;
    cout << "1. Delete a List" << endl;
    cout << "2. Insert at Head" << endl;
    cout << "3. Insert at Tail" << endl;
    cout << "4. Insert at Index" << endl;
    cout << "5. Delete at Head" << endl;
    cout << "6. Delete at Tail" << endl;
    cout << "7. Delete at Index" << endl;
    cout << "8. Reverse List" << endl;
    cout << "9. Sort List" << endl;
    cout << "10. Count Multiples" << endl;
    cout << "11. Delete Multiples" << endl;
    cout << "12. Split List Even Odd" << endl;
    cout << "13. Exit" << endl;
    cout << "Enter a number between 1-13: ";
    cin >> userInput;

    switch (userInput) {
      case 1: {
        myList.~DoubleLinkedList();
        cout << "DLL deleted." << endl;
        return 0;
      }
      case 2: {
        int value;
        string name;
        cout << "Enter value: ";
        cin >> value;
        cout << "Enter name: ";
        cin >> name;
        Data *data = new Data(value, name);
        myList.prepend(data);
        cout << "Inserted at head." << endl;
        break;
      }
      case 3: {
        int value;
        string name;
        cout << "Enter value: ";
        cin >> value;
        cout << "Enter name: ";
        cin >> name;
        Data *data = new Data(value, name);
        myList.append(data);
        cout << "Inserted at tail." << endl;
        break;
      }
      case 4: {
        int index, value;
        string name;
        cout << "Enter an index: ";
        cin >> index;
        cout << "Enter value: ";
        cin >> value;
        cout << "Enter name: ";
        cin >> name;
        Data *data = new Data(value, name);
        bool success = myList.insert(index, data);
        if (success) {
          cout << "Inserted at index " << index << "." << endl;
        } else {
          cout << "Invalid index." << endl;
        }
        break;
      }
      case 5: {
        myList.deleteAtHead();
        break;
      }
      case 6: {
        myList.deleteAtTail();
        break;
      }
      case 7: {
        int index;
        cout << "Enter index: ";
        cin >> index;
        myList.deleteAtIndex(index);
        break;
      }
      case 8: {
        myList.reverseList();
        break;
      }
      case 9: {
        myList.sortList();
        break;
      }
      case 10: {
        int value;
        cout << "Enter value to count: ";
        cin >> value;
        int count = myList.countMultiples(value);
        cout << "Count of " << value << " in the list: " << count << endl;
        break;
      }
      case 11: {
        int value;
        cout << "Enter value to delete: ";
        cin >> value;
        myList.removeMultiples(value);
        break;
      }
      case 12: {
        myList.headTailSplit();
        break;
      }
      case 13: {
        cout << "Exiting." << endl;
        return 0;
      }
      default: {
        cout << "Invalid choice. Please try again." << endl;
        break;
      }
    }
  }

  return 0;
}
