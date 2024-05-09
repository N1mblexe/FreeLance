using System;
using System.Collections.Generic;
using System.IO;
using System.Text.Json;

class Student
{
    public int OgrenciNo { get; set; }
    public string IsimSoyisim { get; set; }
    public int Sinif { get; set; }
    public List<string> Dersler { get; set; }
}

class StudentNotFoundException : Exception
{
    public StudentNotFoundException(string message) : base(message) { }
}

class StudentApp
{
    private const int MaxStudents = 50; 
    private readonly Student[] students;
    private int studentCount;

    public StudentApp(string filePath)
    {
        studentCount = 0;
        students = new Student[MaxStudents];

        if (File.Exists(filePath))
        {
            Initialize(filePath);
        }
        else
        {
            throw new FileNotFoundException($"File not found: {filePath}");
        }
    }
    public StudentApp()
    {
        studentCount = 0;
        students = new Student[MaxStudents];
    }

    private void Initialize(string filePath)
    {
        try
        {
            string jsonText = File.ReadAllText(filePath);
            Student[] temp = JsonSerializer.Deserialize<Student[]>(jsonText);

            foreach (Student s in temp)
                AddStudent(s);
        }
        catch (JsonException ex)
        {
            throw new JsonException($"Error deserializing JSON data: {ex.Message}", ex);
        }
        catch (Exception ex)
        {
            throw new Exception($"An error occurred during initialization: {ex.Message}", ex);
        }
    }


    public void AddStudent(Student student)
    {
        if (studentCount < MaxStudents)
        {
            students[studentCount++] = student;
        }
        else
        {
            throw new InvalidOperationException("Student app is full, cannot add more students.");
        }
    }

    public void RemoveStudent(int studentId)
    {
        int indexToRemove = -1;

        for (int i = 0; i < studentCount; i++)
        {
            if (students[i].OgrenciNo == studentId)
            {
                indexToRemove = i;
                break;
            }
        }

        if (indexToRemove != -1)
        {
            for (int i = indexToRemove; i < studentCount - 1; i++)
            {
                students[i] = students[i + 1];
            }
            studentCount--;
        }
        else
        {
            throw new StudentNotFoundException($"Student with ID {studentId} not found.");
        }
    }

    public void UpdateStudent(int studentId, Student updatedStudent)
    {
        for (int i = 0; i < studentCount; i++)
        {
            if (students[i].OgrenciNo == studentId)
            {
                students[i] = updatedStudent;
                return;
            }
        }

        throw new StudentNotFoundException($"Student with ID {studentId} not found.");
    }

    public void ListStudents()
    {
        for (int i = 0; i < studentCount; i++)
        {
            Console.WriteLine($"ID: {students[i].OgrenciNo}, Name Surname: {students[i].IsimSoyisim}, Class: {students[i].Sinif}");
        }
    }

    public int TotalStudents()
    {
        return studentCount;
    }
}
