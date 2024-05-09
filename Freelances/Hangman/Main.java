import java.util.Scanner;

public class Main {
    public static void main(String[] args)
    {
        Queue<String> QName = new Queue<>(400);
        Queue<Integer> QScore = new Queue<>(400);
        Stack<String> AnimalStack = new Stack<>(400);
        Stack<Character> LetterStack = new Stack<>(30);
        Stack<Character> MissingLetterStack = new Stack<>(30);

        Hangman.InitiliazeLetters(LetterStack);
        FileManager.readHighScores("highscoretable.txt", QScore, QName);
        FileManager.readAnimals("animals.txt" , AnimalStack);

        boolean playAgain = true;
        Scanner scanner = new Scanner(System.in);

        while (playAgain)
        {
            int score = 120;
            Stack<Character> WordStack = QueueHelper.StoCQueue(Hangman.getRandomAnimal(AnimalStack));
            Stack<Character> BoardStack = new Stack<>(WordStack.size());

            Hangman.InitializeBoardStack(BoardStack, WordStack.size());

            boolean gameEnd = false;
            boolean jokerUsed = false;

            while (!gameEnd)
            {
                Hangman.displayGameState(BoardStack , MissingLetterStack , LetterStack, score);

                char guess = promptUser(scanner, jokerUsed);
                if(MissingLetterStack.contains(guess) || BoardStack.contains(guess))
                {
                    System.out.println("\nYou entered the same letter before");
                    continue;
                }

                if (guess == '.') {
                    if(!jokerUsed)
                    {
                        guess = Hangman.revealRandomLetter(WordStack, BoardStack);
                        jokerUsed = true;
                        System.out.println("Used Joker!!");
                    }
                    System.out.println("No Joker left!!");
                }
                else if(guess < 'a' || guess > 'z')
                {
                    System.out.println("Enter a valid input");
                    continue;
                }
                else if (Hangman.checkGuess(guess, WordStack, BoardStack)) {}
                else
                {
                    score -= (Hangman.isVowel(guess) ? 15 : 20);
                    handleIncorrectGuess(guess, WordStack, LetterStack, MissingLetterStack, score);
                }

                if (Hangman.isGameOver(WordStack, score)) {
                    gameEnd = true;
                    System.out.println("You lost!");
                }
                if(!BoardStack.contains('_')) {
                    gameEnd = true;
                    System.out.println("You win!");
                }
            }

            Hangman.displayScores();

            System.out.println("\nWord :" + StackHelper.ToString(WordStack));
            System.out.println("Your score: " + score);

            System.out.println("What is your name:");
            String name = scanner.nextLine();
            Hangman.updateHighScores(QScore, QName, score , name);

            System.out.print("Do you want to play again? (Y/N): ");
            playAgain = scanner.nextLine().trim().equalsIgnoreCase("Y");

            LetterStack = new Stack<>(LetterStack.size());
            Hangman.InitiliazeLetters(LetterStack);

            MissingLetterStack = new Stack<>(MissingLetterStack.size());
        }
        scanner.close();
    }

    private static char promptUser(Scanner scanner, boolean jokerUsed) {
        String str = scanner.nextLine().toLowerCase();
        if(str.isEmpty())
            str = ",";

        if(str.equals("joker"))
            return '.';
        return str.charAt(0);
    }

    private static void handleIncorrectGuess(char guess, Stack<Character> wordStack, Stack<Character> letterStack,
                                             Stack<Character> missingLetterStack, int score) {
        missingLetterStack.push(guess);
        StackHelper.RemoveFromStack(letterStack, guess);
    }

}
