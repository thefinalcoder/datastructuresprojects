#include <iostream>
#include <string>
using namespace std;

class PrintItem{
public:
  string fileName;
  float fileSize;

  PrintItem(string fileName, float fileSize){
    this->fileName = fileName;
    this->fileSize = fileSize;
  }

  ~PrintItem(){
    cout<< "File:" << fileName << " Destroyed" << endl;
  }

  void print(){
    cout << "File name: " << fileName << " File Size: " << fileSize << endl;

  }
};

template <typename T> class Node {
public:
  T *data;
  Node<T> *nextNode;

  Node(T *data) {
    this->data = data;
    nextNode = nullptr;
  }

  ~Node(){
    this->data = data;
    nextNode = nullptr;
  }

  void print() {
    data->print(); 
  }
};

template <typename T> class LLStack {
private:
  Node<T> *top;
  int stackSize;
  const int SMAXITEMS = 100;

public:
  LLStack(){
    top = nullptr;
    stackSize = 0;
  }

  ~LLStack(){
    while(!isEmpty()){
      Node<T> *temp = top;
      top = top->nextNode;
      delete temp->data;
      delete temp;
    }
  }

  bool isFull(){
    return stackSize == SMAXITEMS;
  }

  bool isEmpty(){
    return top == nullptr;
  }

  void push(T* item){
    if(!isFull()){

      Node<T> *newNode = new Node<T>(item);
      newNode ->nextNode = top;
      top = newNode;
      stackSize++;

    }
    else{
      cout << "Stack Overflow" << endl;
    }
  }
    void pop(){
      if(!isEmpty()){
        Node<T> *temp = top;
        top = top->nextNode;
        delete temp;
        stackSize--;
    }
      else{
        cout << "Stack Underflow" << endl;
      }
  }

    T* peek(){
      if(!isEmpty()){
        return top->data;
      }
      else{
        cout << "Stack Empty" << endl;
        return nullptr;
      }
    }
  };

template <typename T> class StackQ {
private:
    LLStack<T>* enQStack;
    LLStack<T>* deQStack;
    int queueSize;
    const int QMAXITEMS = 100;

public:
    StackQ() {
        enQStack = new LLStack<T>();
        deQStack = new LLStack<T>();
        queueSize = 0;
    }

    ~StackQ() {
        delete enQStack;
        delete deQStack;
    }

    bool isFull() {
        return queueSize == QMAXITEMS;
    }

    bool isEmpty() {
        return queueSize == 0;
    }

    void enqueue(T* item) {
        if(!isFull()) {
            enQStack->push(item);
            queueSize++;
        } else {
            cout << "Queue Overflow" << endl;
        }
    }

    void dequeue() {
        if(!isEmpty()) {
            if(deQStack->isEmpty()) {
                while(!enQStack->isEmpty()) {
                    deQStack->push(enQStack->peek());
                    enQStack->pop();
                }
            }
          
            deQStack->pop();
            queueSize--;
        } else {
            cout << "Queue Underflow" << endl;
        }
    }

    T* peek() {
        if(!isEmpty()) {
            if(deQStack->isEmpty()) {
                while(!enQStack->isEmpty()) {
                    deQStack->push(enQStack->peek());
                    enQStack->pop();
                }
            }
            return deQStack->peek();
        } else {
            cout << "Queue Empty" << endl;
            return nullptr;
        }
    }

    int getQueueSize() const {
        return queueSize;
    }

    void displayQueue() {
        if(isEmpty()) {
            cout << "Queue is empty." << endl;
            return;
        }

        LLStack<T> temp;
        while(!deQStack->isEmpty()) {
            temp.push(deQStack->peek());
            deQStack->pop();
        }

        while(!temp.isEmpty()) {
            temp.peek()->print();
            deQStack->push(temp.peek());
            temp.pop();
        }

        while(!enQStack->isEmpty()) {
            temp.push(enQStack->peek());
            enQStack->pop();
        }

        while(!temp.isEmpty()) {
            temp.peek()->print();
            enQStack->push(temp.peek());
            temp.pop();
        }
    }


    void displayStacks() {
        cout << "enQStack items:" << endl;
        displayStackItems(enQStack);

        cout << "deQStack items:" << endl;
        displayStackItems(deQStack);
    }

private:
    void displayStackItems(LLStack<T>* stack) {
        if(stack->isEmpty()) {
            cout << "Stack is empty." << endl;
            return;
        }

        LLStack<T> temp;
        while(!stack->isEmpty()) {
            temp.push(stack->peek());
            stack->pop();
        }

        while(!temp.isEmpty()) {
            temp.peek()->print();
            stack->push(temp.peek());
            temp.pop();
        }
      
    }
};

int main() {
    StackQ<PrintItem> printQueue;

    while (true) {
        cout << "a. Add Item to print queue" << endl;
        cout << "b. Delete from print queue" << endl;
        cout << "c. Peek from the print queue" << endl;
        cout << "d. Display the print queue" << endl;
        cout << "e. Display print queue size" << endl;
        cout << "f. Display enQStack and deQStack" << endl;
        cout << "g. Exit" << endl;
        cout << "Enter your choice: ";

        char choice;
        cin >> choice;

        string filename;
        float filesize;

        switch (choice) {
        case 'a':
            cout << "Enter file name: ";
            cin >> filename;
            cout << "Enter file size: ";
            cin >> filesize;
            printQueue.enqueue(new PrintItem(filename, filesize));
            break;

        case 'b':
            printQueue.dequeue();
            break;

        case 'c':
            if (printQueue.peek() != nullptr)
                printQueue.peek()->print();
            break;

        case 'd':
            printQueue.displayQueue();
            break;

        case 'e':
            cout << "Queue Size: " << printQueue.getQueueSize() << endl;
            break;

        case 'f':
            printQueue.displayStacks();
            break;

        case 'g':
            cout << "Exiting..." << endl;
            return 0;

        default:
            cout << "Invalid choice!" << endl;
            break;
        }
    }

    return 0;
}


