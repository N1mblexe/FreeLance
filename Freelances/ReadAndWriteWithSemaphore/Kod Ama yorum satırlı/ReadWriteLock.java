/**
 * Bu Java sınıfı, basit bir okuma-yazma kilidi (read-write lock) uygulayan bir sınıfı temsil eder.
 * Kod, iki tür işlemi destekler: okuma kilidi (read lock) ve yazma kilidi (write lock).
 * Senkronizasyon için `Semaphore` sınıfını kullanır.
 *
 * - `Semaphore S`: Genel senkronizasyonu sağlamak ve okuma işlemleri arasında bir kilit oluşturmak için kullanılır.
 * - `Semaphore wrt`: Yazma işlemlerini kontrol etmek ve bir yazma işlemi gerçekleştiğinde diğer işlemleri engellemek için kullanılır.
 * - `readCount`: Mevcut okuma işlemlerinin sayısını takip etmek için kullanılır.
 *
 * Metodlar:
 * - `readLock()`: Okuma işlemi başlamadan önce çağrılan bu metot, diğer okuma işlemlerini engeller ve eğer bu ilk okuma işlemi ise yazma işlemlerini engeller.
 * - `writeLock()`: Yazma işlemi başlamadan önce çağrılan bu metot, diğer tüm okuma ve yazma işlemlerini engeller.
 * - `readUnlock()`: Bir okuma işlemi tamamlandığında çağrılan bu metot, diğer okuma işlemlerini serbest bırakır ve eğer tüm okuma işlemleri tamamlanmışsa yazma işlemlerini serbest bırakır.
 * - `writeUnlock()`: Bir yazma işlemi tamamlandığında çağrılan bu metot, diğer yazma işlemlerini serbest bırakır.
 */
/**
 * This Java class represents a simple implementation of a read-write lock.
 * The code supports two types of operations: read lock and write lock.
 * It uses the `Semaphore` class for synchronization.
 *
 * - `Semaphore S`: Used for general synchronization and acts as a lock among read operations.
 * - `Semaphore wrt`: Used to control write operations, preventing other read and write operations when a write operation occurs.
 * - `readCount`: Keeps track of the current number of ongoing read operations.
 *
 * Methods:
 * - `readLock()`: Called before starting a read operation, it prevents other read operations and, if it is the first read operation, blocks write operations.
 * - `writeLock()`: Called before starting a write operation, it blocks all other read and write operations.
 * - `readUnlock()`: Called when a read operation is completed, it releases other read operations and, if all read operations are completed, releases write operations.
 * - `writeUnlock()`: Called when a write operation is completed, it releases other write operations.
 */
import java.util.concurrent.Semaphore;

public class ReadWriteLock {
    /** Genel senkronizasyonu sağlamak ve okuma işlemleri arasında bir kilit oluşturmak için kullanılır. */
    /** Used for general synchronization and acts as a lock among read operations. */
    private final Semaphore S = new Semaphore(1);

    /** Yazma işlemlerini kontrol etmek ve bir yazma işlemi gerçekleştiğinde diğer işlemleri engellemek için kullanılır. */
    /** Used to control write operations, preventing other read and write operations when a write operation occurs. */
    private final Semaphore wrt = new Semaphore(1);

    /** Mevcut okuma işlemlerinin sayısını takip etmek için kullanılır. */
    /** Keeps track of the current number of ongoing read operations. */
    private int readCount = 0;

    /**
     * Okuma işlemi başlamadan önce çağrılan bu metot, diğer okuma işlemlerini engeller ve
     * eğer bu ilk okuma işlemi ise yazma işlemlerini engeller.
     */
    /**
     * Called before starting a read operation, it prevents other read operations and,
     * if it is the first read operation, blocks write operations.
     */
    public void readLock() {
        try {
            S.acquire();
            readCount++;
            if (readCount == 1)
                wrt.acquire();

            S.release();
        } catch (InterruptedException ignored) {
        }
    }

    /**
     * Yazma işlemi başlamadan önce çağrılan bu metot, diğer tüm okuma ve yazma işlemlerini engeller.
     */
    /**
     * Called before starting a write operation, it blocks all other read and write operations.
     */
    public void writeLock() {
        try {
            S.acquire();
            wrt.acquire();
            S.release();
        } catch (InterruptedException ignored) {
        }
    }

    /**
     * Bir okuma işlemi tamamlandığında çağrılan bu metot, diğer okuma işlemlerini serbest bırakır
     * ve eğer tüm okuma işlemleri tamamlanmışsa yazma işlemlerini serbest bırakır.
     */
    /**
     * Called when a read operation is completed, it releases other read operations and,
     * if all read operations are completed, releases write operations.
     */
    public void readUnlock() {
        try {
            S.acquire();
            readCount--;
            if (readCount == 0)
                wrt.release();

            S.release();
        } catch (InterruptedException ignored) {
        }
    }

    /** Bir yazma işlemi tamamlandığında çağrılan bu metot, diğer yazma işlemlerini serbest bırakır. */
    /** Called when a write operation is completed, it releases other write operations. */
    public void writeUnlock() {
        wrt.release();
    }
}
