public class Player
{
    GameObject gameObject;
    Vector2 SpawnPos;

    Player(Vector2 SpawnPos)
    {
        this.SpawnPos = SpawnPos;
        gameObject = new GameObject();
    }
    Player()
    {
        SpawnPos = new Vector2(10,10);
        gameObject = new GameObject();
    }

    public void setSpawnPos(Vector2 spawnPos) {
        SpawnPos = spawnPos;
    }

    boolean SpawnPlayer(MapData mapData) throws Exception
    {
        if (mapData.getDataAtPosition(SpawnPos) != ID.empty.ordinal())
            return false;

        gameObject.transform.position = SpawnPos;
        mapData.setDataToPosition(SpawnPos , ID.player.ordinal());

        return true;
    }

    protected void Move(MapData mapData , PlantingSpot plantingSpot)
    {

        Vector2 in = InputManager.getInput();
        Vector2 temp = Vector2.Addition(gameObject.transform.position ,in);

        try {
            if (mapData.isPositionValid(temp) && mapData.getDataAtPosition(temp) != ID.wall.ordinal())
            {
                if(mapData.isPositionValid(temp) && mapData.getDataAtPosition(temp) == ID.plantingSpot.ordinal() || mapData.isPositionValid(temp) && mapData.getDataAtPosition(temp) == ID.empty.ordinal())
                {
                    mapData.setDataToPosition(gameObject.transform.position , ID.empty.ordinal());
                    gameObject.transform.position = temp;
                    mapData.setDataToPosition(temp , ID.player.ordinal());
                }
                for(int i = 4;i < 8;i++)
                {
                    if(mapData.getDataAtPosition(temp) == i)
                    {
                        if (mapData.getDataAtPosition(Vector2.Addition(temp , in)) == ID.empty.ordinal() || mapData.getDataAtPosition(Vector2.Addition(temp , in)) == ID.plantingSpot.ordinal())
                        {
                            if(mapData.getDataAtPosition(Vector2.Addition(temp , in)) != ID.plantingSpot.ordinal()) {
                                mapData.setDataToPosition(Vector2.Addition(temp, in), i);
                            }
                            else
                                plantingSpot.next();
                            mapData.setDataToPosition(gameObject.transform.position , ID.empty.ordinal());
                            gameObject.transform.position = temp;
                            mapData.setDataToPosition(temp , ID.player.ordinal());
                            return;
                        }

                    }
                }


            }
        }
        catch (Exception ignored) {}
    }

    public void Update(MapData mapData , PlantingSpot plantingSpot)
    {
        Move(mapData , plantingSpot);
    }
}
