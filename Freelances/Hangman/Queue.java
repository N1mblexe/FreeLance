public class Queue<T> {
    private int maxSize;
    private T[] queueArray;
    private int front;
    private int rear;
    private int currentSize;

    public Queue(int size) {
        this.maxSize = size;
        this.queueArray = (T[]) new Object[maxSize];
        this.front = 0;
        this.rear = -1;
        this.currentSize = 0;
    }

    public void enqueue(T value) {
        if (!isFull()) {
            rear = (rear + 1) % maxSize;
            queueArray[rear] = value;
            currentSize++;
        } else {
            System.out.println("Queue is full. Cannot enqueue " + value);
        }
    }

    public T dequeue() {
        if (!isEmpty()) {
            T dequeuedItem = queueArray[front];
            front = (front + 1) % maxSize;
            currentSize--;
            return dequeuedItem;
        } else {
            System.out.println("Queue is empty. Cannot dequeue.");
            return null; // or throw an exception
        }
    }

    public T peek() {
        if (!isEmpty()) {
            return queueArray[front];
        } else {
            System.out.println("Queue is empty. Cannot peek.");
            return null; // or throw an exception
        }
    }

    public boolean isFull() {
        return currentSize == maxSize;
    }

    public boolean isEmpty() {
        return currentSize == 0;
    }

    public int size() {
        return currentSize;
    }


}
