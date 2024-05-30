package Enemies;

import Behaviour.BehaviourManager;
import Game.Vector2;
import Map.ID;
import Map.MapData;
import Map.MapManager;
import PlayerPackage.Player;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class EnemyManager
{
    List<BaseEnemy> enemies;
    public EnemyManager()
    {
        super();

        enemies = new ArrayList<BaseEnemy>();
    }

    public void InitEnemies() {
        for (var enemy: enemies)
            BehaviourManager.DeleteBehaviour(enemy);

        List<BaseEnemy> enemies = new ArrayList<>();

        MapData map = MapManager.Instance.getCurrentMap();

        BaseEnemy enemy = SpawnRandomEnemy(map);
        enemies.add(enemy);

        List<Vector2> spawnPositions = map.enemiesSpawnPos;
        List<ID> enemyTypes = map.enemyTypes;

        int i = 0;
        for (Vector2 pos : spawnPositions) {
            enemies.add(BaseEnemy.getEnemy(enemyTypes.get(i), pos));
            i++;
        }

    }

    private BaseEnemy SpawnRandomEnemy(MapData mapData) {
        Random r = new Random();
        Vector2 size = mapData.getSize();

        Vector2 spawnPos;
        int data = -1;
        do {
            spawnPos = new Vector2(r.nextInt(size.x), r.nextInt(size.y));
            try {
                data = mapData.getDataAtPosition(spawnPos);
            } catch (Exception e) {}
        }
        while (data != ID.empty.ordinal() && Vector2.Distance(spawnPos , Player.instance.getPosition()) > 4);

        ID enemyType = ID.fromInteger(ID.horizontalEnemy.ordinal() + r.nextInt(500)%2);

        return (BaseEnemy.getEnemy(enemyType , spawnPos));

    }
}
