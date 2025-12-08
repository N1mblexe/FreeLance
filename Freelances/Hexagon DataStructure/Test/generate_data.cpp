#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

int main(int argc, char **argv)
{
    int lines = 50000; // default
    int per_line = 6;  // default
    const char *outpath = "../Data.txt";

    if (argc > 1)
        lines = atoi(argv[1]);
    if (argc > 2)
        per_line = atoi(argv[2]);
    if (argc > 3)
        outpath = argv[3];

    if (lines <= 0 || per_line <= 0)
    {
        std::cout << "Kullanım: " << argv[0] << " [satır>0] [satırbaşına>0] [çıkış_yolu]" << std::endl;
        return 1;
    }

    std::ofstream f(outpath);
    if (!f.is_open())
    {
        std::cout << "Hata: Dosya açılmadı -> " << outpath << std::endl;
        return 1;
    }

    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < lines; ++i)
    {
        for (int j = 0; j < per_line; ++j)
        {
            int val = rand() % 1000 + 1; // Random value between 1 and 1000
            f << val << (j == per_line - 1 ? '\n' : ' ');
        }
    }
    f.close();
    std::cout << "Oluşturuldu: " << lines << " satır (" << per_line << " değer/satır) -> " << outpath << std::endl;
    return 0;
}
