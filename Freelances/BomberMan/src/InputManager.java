import java.util.Scanner;

//input'u daha anlaşılır ve rahat almak için bu sınıf kullanılır
public class InputManager
{
    //Bu fonksiyon w , a ,s ,d , e tuşlarını kontrol ederek input'u vector2'ye dönüştürerek geri döndürür
    //Eğer bomba konulduysa exception fırlatır
    static public Vector2 getInput() throws Exception
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
            case 'e', 'E' -> throw new Exception("Bomb");
        }
        return  temp;
    }
}
