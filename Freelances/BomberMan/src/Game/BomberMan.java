package Game;

import Behaviour.BehaviourManager;
import Enemies.EnemyManager;
import Map.MapData;
import Map.MapManager;
import PlayerPackage.Player;

import java.util.List;
import java.util.Scanner;

//Bu sınıf oyunun oynanmasını sağlayan asıl sınıf (oyunu oynamak için bu sınıftan bir obje oluşturun ve run() fonksiyonunu çağırın)
public class BomberMan
{
    private int maxStep = 200;
    public static BomberMan Instance;

    //Oyuncuyu ve map bilgilerini tut
    private static Player player;

    private static FileManager fileManager;
    private static MapManager mapManager;
    private static EnemyManager enemyManager;
    private static InputManager inputManager;

    //Constructor ile yeni bir Map.MapManager oluştur ve dosyaların adlarını map manager'a yolla
    public BomberMan()
    {
        mapManager = new MapManager(new String[]{"Files/Map1.txt" , "Files/Map2.txt"});
        enemyManager = new EnemyManager();
        fileManager = new FileManager("Files/settingsCFG.txt" , "Files/displayCFG.txt");
        inputManager = new InputManager();
    }

    private boolean gameState = true;
    private boolean nextMap = false;
    private String loseMessage;

    //Monobehaviour olan tüm objelerin başlatma (Init) fonksiyonunu çağır
    private void Init()
    {
        if(Instance == null)
            Instance = this;
        BehaviourManager.InitBehaviours();
    }

    public void LoseGame(String message)
    {
        if(player.getShield())
            return;

        gameState = false;
        loseMessage = message;
    }

    public void NextMap()
    {
        nextMap = true;
    }
    private void Start()
    {
        try {
            //Player.Player bilgilerini güncelle (konum ve spawn pozisyonu) ve spawn et
            player = new Player(maxStep);
            player.SpawnPlayer(MapManager.Instance.getCurrentMap());
        } catch (Exception ignored){}

        //Monobehaviour olan tüm objelerin başlatma (start) fonksiyonunu çağır
        BehaviourManager.StartBehaviours();
    }

    //Bu fonksiyon programı başlatır ve ana menüyü çağırır
    public void run()
    {
        Init();
        while (MainMenu());
    }

    //Bu fonksiyon seçili mapi oynatmak için başlatır
    private void RunMap()
    {
        //Behaviour.MonoBehaviour objelerini başlatır
        Start();
        try {
            enemyManager.InitEnemies();

            //Karakter hedefe ulaşana kadar bir döngü oluştur ve move fonksiyonunu çağır
            do {
                //Oyunu ekrana gösterir ve gerekli Update fonksiyonlarını çağırır
                DisplayGame();
                player.HandleInput(MapManager.Instance.getCurrentMap());
                BehaviourManager.UpdateBehaviours();

            }
            while (gameState && !nextMap);
        }catch (Exception ignored){}

        if(gameState)
        {
            if(mapManager.NextMap())
            {
                enemyManager.ClearEnemyCache();
                nextMap = false;
                RunMap();
            }
            else
            {
                System.out.println("You Won");
            }
        }
        else
        {
            System.out.println(loseMessage);
            gameState = true;
        }

        //Mapi bitirince mapi ilk haline geri getir
        MapManager.Instance.Init();
    }

    //Bu fonksiyon ana menüyü çalıştırır
    private boolean MainMenu()
    {
        Scanner sc = new Scanner(System.in);
        int input = -1;

        //Ana menüyü gösterir ve bir input bekler
        DisplayMainMenu();
        try {
            input = sc.nextInt();
        }
        catch (Exception ignored){}
        //Verilen inputa göre gerekli menüye yönlendirir
        switch (input)
        {
            case 1:
                PlayMenu();
                break;
            case 2:
                DisplayHowToPlay();
                break;
            case 3:
                return false;
        }
        return true;
    }

    //Main menüyü ekrana yazdırır
    private void DisplayMainMenu()
    {
        System.out.println("MAIN MENU");

        System.out.println("\n1-Play");
        System.out.println("2-How To Play");
        System.out.println("3-Exit");

        System.out.print("input:");
    }

    //Mapleri seçmesi için listeler
    private void PlayMenu()
    {
        RunMap();
    }

    //private void DisplayPlayMenu()
    //{
    //    System.out.println("Choose Map\n");

    //    mapManager.ListMaps();
    //    System.out.println("Enter map name: ");

    //}
    //Mapi göster
    private void DisplayGame()
    {
        System.out.println(mapManager.getCurrentMap().getVisualizedData());
        System.out.println("Steps left: " + player.StepsLeft());
        System.out.println("Active ability: " + player.getAbility());
        System.out.println("Looking direction: " + player.getDirection());
    }

    //Nasıl oynanacağına dair bilgi veren menü
    private void DisplayHowToPlay() {
        System.out.println("How to play:");

        try {
            InputManager.InputSettings inputSettings = FileManager.instance.GetInputSettings();
            MapData.DisplaySettings displaySettings = FileManager.instance.GetDisplaySettings();

            List<String> chars = displaySettings.getDisplayChars();

        System.out.println("Controls:");
        System.out.println("\t- " + inputSettings.moveKeys[2] +  " , " + inputSettings.moveKeys[0] +" , " + inputSettings.moveKeys[3] + " , " +  inputSettings.moveKeys[1] + ": Movement");
        System.out.println("\t- " + inputSettings.bombPlaceKey +  " : Place a bomb in the direction you are facing");
        System.out.println("\t- " + inputSettings.abilityKey + " : Use ability (if available)");

        System.out.println("\nUnits:");


        System.out.println("\t " + chars.get(1)     + ": Player");
        System.out.println("\t " + chars.get(2)     + ": Unbreakable walls");
        System.out.println("\t " + chars.get(3)     + ": Objective");
        System.out.println("\t " + chars.get(5)     + ": Bomb");
        System.out.println("\t " + chars.get(6)     + ": Breakable Walls");
        System.out.println("\t " + chars.get(7)     + ": Run ability");
        System.out.println("\t " + chars.get(8)     + ": Skateboard Ability");
        System.out.println("\t " + chars.get(9)     + ": Punch Ability");
        System.out.println("\t " + chars.get(10)    + ": Multi bomb ability");
        System.out.println("\t " + chars.get(11)    + ": Shield Ability (Lasts 15 round)");
        System.out.println("\t " + chars.get(12)    + ": Horizontal Enemy");
        System.out.println("\t " + chars.get(13)    + ": Vertical Enemy");


        System.out.println("\nAbout the Game:");
        System.out.println("You can place bombs to destroy breakable walls.");
        System.out.println("Bombs explode after 4 steps when placed.");
        System.out.println("Bombs also damage the player (you only have 1 life).");
        System.out.println("Bomb radius = 2");

        } catch (Exception e) {}
    }

}
