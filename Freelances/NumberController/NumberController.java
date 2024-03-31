import java.io.*;
import java.util.*;

public class NumberController
{
    //20 adet "int" tipinde sayı tutacak bir dizi (array)
    private int[] numbers;

    //Constructer
    public NumberController(String fileName) throws FileNotFoundException 
    {
        File ffl = new File(fileName);
        if(ffl.exists()) 
        {
            Scanner s = new Scanner(ffl);
            int size = s.nextInt();
            numbers = new int[size];
            for (int i = 0; i < size; i++) 
            {
                try
                {
                   numbers[i] = s.nextInt();
                }
                catch(Exception e)
                {
                    break;
                }
            }
            s.close();
            bubbleSort(numbers);
        }
        else 
        {
            throw new FileNotFoundException("File not found or cannot be opened.");
        }
    }


    //Statik bubble sort algoritması
    public static void bubbleSort(int[] dizi)
    {
        int temp1 = dizi.length;
        for (int ilk = 0; ilk < temp1-1; ilk++)
        {
            for (int ikinci = 0; ikinci < temp1-ilk-1; ikinci++)
            {
                if (dizi[ikinci] > dizi[ikinci+1])
                {
                    int temp2 = dizi[ikinci];
                    dizi[ikinci] = dizi[ikinci+1];
                    dizi[ikinci+1] = temp2;
                }
            }
        }
    }
    


    //Binary search algoritması
    public boolean searchBinary(int key)
    {
        int low = 0;
        int high;
        try
        {
            high = numbers.length - 1;
        }
        catch(Exception e)
        {
            return false;
        }
        while (low <= high) {
            int mid = (low + high) / 2;
            if (numbers[mid] == key)
            {
                return true;
            }
            else if (numbers[mid] < key)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return false;
    }

    //Sequential search algoritması
    public boolean searchSequential(int key)
    {
        try
        {
            for (int a = 0; a < numbers.length; a++)
                if (numbers[a] == key)
                    return true;
        }
        catch(Exception ignored)
        {
            return false;
        }
        return false;
    }
}
