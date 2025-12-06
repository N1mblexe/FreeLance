#include <cstdio>
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
        printf("Usage: %s [lines>0] [per_line>0] [output_path]\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(outpath, "w");
    if (!f)
    {
        perror("fopen");
        return 1;
    }

    srand((unsigned)time(0));
    for (int i = 0; i < lines; ++i)
    {
        for (int j = 0; j < per_line; ++j)
        {
            int val = rand() % 1000 + 1; // Random value between 1 and 1000
            fprintf(f, "%d%s", val, (j == per_line - 1) ? "\n" : " ");
        }
    }
    fclose(f);
    printf("Generated %d lines (%d values per line) into %s\n", lines, per_line, outpath);
    return 0;
}
