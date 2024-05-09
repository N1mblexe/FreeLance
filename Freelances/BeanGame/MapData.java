public class MapData
{
    public int[][] data;
    public int [][] staticData;

    Vector2 playerSpawnPos;
    Vector2 plantingSpawnPos;

    boolean isPositionValid(Vector2 pos)
    {
        return data.length >= pos.x && data[0].length >= pos.y && pos.y >= 0 && pos.x >= 0;
    }

    public void setData(int[][] data)
    {
        this.data = data;
        staticData = data;
    }

    public int getDataAtPosition(Vector2 pos) throws Exception
    {
        if(!isPositionValid(pos))
            throw new Exception("Invalid pos!!");
        return data[pos.x][pos.y];
    }

    public void setDataToPosition(Vector2 pos , int data)
    {
        if(isPositionValid(pos))
            this.data[pos.x][pos.y] = data;
    }
    public void setTestData()
    {
        playerSpawnPos = new Vector2(8,9);
        plantingSpawnPos = new Vector2(7,13);

        staticData = new int[][]
                //0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
                {{1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //  0
                 {1, 1, 2, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //  1
                 {1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1},  //  2
                 {2, 2, 2, 1, 1, 7, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1},  //  3
                 {2, 1, 1, 5, 1, 6, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1},  //  4
                 {2, 1, 2, 1, 2, 2, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2},  //  5
                 {2, 1, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 1, 1, 1, 2},  //  6
                 {2, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},  //  7
                 {2, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 1, 1, 1, 2},  //  8
                 {1, 1, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2},  //  9
                 {1, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1}}; //  10


        data = staticData;
        setDataToPosition(plantingSpawnPos , ID.plantingSpot.ordinal());
    }

    public static String getVisualizedData(int [][] data)
    {
        String temp = new String();
        for (int x = 0 ; x < data.length ; x++)
        {
            for(int y = 0; y < data[x].length ; y++)
            {
                if(data[x][y] == 1)     temp += "   ";
                if(data[x][y] == 2)     temp += "□□□";
                if(data[x][y] == 3)     temp += " O ";
                if(data[x][y] == 4)     temp += " A ";
                if(data[x][y] == 5)     temp += " B ";
                if(data[x][y] == 6)     temp += " C ";
                if(data[x][y] == 7)     temp += " D ";
                if(data[x][y] == 9)     temp += " X ";
            }
            temp += "\n";
        }
        return temp;
    }

    public void LateUpdate()
    {
        data = staticData;
    }
}
