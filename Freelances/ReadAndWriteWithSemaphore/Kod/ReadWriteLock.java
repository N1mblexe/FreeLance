import java.util.concurrent.Semaphore;

public class ReadWriteLock {
    private final Semaphore S = new Semaphore(1);

    private final Semaphore wrt = new Semaphore(1);

    private int readCount = 0;

    public void readLock()
    {
        try
        {
            S.acquire();
            readCount++;
            if (readCount == 1)
                wrt.acquire();

            S.release();
        }
        catch (InterruptedException ignored) {}
    }

    public void writeLock()
    {
        try
        {
            S.acquire();
            wrt.acquire();
            S.release();
        }
        catch (InterruptedException ignored) {}
    }
    public void readUnlock()
    {
        try
        {
            S.acquire();
            readCount--;
            if (readCount == 0)
                wrt.release();

            S.release();
        }
        catch (InterruptedException ignored) {}
    }

    public void writeUnlock() {
        wrt.release();
    }
}
