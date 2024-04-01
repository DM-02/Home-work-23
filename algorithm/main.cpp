//
//  main.cpp
//  algorithm
//
//  Created by Дмитрий Сергеевич on 13.03.2024.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct Employee {
    int id;
    std::string name;
    bool isDayShift;
    double salary;
};

void printEmployee(const Employee& emp) {
    std::cout << "ID: " << emp.id << ", Name: " << emp.name << ", Shift: " << (emp.isDayShift ? "Day" : "Night") << ", Salary: " << emp.salary << std::endl;
}

int main() {
    std::vector<Employee> employees;
    int N = 10; // Number of employees

    // Generate random data for N employees
    for (int i = 0; i < N; ++i) {
        Employee emp;
        emp.id = i + 1;
        emp.name = "Employee" + std::to_string(emp.id);
        emp.isDayShift = rand() % 2; // Randomly assign day or night shift
        emp.salary = rand() % 1000 + 1000; // Random salary between 1000 and 1999
        employees.push_back(emp);
    }

    // Print all employees
    for (const auto& emp : employees) {
        printEmployee(emp);
    }

    // Separate day and night shift employees
    std::vector<Employee> dayShiftEmployees, nightShiftEmployees;
    for (const auto& emp : employees) {
        if (emp.isDayShift) {
            dayShiftEmployees.push_back(emp);
        } else {
            nightShiftEmployees.push_back(emp);
        }
    }

    // Sort employees by salary
    std::sort(employees.begin(), employees.end(), [](const Employee& a, const Employee& b) {
        return a.salary > b.salary;
    });
    std::sort(dayShiftEmployees.begin(), dayShiftEmployees.end(), [](const Employee& a, const Employee& b) {
        return a.salary > b.salary;
    });
    std::sort(nightShiftEmployees.begin(), nightShiftEmployees.end(), [](const Employee& a, const Employee& b) {
        return a.salary > b.salary;
    });

    // Print top 3 highest paid employees
    std::cout << "\nTop 3 highest paid employees:\n";
    for (int i = 0; i < 3; ++i) {
        printEmployee(employees[i]);
    }

    // Save top 3 highest paid employees to file
    std::ofstream outFile("top_paid_employees.txt");
    for (int i = 0; i < 3; ++i) {
        outFile << "ID: " << employees[i].id << ", Name: " << employees[i].name << ", Shift: " << (employees[i].isDayShift ? "Day" : "Night") << ", Salary: " << employees[i].salary << std::endl;
    }
    outFile.close();

    // Print top 3 lowest paid employees
    std::cout << "\nTop 3 lowest paid employees:\n";
    for (int i = employees.size() - 1; i >= employees.size() - 3; --i) {
        printEmployee(employees[i]);
    }

    // Save top 3 lowest paid employees to file
    outFile.open("low_paid_employees.txt", std::ios::app);
    for (int i = employees.size() - 1; i >= employees.size() - 3; --i) {
        outFile << "ID: " << employees[i].id << ", Name: " << employees[i].name << ", Shift: " << (employees[i].isDayShift ? "Day" : "Night") << ", Salary: " << employees[i].salary << std::endl;
    }
    outFile.close();

    // Read data from file and keep only unique records
    std::ifstream inFile("low_paid_employees.txt");
    std::vector<Employee> uniqueEmployees;
    Employee tempEmp;
    while (inFile >> tempEmp.id >> tempEmp.name >> tempEmp.isDayShift >> tempEmp.salary) {
        if (std::find(uniqueEmployees.begin(), uniqueEmployees.end(), tempEmp) == uniqueEmployees.end()) {
            uniqueEmployees.push_back(tempEmp);
        }
    }
    inFile.close();

    // Print unique records
    std::cout << "\nUnique records:\n";
    for (const auto& emp : uniqueEmployees) {
        printEmployee(emp);
    }

    return 0;
}

