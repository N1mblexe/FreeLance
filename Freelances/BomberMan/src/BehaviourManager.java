import java.util.ArrayList;
import java.util.List;

//Bu sınıf Unity'nin MonoBehaviour sistemine benzer bir sistemi simüle eder
//Eklenen monobehaviour objelerinin kolay bir şekilde güncellenmesini sağlar
public class BehaviourManager
{
    //Monobehaviourları tutan bir liste
    private static List<MonoBehaviour> behaviours = new ArrayList<>();

    //Listeye yeni bir monobehaviour ekleyen fonksiyon
    public static void AddNewBehaviour(MonoBehaviour behaviour)
    {
        behaviours.add(behaviour);
    }

    //listemdeki behaviourların hepsinin Init fonksiyonunu foreach ile çağıran fonksiyon
    public static void InitBehaviours()
    {
        for (MonoBehaviour mBehaviour: behaviours) { mBehaviour.Init(); }
    }
    //listemdeki behaviourların hepsinin Start fonksiyonunu foreach ile çağıran fonksiyon
    public static void StartBehaviours()
    {
        for (MonoBehaviour mBehaviour: behaviours) { mBehaviour.Start(); }
    }
    //listemdeki behaviourların hepsinin Update fonksiyonunu foreach ile çağıran fonksiyon
    public static void UpdateBehaviours()
    {
        for (MonoBehaviour mBehaviour: behaviours) { mBehaviour.Update(); }
    }

}
