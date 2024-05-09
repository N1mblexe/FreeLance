public class QueueHelper {
    public static void sortQueue(Queue<HighScore> scores) {
        int n = scores.size();

        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                HighScore first = scores.dequeue();
                HighScore second = scores.dequeue();

                if (first.score < second.score) {
                    scores.enqueue(first);
                    scores.enqueue(second);
                } else {
                    scores.enqueue(second);
                    scores.enqueue(first);
                }
            }
        }
    }

    public static void MakeItSeperate(Queue<HighScore> scores , Queue<String> str , Queue<Integer> qInt)
    {
        while (!scores.isEmpty())
        {
            HighScore hs = scores.dequeue();

            str.enqueue(hs.name);
            qInt.enqueue(hs.score);
        }
    }

    public static Stack<Character> StoCQueue(String str)
    {
        Stack<Character> qChar = new Stack<>(str.length());

        for(int i = 0; i < str.length();i++)
        {
            qChar.push(str.charAt(i));
        }

        return qChar;
    }
}
