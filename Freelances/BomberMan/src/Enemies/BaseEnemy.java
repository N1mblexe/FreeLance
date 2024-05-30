package Enemies;

import Behaviour.MonoBehaviour;
import Game.BomberMan;
import Game.Vector2;
import Map.ID;
import Map.MapData;
import Map.MapManager;

public class BaseEnemy extends MonoBehaviour implements IEnemy
{
    private ID enemyOn = ID.empty;
    private ID id;
    protected Vector2 dir;
    protected Vector2 position;
    BaseEnemy(Vector2 position, ID id , Vector2 dir)
    {
        super();

        this.dir = dir;
        this.id = id;
        this.position = position;
    }

    public static BaseEnemy getEnemy(ID id , Vector2 pos)
    {
        if(id == ID.verticalEnemy)
        {
            return new VerticalEnemy(pos);
        }
        else if(id == ID.horizontalEnemy)
        {
            return new HorizontalEnemy(pos);
        }
        return null;
    }

    public boolean Move(MapData map , Vector2 newPos)
    {
        try
        {
            int data = map.getDataAtPosition(newPos);

            if(data == ID.player.ordinal())
            {
                BomberMan.Instance.LoseGame("Enemy killed you!!");
                return true;
            }
            if(data != ID.breakableWall.ordinal() && data != ID.wall.ordinal() && data != ID.bomb.ordinal())
            {
                enemyOn = ID.fromInteger(data);
                map.setDataToPosition(position , enemyOn.ordinal());
                position = newPos;
                map.setDataToPosition(position , id.ordinal());
                return true;
            }
            else
                return false;
        } catch (Exception e) {}
        return false;
    }



}
