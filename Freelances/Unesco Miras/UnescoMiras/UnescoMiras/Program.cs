using System;
using System.Collections.Generic;
using UnescoMiras;

internal class Program
{
    static void Main(string[] args)
    {
        UM.StackX<UM_Alani> stack = new UM.StackX<UM_Alani>();
        UM.QueueX<UM_Alani> queue = new UM.QueueX<UM_Alani>();

        stack = UM_Alani.ReadDataFromFile("data.txt");
        queue = UM_Alani.ReadDataFromFileQueue("data.txt");

        Console.WriteLine("STACK (YIĞIT):");
        PrintDatas(stack);
        Console.WriteLine("########################################################");

        Console.WriteLine("QUEUE (YIĞIN):");
        PrintDatas(queue);
        Console.WriteLine("########################################################");
    
    }

    static void PrintDatas(UM.StackX<UM_Alani> stacks)
    {
        try
        {
            while (stacks.Peek() != null)
            {
                stacks.Pop()?.Print();
            }
        }
        catch (InvalidOperationException ignored) { }
    }

    static void PrintDatas(UM.QueueX<UM_Alani> queues)
    {
        try
        {
            while (queues.Peek() != null)
            {
                queues.Dequeue()?.Print();
            }
        }
        catch (InvalidOperationException ignored) { }
    }





}
