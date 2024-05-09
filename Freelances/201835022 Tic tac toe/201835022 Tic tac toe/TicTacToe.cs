using TicTacToe_BaseApp;

namespace TicTacToe
{
    class TicTacToe : TicTacToe_base
    {
        private String currentPlayer;
        private String computerPlayer;

        public TicTacToe()
        {
            currentPlayer = "X";
            computerPlayer = "O";
        }

        protected override bool CheckWin(String user)
        {
            foreach (var winList in WinLists)
            {
                int count = 0;
                foreach (var pos in winList)
                {
                    if (board.ContainsKey(pos) && board[pos] == user)
                        count++;
                }
                if (count == 3)
                    return true;
            }
            return false;
        }

        private bool CheckDraw()
        {
            return board.Count == 9;
        }

        private bool GetUserInput(out int pos)
        {
            Console.Write($"Enter position for {currentPlayer}: ");
            if (int.TryParse(Console.ReadLine(), out pos))
            {
                if (!AddInputToBoard(pos, currentPlayer))
                {
                    Console.WriteLine("Invalid input!");
                    return false;
                }
            }
            else
            {
                Console.WriteLine("Invalid input!");
                return false;
            }
            return true;
        }

        public override void Run()
        {
            // game loop
            while (true)
            {
                DrawBoard();

                // check for win or draw
                if (CheckWin(currentPlayer))
                {
                    Console.WriteLine($"{currentPlayer} wins!");
                    break;
                }
                else if (CheckDraw())
                {
                    Console.WriteLine("Draw!");
                    break;
                }

                // get user input
                int pos;
                while (!GetUserInput(out pos)) { }

                // switch players
                currentPlayer = (currentPlayer == "X") ? "O" : "X";

                // get computer input
                pos = FindNextPosByAI();
                while (!AddInputToBoard(pos, computerPlayer))
                    pos = FindNextPosByAI();

                // switch players
                currentPlayer = (currentPlayer == "X") ? "O" : "X";
            }
            DrawBoard();
        }
    }
}
