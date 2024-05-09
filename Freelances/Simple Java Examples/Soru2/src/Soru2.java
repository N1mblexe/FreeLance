import java.util.*;
import java.io.*;

public class Soru2 
{

    public static void main(String[] args) throws IOException 
    {
        //Dosyayı kontrol etmek için tanımlıyoruz
        File file = new File("girdiQuiz1.txt");

        //Eğer dosya bulunamazsa dosyayı oluşturuyoruz
        if(!file.exists())
            file.createNewFile();
        
        BufferedReader br = null;
        try 
        {
            br = new BufferedReader(new FileReader("girdiQuiz1.txt"));
            String line;
            
            while ((line = br.readLine()) != null) 
            {
                //Token'ı ',' de next token'a geçecek şekilde ayarlıyoruz
                StringTokenizer st = new StringTokenizer(line, ",");
                Employee employee = null;
                
                try
                {
                //Ilk token'ı geçici bir değişkene atıyoruz
                String temp = st.nextToken();

                //Defaultsa new employee yapıyoruz
                if (temp.equals("Default"))
                     employee = new Employee();
                //
                else 
                {
                    //isim pozisyon gibi değerleri dosyadan alarak değişkenlere atıyoruz
                    String name = temp;
                    int age = Integer.parseInt(st.nextToken());
                    String department = st.nextToken();
                    String position = st.nextToken();
                    employee = new Employee(name, age, department, position);
                }
                //Employe'i yazdırıyoruz
                System.out.println(employee);
                }
                catch(NumberFormatException e)
                {
                    System.err.println("Dosyada duzen hatasi!!");
                }
            }
        } 
        finally 
        {
            if (br != null) 
                br.close();
        }
    }
}