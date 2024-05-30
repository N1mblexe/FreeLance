package Behaviour;

import java.util.ArrayList;
import java.util.List;

//Bu sınıf Unity'nin Behaviour.MonoBehaviour sistemine benzer bir sistemi simüle eder
//Eklenen monobehaviour objelerinin kolay bir şekilde güncellenmesini sağlar
public class BehaviourManager
{
    private static List<MonoBehaviour> behaviours = new ArrayList<>();

    public static void AddNewBehaviour(MonoBehaviour behaviour)
    {
        behaviours.add(behaviour);
    }

    public static void DeleteBehaviour(MonoBehaviour behaviour)
    {
        behaviours.remove(behaviour);
    }
    public static void InitBehaviours()
    {
        for (MonoBehaviour mBehaviour: behaviours) { mBehaviour.Init(); }
    }
    public static void StartBehaviours()
    {
        for (MonoBehaviour mBehaviour: behaviours) { mBehaviour.Start(); }
    }
    public static void UpdateBehaviours()
    {
        for (MonoBehaviour mBehaviour: behaviours) {
            mBehaviour.Update(); }
    }

}
