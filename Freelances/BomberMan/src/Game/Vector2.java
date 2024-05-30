package Game;

//iki boyutlu veriler için kullanılan vektör sınıfı (karakterin konumu , karakterin baktığı yön, bombanını konumu gibi şeyler...)
public class Vector2
{
    //x ve y eksenindeki değerler
    public int x,y;

    //Constructor ile değerleri atama
    public Vector2(int x, int y)
    {
        this.x = x;
        this.y = y;
    }
    public Vector2()
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

    public Vector2 normalized()
    {
        int a , b;

        a = x;
        b = y;

        if(a > 1) a = 1;
        if(a < -1) a = -1;
        if(b > 1) b = 1;
        if(b < -1) b = -1;

        return new Vector2(a , b);
    }

    public float Magnitude()
    {
        return (float) Math.sqrt(x * x + y * y);
    }

    public static float Distance(Vector2 a,  Vector2 b)
    {
        return Substraction(a , b).Magnitude();
    }

    public static Vector2 Addition(Vector2 a , Vector2 b)
    {
        return new Vector2(a.x + b.x , a.y +b.y);
    }
    public static Vector2 Substraction(Vector2 a , Vector2 b)
    {
        return new Vector2(a.x - b.x , a.y -b.y);
    }
    public static Vector2 Multiply(Vector2 a , int b){ return new Vector2(a.x * b , a.y * b);}

    @Override
    public String toString() {
        return "(" + x  + "," + y + ")";
    }
}
