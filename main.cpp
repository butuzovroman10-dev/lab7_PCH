#include "MyContainer.h"
#include "Developer.h"
#include "Manager.h"
#include "Tester.h"
#include <iostream>
#include <algorithm>
#include <string>

bool compareBySalary(Employee* a, Employee* b) {
    return a->getSalary() < b->getSalary();
}

bool compareById(Employee* a, Employee* b) {
    return a->getId() < b->getId();
}

void printAllEmployees(const MyContainer<Employee*>& container) {
    std::cout << "\n=== All Employees (sorted by ID automatically) ===" << std::endl;
    for (auto it = container.begin(); it != container.end(); ++it) {
        (*it)->displayInfo();
        std::cout << std::endl;
    }
}

void findAndDisplayEmployee(MyContainer<Employee*>& container, int id) {
    auto it = std::find_if(container.begin(), container.end(), 
        [id](Employee* emp) { return emp->getId() == id; });
    
    if (it != container.end()) {
        std::cout << "\nFound employee with ID " << id << ": ";
        (*it)->displayInfo();
        std::cout << std::endl;
    } else {
        std::cout << "\nEmployee with ID " << id << " not found" << std::endl;
    }
}

void demonstrateHighEfficiencyEmployees(const MyContainer<Employee*>& container) {
    std::cout << "\n=== High Efficiency Employees (Efficiency > 0.85) ===" << std::endl;
    
    for (auto it = container.begin(); it != container.end(); ++it) {
        double efficiency = (*it)->getEfficiency();
        if (efficiency > 0.85) {
            (*it)->displayInfo();
            std::cout << " - Efficiency: " << (efficiency * 100) << "%" << std::endl;
        }
    }
}

void demonstrateRemoveOperation(MyContainer<Employee*>& container, int id) {
    auto it = std::find_if(container.begin(), container.end(), 
        [id](Employee* emp) { return emp->getId() == id; });
    
    if (it != container.end()) {
        Employee* emp = *it;
        container.remove(emp);
        std::cout << "\nRemoved employee with ID " << id << std::endl;
        delete emp;
    }
}

int main() {
    MyContainer<Employee*> company;
    
    Developer* dev1 = new Developer("Alice", 105, 75000, "C++", 450);
    Developer* dev2 = new Developer("Diana", 101, 80000, "Python", 600);
    Manager* mgr1 = new Manager("Bob", 104, 90000, 8, 5);
    Manager* mgr2 = new Manager("Eve", 102, 95000, 12, 7);
    Tester* tst1 = new Tester("Charlie", 106, 65000, 25, "Selenium");
    Tester* tst2 = new Tester("Frank", 103, 70000, 30, "Cypress");
    
    std::cout << "=== Adding employees (auto-sorted by ID) ===" << std::endl;
    company.push_back(dev1);
    company.push_back(dev2);
    company.push_back(mgr1);
    company.push_back(mgr2);
    company.push_back(tst1);
    company.push_back(tst2);
    
    std::cout << "Container size: " << company.size() << std::endl;
    
    printAllEmployees(company);
    
    findAndDisplayEmployee(company, 103);
    findAndDisplayEmployee(company, 999);
    
    demonstrateHighEfficiencyEmployees(company);
    
    std::cout << "\n=== Range-based for loop demo ===" << std::endl;
    for (const auto& emp : company) {
        emp->work();
    }
    
    demonstrateRemoveOperation(company, 104);
    
    std::cout << "\n=== After removal ===" << std::endl;
    printAllEmployees(company);
    
    std::cout << "\n=== Testing push_front (same as push_back for sorted container) ===" << std::endl;
    Tester* tst3 = new Tester("Grace", 100, 72000, 28, "Playwright");
    company.push_front(tst3);
    printAllEmployees(company);
    
    std::cout << "\n=== Front element: ";
    company.front()->displayInfo();
    std::cout << std::endl;
    
    std::cout << "\n=== Back element: ";
    company.back()->displayInfo();
    std::cout << std::endl;
    
    std::cout << "\n=== Clearing container ===" << std::endl;
    company.clear();
    std::cout << "Container size after clear: " << company.size() << std::endl;
    
    delete dev1;
    delete dev2;
    delete mgr1;
    delete mgr2;
    delete tst1;
    delete tst2;
    delete tst3;
    
    return 0;
}