public class MapData
{
    //Map iki boyutlu bir int dizisi olarak tututuluyor
    public int[][] data;

    Vector2 playerSpawnPos;

    //Girilen posizyonun mapin içinde kalıp kalmadığını hesaplayıp ona göre true ya da false döndüren fonksiyon
    boolean isPositionValid(Vector2 pos)
    {
        return data.length >= pos.x && data[0].length >= pos.y && pos.y >= 0 && pos.x >= 0;
    }

    //Girilen dataya göre elimdeki datayı güncelleyen fonksiyon
    //Aynı zamanda yeni gelen dataya göre karakterin başlangıç konumunu hesaplıyor
    public void setData(int[][] data)
    {
        this.data = data;

        setPlayerSpawnPos();
    }

    //Girilen pozisyondaki veriyi döndüren fonksiyon
    public int getDataAtPosition(Vector2 pos) throws Exception
    {
        if(!isPositionValid(pos))
            throw new Exception("Invalid pos!!");
        return data[pos.x][pos.y];
    }

    //Girilen pozisyona verilen veriyi atayan fonksiyon
    public void setDataToPosition(Vector2 pos , int data)
    {
        if(isPositionValid(pos))
            this.data[pos.x][pos.y] = data;
    }

    //Elimizdeki dataya göre karakterin başlangıç konumunu bulan fonksiyon
    private void setPlayerSpawnPos()
    {
        for (int i = 0; i < data.length;i++)
        {
            for (int j = 0; j < data[i].length;j++)
            {
                Vector2 temp = new Vector2(i , j);
                if(data[i][j]  == ID.spawnPos.ordinal())
                {
                    playerSpawnPos = temp;
                    return;
                }
            }

        }
    }


    //Bu fonksiyonu mapleri dosyadan almayı yapmadan önce yazdım , sadece test etmek amaçlı

    //public void setTestData()
    //{
    //    data = new int[][]
    //           //0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
    //           {{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},  //  0
    //            {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 2},  //  1
    //            {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 2},  //  2
    //            {2, 0, 6, 6, 6, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 2},  //  3
    //            {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 6, 0, 2},  //  4
    //            {2, 0, 0, 0, 0, 0, 0, 0, 4, 0, 6, 0, 0, 0, 0, 2},  //  5
    //            {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 2},  //  6
    //            {2, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 6, 6, 2},  //  7
    //            {2, 0, 0, 0, 0, 0, 0, 6, 0, 0, 6, 0, 0, 0, 0, 2},  //  8
    //            {2, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 2},  //  9
    //            {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 2}}; //  10

    //    setPlayerSpawnPos();
    //}



    //Elimdeki veriyi görsel haline çeviren fonksiyon
    public String getVisualizedData()
    {
        StringBuilder temp = new StringBuilder(new String());
        for (int x = 0 ; x < data.length ; x++)
        {
            for(int y = 0; y < data[x].length ; y++)
            {
                // her bir verinin kendine ait bir sembolü var
                if(data[x][y] == ID.empty.ordinal())            temp.append("   ");
                if(data[x][y] == ID.player.ordinal())           temp.append(" O ");
                if(data[x][y] == ID.wall.ordinal())             temp.append("□□□");
                if(data[x][y] == ID.exit.ordinal())             temp.append(" X ");
                if(data[x][y] == ID.spawnPos.ordinal())         temp.append("   ");
                if(data[x][y] == ID.bomb.ordinal())             temp.append(" ! ");
                if(data[x][y] == ID.breakableWall.ordinal())    temp.append(" # ");
            }
            temp.append("\n");
        }
        return temp.toString();
    }
}
