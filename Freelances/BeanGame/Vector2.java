public class Vector2
{
    public int x,y;

    Vector2(int x , int y)
    {
        this.x = x;
        this.y = y;
    }
    Vector2()
    {
        x = y = 0;
    }

    public boolean Equals(Vector2 vec2)
    {
        if(vec2.x == x && vec2.y == y)
            return  true;

        return  false;
    }

    public static Vector2 Addition(Vector2 a , Vector2 b)
    {
        return new Vector2(a.x + b.x , a.y +b.y);
    }


}
