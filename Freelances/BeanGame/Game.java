public class Game
{
    protected Map map;
    protected Player player;
    protected PlantingSpot plantingSpot;


    public void Start()
    {
        plantingSpot = new PlantingSpot();
        player = new Player();
        map = new Map();

        map.mapData.setTestData();
        player.setSpawnPos(map.mapData.playerSpawnPos);
        try {
            player.SpawnPlayer(map.mapData);
        } catch (Exception ignored) {}
    }
    protected void Update()
    {
        System.out.println(MapData.getVisualizedData(map.mapData.staticData));
        map.mapData.setDataToPosition(map.mapData.plantingSpawnPos, ID.plantingSpot.ordinal());
        player.Move(map.mapData , plantingSpot);
    }
    protected void LateUpdate()
    {
        map.mapData.LateUpdate();
    }
    public void Play()
    {
        Start();
        while (!plantingSpot.gameFinished)
        {
            Update();
            LateUpdate();
        }
        System.out.println("\nOyunu kazandiniz!!!");
    }

}
