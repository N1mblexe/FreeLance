package Map;

import Game.FileManager;
import Game.Vector2;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class MapData
{
    public static class DisplaySettings
    {
        private List<String> chars;

        public void setSettings(String[] val)
        {
            chars = Arrays.stream(val).toList();
        }

        public static DisplaySettings DefaultSettings()
        {
            DisplaySettings ds = new DisplaySettings();

            ds.chars.add("   ");
            ds.chars.add(" O ");
            ds.chars.add("□□□");
            ds.chars.add(" X ");
            ds.chars.add("   ");
            ds.chars.add(" ! ");
            ds.chars.add(" # ");
            ds.chars.add(" R ");
            ds.chars.add(" S ");
            ds.chars.add(" P ");
            ds.chars.add(" B ");
            ds.chars.add(" I ");
            ds.chars.add(" H ");
            ds.chars.add(" V ");

            return ds;
        }
    }
    DisplaySettings ds;
    public MapData()
    {
        try {
            ds = FileManager.instance.GetDisplaySettings();
        }catch (Exception e)
        {
            ds = DisplaySettings.DefaultSettings();
        }
    }


    //Map iki boyutlu bir int dizisi olarak tututuluyor
    public int[][] data;

    public Vector2 playerSpawnPos;
    public List<Vector2> enemiesSpawnPos;
    public List<ID> enemyTypes;


    public Vector2 getSize()
    {
        return new Vector2(data.length , data[0].length);
    }

    //Girilen posizyonun mapin içinde kalıp kalmadığını hesaplayıp ona göre true ya da false döndüren fonksiyon
    public boolean isPositionValid(Vector2 pos)
    {
        return data.length >= pos.x && data[0].length >= pos.y && pos.y >= 0 && pos.x >= 0;
    }

    //Girilen dataya göre elimdeki datayı güncelleyen fonksiyon
    //Aynı zamanda yeni gelen dataya göre karakterin başlangıç konumunu hesaplıyor
    public void setData(int[][] data)
    {
        this.data = data;

        setSpawnPos();
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
    private void setSpawnPos()
    {
        enemyTypes = new ArrayList<>();
        enemiesSpawnPos = new ArrayList<>();

        for (int i = 0; i < data.length;i++)
        {
            for (int j = 0; j < data[i].length;j++)
            {
                Vector2 temp = new Vector2(i , j);
                if(data[i][j]  == ID.spawnPos.ordinal())
                {
                    playerSpawnPos = temp;
                }
                if(data[i][j] == ID.verticalEnemy.ordinal() || data[i][j] == ID.horizontalEnemy.ordinal())
                {
                    enemiesSpawnPos.add(temp);
                    enemyTypes.add(ID.fromInteger(data[i][j]));
                }
            }

        }
    }

    //Elimdeki veriyi görsel haline çeviren fonksiyon
    public String getVisualizedData()
    {
        StringBuilder temp = new StringBuilder();
        for (int[] datum : data) {
            for (int i : datum) {
                // her bir verinin kendine ait bir sembolü var
                if (i == ID.empty.ordinal()) temp.append(ds.chars.get(0));
                if (i == ID.player.ordinal()) temp.append(ds.chars.get(1));
                if (i == ID.wall.ordinal()) temp.append(ds.chars.get(2));
                if (i == ID.exit.ordinal()) temp.append(ds.chars.get(3));
                if (i == ID.spawnPos.ordinal()) temp.append(ds.chars.get(4));
                if (i == ID.bomb.ordinal()) temp.append(ds.chars.get(5));
                if (i == ID.breakableWall.ordinal()) temp.append(ds.chars.get(6));
                if (i == ID.runPower.ordinal()) temp.append(ds.chars.get(7));
                if (i == ID.skateBoardPower.ordinal()) temp.append(ds.chars.get(8));
                if (i == ID.punchPower.ordinal()) temp.append(ds.chars.get(9));
                if (i == ID.multiBombPower.ordinal()) temp.append(ds.chars.get(10));
                if (i == ID.shieldPower.ordinal()) temp.append(ds.chars.get(11));
                if (i == ID.horizontalEnemy.ordinal()) temp.append(ds.chars.get(12));
                if (i == ID.verticalEnemy.ordinal()) temp.append(ds.chars.get(13));
            }
            temp.append("\n");
        }
        return temp.toString();
    }
}
