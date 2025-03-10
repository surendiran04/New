CREATE DATABASE university;
USE university;

CREATE TABLE Student (
    ID INT PRIMARY KEY,
    Name VARCHAR(100),
    Department VARCHAR(100),
    CGPA FLOAT
);
import java.sql.*;

public class StudentDatabase {
    private static final String URL = "jdbc:mysql://localhost:3306/university";
    private static final String USER = "root";  // Change to your MySQL username
    private static final String PASSWORD = "";  // Change to your MySQL password

    public static void main(String[] args) {
        createStudent(101, "Alice Johnson", "Computer Science", 3.8);
        getStudentByID(101);
    }

    // Insert a new student record
    public static void createStudent(int id, String name, String department, double cgpa) {
        String sql = "INSERT INTO Student (ID, Name, Department, CGPA) VALUES (?, ?, ?, ?)";

        try (Connection conn = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, id);
            stmt.setString(2, name);
            stmt.setString(3, department);
            stmt.setDouble(4, cgpa);

            int rowsInserted = stmt.executeUpdate();
            if (rowsInserted > 0) {
                System.out.println("Student record inserted successfully.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // Retrieve a student record by ID
    public static void getStudentByID(int id) {
        String sql = "SELECT * FROM Student WHERE ID = ?";

        try (Connection conn = DriverManager.getConnection(URL, USER, PASSWORD);
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setInt(1, id);
            ResultSet resultSet = stmt.executeQuery();

            if (resultSet.next()) {
                System.out.println("Student ID: " + resultSet.getInt("ID"));
                System.out.println("Name: " + resultSet.getString("Name"));
                System.out.println("Department: " + resultSet.getString("Department"));
                System.out.println("CGPA: " + resultSet.getFloat("CGPA"));
            } else {
                System.out.println("Student not found.");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
