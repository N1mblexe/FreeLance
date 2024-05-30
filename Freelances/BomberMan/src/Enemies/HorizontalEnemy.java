package Enemies;

import Behaviour.BehaviourManager;
import Game.Vector2;
import Map.ID;
import Map.MapManager;

public class HorizontalEnemy extends BaseEnemy{
    public HorizontalEnemy(Vector2 position) {
        super(position, ID.horizontalEnemy , new Vector2(0 , 1));
    }
    @Override
    public void Update()
    {
        if(!Move(MapManager.Instance.getCurrentMap(), Vector2.Addition(position , dir)))
        {
            dir = Vector2.Multiply(dir , -1);
        }
    }
}
