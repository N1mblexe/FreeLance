using System;

class Program
{
    static void Main()
    {
        string filePath = "daa.txt";
        StudentApp studentApp = new();
        try
        {
            studentApp = new(filePath);
        }
        catch (Exception)
        {
            Console.WriteLine("Initializing error from file!!");
        }

        while (true)
        {
            Console.WriteLine("\nStudent Management System");
            Console.WriteLine("1. Add Student");
            Console.WriteLine("2. Remove Student");
            Console.WriteLine("3. Update Student");
            Console.WriteLine("4. List Students");
            Console.WriteLine("5. Total Students");
            Console.WriteLine("6. Quit");

            Console.Write("Enter your choice (1-6): ");
            string choice = Console.ReadLine();

            switch (choice)
            {
                case "1":
                    AddStudent(studentApp);
                    break;

                case "2":
                    RemoveStudent(studentApp);
                    break;

                case "3":
                    UpdateStudent(studentApp);
                    break;

                case "4":
                    ListStudents(studentApp);
                    break;

                case "5":
                    ShowTotalStudents(studentApp);
                    break;

                case "6":
                    Console.WriteLine("Exiting the program. Goodbye!");
                    return;

                default:
                    Console.WriteLine("Invalid choice. Please enter a number between 1 and 6.");
                    break;
            }
        }
    }

    static void AddStudent(StudentApp studentApp)
    {
        try
        {
            Console.WriteLine("\nAdd Student");
            Console.Write("Enter student ID: ");
            int id = GetValidIntInput();

            Console.Write("Enter student name: ");
            string name = Console.ReadLine();

            Console.Write("Enter updated student class: ");
            int _class = GetValidIntInput();

            Student newStudent = new() { OgrenciNo = id, IsimSoyisim = name , Sinif = _class};
            studentApp.AddStudent(newStudent);

            Console.WriteLine("Student added successfully.");
        }
        catch (FormatException)
        {
            Console.WriteLine("Invalid input. Please enter a valid number.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }

    static void RemoveStudent(StudentApp studentApp)
    {
        try
        {
            Console.WriteLine("\nRemove Student");
            Console.Write("Enter student ID to remove: ");
            int idToRemove = GetValidIntInput();

            studentApp.RemoveStudent(idToRemove);

            Console.WriteLine("Student removed successfully.");
        }
        catch (FormatException)
        {
            Console.WriteLine("Invalid input. Please enter a valid number.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }

    static void UpdateStudent(StudentApp studentApp)
    {
        try
        {
            Console.WriteLine("\nUpdate Student");
            Console.Write("Enter student ID to update: ");
            int idToUpdate = GetValidIntInput();

            Console.Write("Enter updated student name: ");
            string updatedName = Console.ReadLine();

            Console.Write("Enter updated student class: ");
            int _class = GetValidIntInput();

            Student updatedStudent = new() { OgrenciNo = idToUpdate, IsimSoyisim = updatedName , Sinif = _class };
            studentApp.UpdateStudent(idToUpdate, updatedStudent);

            Console.WriteLine("Student updated successfully.");
        }
        catch (FormatException)
        {
            Console.WriteLine("Invalid input. Please enter a valid number.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Error: {ex.Message}");
        }
    }

    static void ListStudents(StudentApp studentApp)
    {
        Console.WriteLine("\nList of Students:");
        studentApp.ListStudents();
    }

    static void ShowTotalStudents(StudentApp studentApp)
    {
        int totalStudents = studentApp.TotalStudents();
        Console.WriteLine($"\nTotal Students: {totalStudents}");
    }

    static int GetValidIntInput()
    {
        while (true)
        {
            if (int.TryParse(Console.ReadLine(), out int result))
            {
                return result;
            }
            else
            {
                Console.WriteLine("Invalid input. Please enter a valid number.");
            }
        }
    }
}
