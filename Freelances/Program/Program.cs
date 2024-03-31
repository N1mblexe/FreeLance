namespace Caesar_Cipher
{
    class Program
    {
        public static char cipher(char ch, int key)
        {
            if (!char.IsLetter(ch))
            {

                return ch;
            }

            char d = char.IsUpper(ch) ? 'A' : 'a';
            return (char)((((ch + key) - d) % 26) + d);

        }
        public static string Encipher(string input, int key)
        {
            string output = string.Empty;

            foreach (char ch in input)
                output += cipher(ch, key);

            return output;
        }

        public static string Decipher(string input, int key)
        {
            return Encipher(input, 26 - key);
        }


        static void Main(string[] args)
        {

            Console.WriteLine("Şifrelenecek metni giriniz:");
            string UserString = Console.ReadLine();


            Console.Write("Anahtarı giriniz:");
            int key = Convert.ToInt32(Console.ReadLine());
            Console.WriteLine("\n");


            Console.WriteLine("Şifrelenmiş Data");

            string cipherText = Encipher(UserString, key);
            Console.WriteLine(cipherText);

            Console.WriteLine("Çözülmüş Data:");

            string t = Decipher(cipherText, key);
            Console.WriteLine(t);




            Console.ReadKey();

        }
    }
}