package Map;

//Bu enum sınıfı haritadaki sayıların hangi birimi ifade ettiğini gösterir
//Mesela haritada bulunan 1 karakteri temsil eder ve ona göre gösterilir
public enum ID {
    empty, //0
    player, //1
    wall, //2
    exit, //3
    spawnPos, //4
    bomb,//5
    breakableWall,//6
    runPower,//7
    skateBoardPower,//8
    punchPower,//9
    multiBombPower,//10
    shieldPower,//11
    horizontalEnemy, //12
    verticalEnemy; //13


    public static ID fromInteger(int x) {
        return switch (x) {
            case 0 -> empty;
            case 1 -> player;
            case 2 -> wall;
            case 3 -> exit;
            case 4 -> spawnPos;
            case 5 -> bomb;
            case 6 -> breakableWall;
            case 7 -> runPower;
            case 8 -> skateBoardPower;
            case 9 -> punchPower;
            case 10 -> multiBombPower;
            case 11 -> shieldPower;
            case 12 -> horizontalEnemy;
            case 13 -> verticalEnemy;
            default -> null;
        };
    }
}
