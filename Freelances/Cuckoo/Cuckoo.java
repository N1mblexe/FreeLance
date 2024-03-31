import java.util.List;

public class Cuckoo extends AbstractCuckoo
{
    private final int tableSize;

    public Cuckoo(int maxAttemps, HashTable t1, HashTable t2) {
        super(maxAttemps, t1, t2);
        this.tableSize = t1.getTableAsList().size();
    }

    @Override
    public boolean insert(int key) {
        return insertKey(key , 0);
    }

    private boolean insertKey(int key, int attempts) {
        if (attempts >= MAX_REHASH_ATTEMPTS || (table1.getProbeCount() > MAX_REHASH_ATTEMPTS && table2.getProbeCount() > MAX_REHASH_ATTEMPTS))  return false;


        Integer[] keys = new Integer[2];

        int index1 = table1.hash(key);
        keys[0] = table1.get(index1);
        if (keys[0] == null) {
            table1.set(index1, key);
            return true;
        }

        attempts++;
        int temp = keys[0];
        table1.set(index1, key);

        if (attempts >= MAX_REHASH_ATTEMPTS || (table1.getProbeCount() > MAX_REHASH_ATTEMPTS && table2.getProbeCount() > MAX_REHASH_ATTEMPTS))  return false;

        int index2 = table2.hash(temp);
        keys[1] = table2.get(index2);
        if (keys[1] == null)
        {
            table2.set(index2, temp);
            return true;
        }
        else
        {
            table2.set(index2, temp);
            return insertKey(keys[1], attempts + 1);
        }
    }

    @Override
    public boolean search(int key)
    {
        int hV1 = table1.hash(key);
        int index1 = hV1 % tableSize;

        int hV2 = table2.hash(key);
        int index2 = hV2 % tableSize;

        Integer value1 = table1.get(index1);
        Integer value2 = table2.get(index2);

        return (value1 != null && value1.intValue() == key) ||
                (value2 != null && value2.intValue() == key);
    }
}
