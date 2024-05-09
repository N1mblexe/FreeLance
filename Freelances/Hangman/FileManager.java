import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class FileManager
{
    public static void readHighScores(String filename, Queue<Integer> qScore, Queue<String> qName) {
        Queue<HighScore> hsQ = new Queue<>(400);
        try (BufferedReader br = new BufferedReader(new FileReader(filename)))
        {
            String line;
            while ((line = br.readLine()) != null) {
                String[] parts = line.split(" ");
                if (parts.length == 2) {
                    String name = parts[0];
                    int score = Integer.parseInt(parts[1]);
                    HighScore hs = new HighScore(score, name);
                    hsQ.enqueue(hs);
                    qName.enqueue(name);
                }
            }
        } catch (IOException e) {
            System.out.println("Cannot find files");
        }
        QueueHelper.sortQueue(hsQ);
        QueueHelper.MakeItSeperate(hsQ , qName , qScore);
    }
    public static void readAnimals(String filename , Stack<String> animals)
    {
        try(BufferedReader br = new BufferedReader(new FileReader(filename)))
        {
            String line;
            while((line = br.readLine()) != null)
            {
                animals.push(line);
            }
        }
        catch (IOException e)
        {
            System.out.println("Cannot find files");
        }
    }
}
