package Behaviour;

import Behaviour.BehaviourManager;

//Bu sınıf Unity'nin Behaviour.MonoBehaviour sınıfı örnek alarak tasarlanmıştır
public class MonoBehaviour
{
    //Yapıcı metot ile oluşturulan yeni sınıfımız listeye eklenir bu sayede oluşturulan tüm objelere kolaylıkla erişebiliriz
    public MonoBehaviour()
    {
        BehaviourManager.AddNewBehaviour(this);
    }
    //Init fonksiyonu program ilk çalıştığında 1 kez çalışır
    public void Init() {}

    //Start fonksiyonu her yeni bir map'e girildiğinde 1 kez çalışır
    public void Start() {}

    //Update fonksiyonu oyun oynanırken her bir adımda 1 kere çağırılır
    public void Update() {}
}
