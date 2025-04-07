namespace TicTacToe_BaseApp
{
    internal abstract class TicTacToe_base
    {
        protected SortedList<int, String> board; // keeps all user's selections
        protected List<int[]> WinLists; // winner position lists
        public TicTacToe_base()
        {
            board = new SortedList<int, string>();
            WinLists = new List<int[]>();
            // rows
            WinLists.Add(new int[] { 1, 2, 3 });
            WinLists.Add(new int[] { 4, 5, 6 });
            WinLists.Add(new int[] { 7, 8, 9 });
            // columns
            WinLists.Add(new int[] { 1, 4, 7 });
            WinLists.Add(new int[] { 2, 5, 8 });
            WinLists.Add(new int[] { 3, 6, 9 });
            // diagonals
            WinLists.Add(new int[] { 1, 5, 9 });
            WinLists.Add(new int[] { 3, 5, 7 });
        }

        // Stores user entries in the board list after checking for accuracy.
        // Returns true if the input is accepted, false otherwise.
        protected bool AddInputToBoard(int pos, String user)
        {
            // check for valid positions
            if (pos < 1 || pos > 9)
                return false;
            // check for valid user
            if (!(user.Equals("X") || user.Equals("O")))
                return false;
            // check used positions
            if (board.ContainsKey(pos))
                return false;
            // add this
            board.Add(pos, user.ToUpper());
            return true;
        }
        protected void DrawBoard()
        {
            string? user;
            Console.Clear();
            Console.WriteLine("Tic-Tac-Toe Game board.");
            Console.WriteLine("User marked with X, Computer marked with O " +
            "and empty positons marked by numbers.");
            for (int pos = 1; pos < 10; pos++)
            {
                user = pos.ToString();
                if (board.ContainsKey(pos))
                    _ = board.TryGetValue(pos, out user);
                Console.Write(user);
                if (pos % 3 != 0)
                    Console.Write(" | ");
                else if ((pos % 3 == 0) && (pos < 9))
                    Console.WriteLine("\n--+---+--");
                else
                    Console.WriteLine();
            }
        }
        /// <summary>
        /// Computer game position selection is made randomly.
        /// </summary>
        /// <returns>returns an integer in rane of 1 to 9.</returns>
        protected int FindNextPosByAI()
        {
            Random rn = new Random();
            return rn.Next(1, 10);
        }
        protected abstract bool CheckWin(String user);
        public abstract void Run();
    }
}