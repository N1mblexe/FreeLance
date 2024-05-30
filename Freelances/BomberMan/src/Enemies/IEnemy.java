package Enemies;

import Game.Vector2;
import Map.MapData;

public interface IEnemy {
    public boolean Move(MapData map , Vector2 newPos);
}
