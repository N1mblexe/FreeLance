package PlayerPackage;

import Behaviour.MonoBehaviour;
import Game.Bomb;
import Game.BomberMan;
import Game.InputManager;
import Game.Vector2;
import Map.ID;
import Map.MapData;
import Map.MapManager;

//Bu sınıf Oyuncuyu temsil eder ve temel özelliklerini ve metodlarını taşır
public class Player extends MonoBehaviour
{
    public static Player instance;

    private AbilityStates state = AbilityStates.none;
    public String getAbility(){return state.toString();}

    private Bomb currBomb = null;
    public void deleteBomb()
    {
        //Behaviour.BehaviourManager.DeleteBehaviour(currBomb);
        currBomb = null;
    }

    private boolean returnToNormal = false;
    private boolean punchAvailable = false;
    private boolean multiBomb = false;
    private boolean shield = false;
    public boolean getShield() { return  shield; }

    ID playerOn = ID.empty;

    private Vector2 position;
    public Vector2 getPosition()
    {
        return position;
    }
    private Vector2 SpawnPos;
    private Vector2 dir;

    public String getDirection()
    {
        if(dir.x == 1)  return "Down";
        if(dir.x == -1) return "Up";
        if(dir.y == 1)  return "Right";
        if(dir.y == -1) return "Left";

        return "?";
    }

    private int     returnTime = 10;
    private int     stepAmount = 0;
    private final int     maxStep;

    public int StepsLeft()
    {
        return maxStep - stepAmount;
    }


    public Player(int maxStep)
    {
        super();

        this.maxStep = maxStep;
        this.position = new Vector2();
        SpawnPos = new Vector2(5,5);
        dir = new Vector2(1 , 0);
    }

    //Karkateri map'in spawn konumuna göre spawn eden fonksiyon
    public void SpawnPlayer(MapData mapData) throws Exception
    {
        instance = this;

        SpawnPos = mapData.playerSpawnPos;

        if (mapData.getDataAtPosition(SpawnPos) != ID.spawnPos.ordinal())
            return;

        position = SpawnPos;
        mapData.setDataToPosition(SpawnPos , ID.player.ordinal());

    }
    @Override
    public void Update()
    {
        if(returnToNormal)
            if(--returnTime <= 0)
            {
                state = AbilityStates.none;
                returnTime = 0;
                returnToNormal = false;

                shield = false;

            }
    }

    public void HandleInput(MapData mapData)
    {
        if(maxStep - stepAmount <= 0)
            BomberMan.Instance.LoseGame("Out of steps!!");

        Vector2 playerVelocity;

        EPlayerAction action = InputManager.getInput();
        playerVelocity = InputManager.GetVelocity();

        switch (action)
        {
            case move:
                if(state == AbilityStates.run)
                   playerVelocity = CalculateRunVelocity(mapData ,  playerVelocity);
                if(state == AbilityStates.skateboard)
                    playerVelocity = CalculateSkateboardVelocity(mapData , playerVelocity);
                if(state == AbilityStates.punch)
                    punchAvailable = true;
                if(state == AbilityStates.multiBomb)
                    multiBomb = true;
                if(state == AbilityStates.shield)
                {
                    shield = true;
                    returnTime = 15;
                    returnToNormal = true;
                }

                Move(mapData , playerVelocity);
                break;

            case setBomb:
                PlaceBomb();
                break;

            case useAbility:
                if(punchAvailable)
                    Punch(mapData);
                break;

            case undefinedInput:
                break;
        }
        stepAmount++;
    }

    private void HandleCollision(MapData mapData , Vector2 collisionPos)
    {
        try {
            if(mapData.isPositionValid(collisionPos) && mapData.getDataAtPosition(collisionPos) != ID.wall.ordinal())
            {
                ID nextPos = ID.fromInteger(mapData.getDataAtPosition(collisionPos));

                if(nextPos == ID.exit)
                {
                    BomberMan.Instance.NextMap();
                    return;
                }
                if(nextPos == ID.horizontalEnemy || nextPos == ID.verticalEnemy)
                    BomberMan.Instance.LoseGame("Enemy killed you!");
                if(nextPos != ID.breakableWall)
                {
                    HandlePowerUpCollisions(nextPos);
                    Step(mapData , collisionPos);
                }


            }
        } catch (Exception ignored) {}
    }
    private void HandlePowerUpCollisions(ID nextPos)
    {
        if(state == AbilityStates.none)
        {
            if (nextPos == ID.runPower)
                state = AbilityStates.run;
            else if (nextPos == ID.skateBoardPower)
                state = AbilityStates.skateboard;
            else if (nextPos == ID.punchPower)
                state = AbilityStates.punch;
            else if (nextPos == ID.multiBombPower)
                state = AbilityStates.multiBomb;
            else if (nextPos == ID.shieldPower)
                state = AbilityStates.shield;

            if(state != AbilityStates.none)
                playerOn = ID.empty;
        }
    }

    private void Move(MapData mapData , Vector2 playerVelocity)
    {
        dir = playerVelocity.normalized();
        Vector2 temp = Vector2.Addition(position , playerVelocity);

        HandleCollision(mapData , temp);
    }

    //Karakterin baktığı yöne doğru 1 birim ileri bomba kuran fonksiyon
    private void PlaceBomb()
    {
        if(currBomb != null && !multiBomb)
            return;

        //konumu hesapla ve boş mu kontrol et
        Vector2 bombPos = Vector2.Addition(position , dir);
        try
        {
            if (MapManager.Instance.getCurrentMap().getDataAtPosition(bombPos) != ID.empty.ordinal())
                return;
        }
        catch (Exception ignored) {
            return;
        }

        //Yeni bir bomba oluşturuyor
        int bombRadius = 2;
        currBomb = new Bomb(bombPos , bombRadius);

        //Bombayı map verisine ekliyor
        MapManager.Instance.getCurrentMap().setDataToPosition(bombPos , ID.bomb.ordinal());
    }
    //Karakteri istenilen konuma taşır
    private void Step(MapData mapData , Vector2 temp)
    {
        //Önceki pozisyonunu temizliyor
        mapData.setDataToPosition(position , playerOn.ordinal());

        //Yeni konumu ayarlıyor ve konumunu güncelliyor
        position = temp;
        try {
            playerOn = ID.fromInteger(mapData.getDataAtPosition(temp));
        } catch (Exception ignored) {}
        mapData.setDataToPosition(temp , ID.player.ordinal());
    }

    private Vector2 CalculateRunVelocity(MapData mapData , Vector2 playerVelocity)
    {
        Vector2 normal = Vector2.Addition(position , playerVelocity);
        Vector2 run = Vector2.Addition(normal , playerVelocity);

        try
        {
            if(mapData.getDataAtPosition(normal) == ID.empty.ordinal() && mapData.getDataAtPosition(run) == ID.empty.ordinal())
                return Vector2.Substraction(run , position);
        }
        catch (Exception ignored) {}

        return playerVelocity;
    }

    private Vector2 CalculateSkateboardVelocity(MapData mapData, Vector2 playerVelocity)
    {
        Vector2 tempPos = position;

        try
        {
            do
            {
                tempPos = Vector2.Addition(tempPos, playerVelocity);
            }
            while (mapData.getDataAtPosition(tempPos) != ID.wall.ordinal() || mapData.getDataAtPosition(tempPos) != ID.breakableWall.ordinal());
        }catch (Exception ignored){}

        tempPos = Vector2.Substraction(tempPos , playerVelocity);
        return Vector2.Substraction(tempPos , position);
    }

    private void Punch(MapData map)
    {
        if(currBomb == null)
            return;

        Vector2[] positions = new Vector2[3];

        positions[0] = Vector2.Addition(currBomb.currPos , dir);
        positions[1] = Vector2.Addition(positions[0] , dir);
        positions[2] = Vector2.Addition(positions[1] , dir);

        if(currBomb.currPos.Equals(Vector2.Addition(position , dir)))
        {
            if(map.isPositionValid(positions[2]))           currBomb.setPosition(map , positions[2]);
            else if(map.isPositionValid(positions[1]))      currBomb.setPosition(map , positions[1]);
            else if(map.isPositionValid(positions[0]))      currBomb.setPosition(map , positions[0]);
        }
    }

}
