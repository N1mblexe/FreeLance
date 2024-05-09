import java.io.*;
import java.util.Random;

public class Hangman
{
    public static void InitializeBoardStack(Stack<Character> BoardStack, int size) {
        for (int i = 0; i < size; i++) {
            BoardStack.push('_');
        }
    }

    public static void displayGameState(Stack<Character> BoardStack , Stack<Character> missingLetter , Stack<Character> letters, int score) {
        Stack<Character> temp = new Stack<>(BoardStack.size());

       System.out.print("Word: ");
       System.out.print(StackHelper.ToString(BoardStack));

       System.out.print("\tMisses: ");
       System.out.print(StackHelper.ToString(missingLetter));

       System.out.print("\tScore: " + score);

       System.out.print("\t");
       System.out.println(StackHelper.ToString(letters));

        System.out.println("\nGuess: ");
    }


    public static char revealRandomLetter(Stack<Character> WordStack, Stack<Character> BoardStack) {
        Random random = new Random();
        int index = random.nextInt(WordStack.size());
        char letter = WordStack.get(index);
        BoardStack.set(letter , index);
        return letter;
    }

    public static boolean checkGuess(char guess, Stack<Character> WordStack, Stack<Character> BoardStack) {
        boolean correctGuess = false;
        for (int i = 0; i < WordStack.size(); i++) {
            Character temp = WordStack.get(i);
            if (temp == guess) {
                BoardStack.set(guess , i);
                correctGuess = true;
            }
        }
        return correctGuess;
    }

    public static boolean isVowel(char letter) {
        return "AEIOU".indexOf(Character.toUpperCase(letter)) != -1;
    }

    public static boolean isGameOver(Stack<Character> WordStack, int score) {
        return (WordStack.isEmpty() || score <= 0);
    }

    public static void updateHighScores(Queue<Integer> QScore, Queue<String> QName, int score , String name) {


        try {
            BufferedWriter bw = new BufferedWriter(new FileWriter("highscoretable.txt"));
            bw.write(score + "," + name + "\n");
            bw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public  static String getRandomAnimal(Stack<String> SAnimal)
    {
        Random rnd = new Random();

        int index = rnd.nextInt(SAnimal.size());

        Stack<String> tempStack = new Stack<>(400);
        String temp;

        for(int i = 0;i < index;i++)
            tempStack.push(SAnimal.pop());

        String animal = SAnimal.peek();

        for(int i = 0;i < index;i++)
            SAnimal.push(tempStack.pop());

        return animal;
    }
    public static void InitiliazeLetters(Stack<Character> letters)
    {
        for (char c = 'a'; c <= 'z'; c++) {
            letters.push(c);
        }
    }

    public  static void displayScores()
    {
        String str = "";
        try (BufferedReader br = new BufferedReader(new FileReader("highscoretable.txt")))
        {
            String line;
            while ((line = br.readLine()) != null) {
                str += line;
            }
        } catch (IOException e) {
            System.out.println("Cannot find files");
        }

        if(!str.isEmpty())
            System.out.print(str);
    }

}

