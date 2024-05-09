//iki boyutlu veriler için kullanılan vektör sınıfı (karakterin konumu , karakterin baktığı yön, bombanını konumu gibi şeyler...)
public class Vector2
{
    //x ve y eksenindeki değerler
    public int x,y;

    //Constructor ile değerleri atama
    Vector2(int x , int y)
    {
        this.x = x;
        this.y = y;
    }
    Vector2()
    {
        x = y = 0;
    }

    //iki vektörün eşit olup olmamasını kontrol eden fonksiyon
    public boolean Equals(Vector2 vec2)
    {
        if(vec2.x == x && vec2.y == y)
            return  true;

        return  false;
    }

    //iki fonksyionu matematiksel olarak toplayan fonksiyon (ax + bx) , (ay + by)
    public static Vector2 Addition(Vector2 a , Vector2 b)
    {
        return new Vector2(a.x + b.x , a.y +b.y);
    }
}
