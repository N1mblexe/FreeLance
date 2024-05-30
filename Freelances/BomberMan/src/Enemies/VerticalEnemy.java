package Enemies;

import Behaviour.BehaviourManager;
import Game.Vector2;
import Map.ID;
import Map.MapManager;

public class VerticalEnemy extends BaseEnemy{
    public VerticalEnemy(Vector2 position) {
        super(position, ID.verticalEnemy , new Vector2(1 , 0));
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
