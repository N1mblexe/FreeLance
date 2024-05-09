
public class StackHelper {
    public static void sortStack(Stack<Integer> stack) {
        Stack<Integer> tempStack = new Stack<>(400);

        while (!stack.isEmpty()) {
            int temp = stack.pop();

            while (!tempStack.isEmpty() && tempStack.peek() > temp) {
                stack.push(tempStack.pop());
            }

            tempStack.push(temp);
        }

        while (!tempStack.isEmpty()) {
            stack.push(tempStack.pop());
        }
    }

    public static Stack<Character> StackifyQueue(String word) {
        Stack<Character> stack = new Stack<>(50);
        for (int i = word.length() - 1; i >= 0; i--) {
            stack.push(word.charAt(i));
        }
        return stack;
    }

    //public static Character GetFromStack(Stack<Character> stack, int i) {
    //    if (i < 0 || i >= stack.size()) {
    //        System.out.println("Invalid index.");
    //        return null;
    //    }
    //    // Retrieve the character at index i
    //    Stack<Character> tempStack = new Stack<>(stack.size());
    //    Character result = null;
    //    for (int j = 0; j <= i; j++) {
    //        result = stack.pop();
    //        tempStack.push(result);
    //    }
    //    while (!tempStack.isEmpty()) {
    //        stack.push(tempStack.pop());
    //    }
    //    return result;
    //}

    //public static void SetToStack(Stack<Character> stack, int i, Character c) {
    //    if (i < 0 || i >= stack.size()) {
    //        System.out.println("Invalid index.");
    //        return;
    //    }
    //    // Replace the character at index i with c
    //    Stack<Character> tempStack = new Stack<>(stack.size());
    //    for (int j = 0; j < i; j++) {
    //        tempStack.push(stack.pop());
    //    }
    //    stack.pop(); // Remove the character at index i
    //    stack.push(c); // Push the new character
    //    while (!tempStack.isEmpty()) {
    //        stack.push(tempStack.pop());
    //    }
    //}
    public static void RemoveFromStack(Stack<Character> stack, Character c) {
        Stack<Character> tempStack = new Stack<>(stack.size());
        boolean found = false;
        while (!stack.isEmpty()) {
            Character current = stack.pop();
            if (current.equals(c)) {
                found = true;
                break;
            } else {
                tempStack.push(current);
            }
        }
        while (!tempStack.isEmpty()) {
            stack.push(tempStack.pop());
        }
        if (!found) {
            //System.out.println("Character " + c + " not found in the stack.");
        }
    }

    public static String ToString(Stack<Character> stack)
    {
        String str = "";
        Stack<Character> temp = new Stack<>(stack.size());

        while(!stack.isEmpty())
        {
            temp.push(stack.pop());
        }
        while(!temp.isEmpty())
        {
            Character c = temp.pop();
            str += c;
            stack.push(c);
        }

        return str;
    }

}
