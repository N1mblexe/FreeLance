using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace UM
{
    public class StackX<T>
    {
        private int maxSize; // size of stack array
        private T[] stackArray;
        private int top; // top of stack

        //--------------------------------------------------------------
        public StackX(int s = 20) // constructor
        {
            maxSize = s; // set array size
            stackArray = new T[maxSize]; // create array
            top = -1; // no items yet
        }

        //--------------------------------------------------------------
        public void Push(T item) // put item on top of stack
        {
            if (top == maxSize - 1)
            {
                throw new InvalidOperationException("Stack is full");
            }

            stackArray[++top] = item; // increment top, insert item
        }

        //--------------------------------------------------------------
        public T Pop() // take item from top of stack
        {
            if (top == -1)
            {
                throw new InvalidOperationException("Stack is empty");
            }

            return stackArray[top--]; // access item, decrement top
        }

        //--------------------------------------------------------------
        public T Peek() // peek at top of stack
        {
            if (top == -1)
            {
                throw new InvalidOperationException("Stack is empty");
            }

            return stackArray[top];
        }

        //--------------------------------------------------------------
        public bool IsEmpty() // true if stack is empty
        {
            return (top == -1);
        }

        //--------------------------------------------------------------
        public bool IsFull() // true if stack is full
        {
            return (top == maxSize - 1);
        }
        //--------------------------------------------------------------

        public T this[int index]
        {
            get
            {
                if (index < 0 || index > top)
                {
                    throw new IndexOutOfRangeException("Index is out of range");
                }

                return stackArray[index];
            }
            set
            {
                if (index < 0 || index > top)
                {
                    throw new IndexOutOfRangeException("Index is out of range");
                }

                stackArray[index] = value;
            }
        }

    }
    public class QueueX<T>
    {
        private int maxSize; // size of queue array
        private T[] queueArray;
        private int front; // front of the queue
        private int rear; // rear of the queue
        private int itemCount; // current number of items in the queue

        //--------------------------------------------------------------
        public QueueX(int s = 20) // constructor
        {
            maxSize = s; // set array size
            queueArray = new T[maxSize]; // create array
            front = 0; // initialize front
            rear = -1; // initialize rear
            itemCount = 0; // no items yet
        }

        //--------------------------------------------------------------
        public void Enqueue(T item) // insert item at rear of queue
        {
            if (itemCount == maxSize)
            {
                throw new InvalidOperationException("Queue is full");
            }

            if (rear == maxSize - 1)
            {
                rear = -1; // wrap around
            }

            queueArray[++rear] = item; // increment rear, insert item
            itemCount++;
        }

        //--------------------------------------------------------------
        public T Dequeue() // remove item from front of queue
        {
            if (itemCount == 0)
            {
                throw new InvalidOperationException("Queue is empty");
            }

            T temp = queueArray[front++]; // get value and increment front
            if (front == maxSize)
            {
                front = 0; // wrap around
            }

            itemCount--;
            return temp;
        }

        //--------------------------------------------------------------
        public T Peek() // peek at front of queue
        {
            if (itemCount == 0)
            {
                throw new InvalidOperationException("Queue is empty");
            }

            return queueArray[front];
        }

        //--------------------------------------------------------------
        public bool IsEmpty() // true if queue is empty
        {
            return (itemCount == 0);
        }

        //--------------------------------------------------------------
        public bool IsFull() // true if queue is full
        {
            return (itemCount == maxSize);
        }

        //--------------------------------------------------------------
        public int Count() // number of items in the queue
        {
            return itemCount;
        }
    }
}

