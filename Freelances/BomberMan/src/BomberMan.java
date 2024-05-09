import java.util.Scanner;

//Bu sınıf oyunun oynanmasını sağlayan asıl sınıf (oyunu oynamak için bu sınıftan bir obje oluşturun ve run() fonksiyonunu çağırın)
public class BomberMan
{
    private int maxStep = 50;
    public static BomberMan Instance;

    //Oyuncuyu ve map bilgilerini tut
    private static Player player;
    private static MapManager mapManager;

    //Constructor ile yeni bir MapManager oluştur ve dosyaların adlarını map manager'a yolla
    public BomberMan()
    {
        mapManager = new MapManager(new String[]{"Map1.txt" , "Map2.txt"});
    }

    private boolean gameState = true;
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
        gameState = false;
        loseMessage = message;
    }
    private void Start()
    {
        try {
            //Player bilgilerini güncelle (konum ve spawn pozisyonu) ve spawn et
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
        //MonoBehaviour objelerini başlatır
        Start();
        try {
            //Karakter hedefe ulaşana kadar bir döngü oluştur ve move fonksiyonunu çağır
            do {
                //Oyunu ekrana gösterir ve gerekli Update fonksiyonlarını çağırır
                DisplayGame();
                BehaviourManager.UpdateBehaviours();
            }
            while (!player.Move(MapManager.Instance.getCurrentMap()) && gameState);
        }catch (Exception ignored){}

        if(gameState)
        {
            if(mapManager.NextMap())
            {
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
        int input;

        //Ana menüyü gösterir ve bir input bekler
        DisplayMainMenu();
        input = sc.nextInt();

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
    //Mapleri listele
    private void DisplayPlayMenu()
    {
        System.out.println("Choose Map\n");

        mapManager.ListMaps();
        System.out.println("Enter map name: ");

    }
    //Mapi göster
    private void DisplayGame()
    {
        System.out.println(mapManager.getCurrentMap().getVisualizedData());
        System.out.println("Steps left: " + player.maxStep);
    }

    //Nasıl oynanacağına dair bilgi veren menü
    private void DisplayHowToPlay() {
        System.out.println("How to play:");

        System.out.println("Controls:");
        System.out.println("\t-w, a, s, d: Movement");
        System.out.println("\t-e: Place a bomb in the direction you are facing");

        System.out.println("\nUnits:");
        System.out.println("\tO: Player");
        System.out.println("\t□□□: Unbreakable walls");
        System.out.println("\t#: Breakable walls");
        System.out.println("\t!: Bomb");
        System.out.println("\tX: Objective (reach this point)");

        System.out.println("\nAbout the Game:");
        System.out.println("You can place bombs to destroy breakable walls.");
        System.out.println("Bombs explode after 4 steps when placed.");
        System.out.println("Bombs also damage the player (you only have 1 life).");
        System.out.println("Bomb radius = 2");
    }

}
