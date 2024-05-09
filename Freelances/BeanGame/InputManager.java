import java.util.Scanner;

public class InputManager
{
    static public Vector2 getInput()
    {
        Scanner console = new Scanner(System.in);
        String inputStr = console.next();

        char input = inputStr.charAt(0);

        Vector2 temp = new Vector2(0,0);

        switch (input)
        {
            case 'w', 'W' -> temp.x = -1;
            case 'a', 'A' -> temp.y = -1;
            case 's', 'S' -> temp.x = 1;
            case 'd', 'D' -> temp.y = 1;
        }
        return  temp;
    }
}
