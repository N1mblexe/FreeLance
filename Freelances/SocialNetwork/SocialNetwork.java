import java.util.*;

/**
 * Verilen SocialNetwork sınıfı bir sosyal ağı temsil etmektedir. Sınıfın içinde bir
 * kişinin ismini arkadaş listesine eşleyen bir Map türünde değişken bulunmaktadır.
 * Bu sınıfın sadece mostFriendCount ve recommendedFriends metotlarını değiştirin.
 * Diğer metot ve özellikler testlerin çalışması için gereklidir.
 */
public class SocialNetwork {
    // ************************ Lütfen bu aralıktaki kodları değiştirmeyin *************************
    // Her bir kişinin ismini arkadaş listesine eşleyen bir harita
    private Map<String, List<String>> adjacencyList;

    // Map nesnesi getter
    public Map<String, List<String>> getAdjacencyList() {
        return adjacencyList;
    }

    // Yapıcı
    public SocialNetwork() {
        adjacencyList = new HashMap<>();
    }

    // Sosyal ağa bir kişi ekler
    public void addPerson(String name) {
        if (!adjacencyList.containsKey(name)) {
            adjacencyList.put(name, new ArrayList<String>());
        }
    }

    // İki kişi arasında bir arkadaşlık ekler
    public void addFriendship(String person1, String person2) {
        addPerson(person1);
        addPerson(person2);
        if (!adjacencyList.get(person1).contains(person2)) {
            adjacencyList.get(person1).add(person2);
            adjacencyList.get(person2).add(person1);
        }
    }

    // Graftaki köşe(vertex) ve kenarların(edge) string temsilini döndürür
    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();

        builder.append("Vertices:\n");
        for (Map.Entry<String, List<String>> entry : adjacencyList.entrySet()) {
            String person = entry.getKey();
            builder.append(person + "\n");
        }

        builder.append("\nEdges:\n");
        for (Map.Entry<String, List<String>> entry : adjacencyList.entrySet()) {
            String person = entry.getKey();
            List<String> friends = entry.getValue();
            builder.append(person + ": [");
            for (int i = 0; i < friends.size(); i++) {
                String friend = friends.get(i);
                if (i == friends.size() - 1) {
                    builder.append(friend);
                } else {
                    builder.append(friend + ", ");
                }
            }
            builder.append("]\n");
        }

        return builder.toString();
    }

    // ************************ Lütfen bu aralıktaki kodları değiştirmeyin *************************

    public int mostFriendCount() {
        int maxFriendCount = 0;

        for (List<String> friends : adjacencyList.values())
        {
            int friendCount = friends.size();
            if (friendCount > maxFriendCount)
            {
                maxFriendCount = friendCount;
            }
        }

        return maxFriendCount;
    }


    public List<String> recommendedFriends(String person)
    {
        List<String> recommended = new ArrayList<>();

        List<String> personFriends = adjacencyList.getOrDefault(person, new ArrayList<>());

        Set<String> directFriendsSet = new HashSet<>(personFriends);

        Set<String> friendsOfFriendsSet = new HashSet<>();
        for (String friend : personFriends)
        {
            List<String> friendsOfFriend = adjacencyList.getOrDefault(friend, new ArrayList<>());
            friendsOfFriendsSet.addAll(friendsOfFriend);
        }

        for (String recommendedFriend : directFriendsSet)
        {
            if (!friendsOfFriendsSet.contains(recommendedFriend) && !recommendedFriend.equals(person))
            {
                recommended.add(recommendedFriend);
            }
        }

        return recommended;
    }
}