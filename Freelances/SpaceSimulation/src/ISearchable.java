/**
 *
 * @author Yazar adı ve mail
 * @since 2025-04-07
 * <p>
 * Nesne listelerinde isim bazlı arama yapılmasını sağlayan ISearchable arayüzü.
 * </p>
 */


import java.util.List;

public interface ISearchable
{
    static <T extends ISearchable> T SearchInList(List<T> list, String name)
    {
        for (T t : list)
            if (t.getName().equals(name))
                return t;

        return null;
    }

    String getName();
}
