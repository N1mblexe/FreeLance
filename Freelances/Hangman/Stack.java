public class Stack<T> {
    private int maxSize;
    private T[] stackArray;
    private int top;

    public Stack(int maxSize) {
        this.maxSize = maxSize;
        this.stackArray = (T[]) new Object[maxSize];
        this.top = -1;
    }

    public void push(T value) {
        if (isFull()) {
            //System.out.println("Stack is full. Cannot push element.");
            return;
        }
        stackArray[++top] = value;
    }

    public T pop() {
        if (isEmpty()) {
            //System.out.println("Stack is empty. Cannot pop element.");
            return null;
        }
        return stackArray[top--];
    }

    public T peek() {
        if (isEmpty()) {
            //System.out.println("Stack is empty. Cannot peek element.");
            return null;
        }
        return stackArray[top];
    }

    public boolean isFull() {
        return (top == maxSize - 1);
    }

    public boolean isEmpty() {
        return (top == -1);
    }

    public int size() {
        return top + 1;
    }

    public T get(int id)
    {
        return  stackArray[id];
    }
    public void set(T obj , int id)
    {
        stackArray[id] = obj;
    }

    public boolean contains(T value) {
        for (int i = 0; i <= top; i++) {
            if (stackArray[i].equals(value)) {
                return true;
            }
        }
        return false;
    }

}