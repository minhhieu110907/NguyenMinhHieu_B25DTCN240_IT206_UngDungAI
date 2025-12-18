#include <stdio.h>
#include <string.h>

// Định nghĩa struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

// Hàm in danh sách sinh viên dưới dạng bảng
void printStudents(struct Student students[], int count) {
    printf("\n");
    printf("+------+----------------------+------+------+\n");
    printf("|  ID  |        Name          | Age  | GPA  |\n");
    printf("+------+----------------------+------+------+\n");
    
    for (int i = 0; i < count; i++) {
        printf("| %-4d | %-20s | %-4d | %-4.2f |\n", 
               students[i].id, 
               students[i].name, 
               students[i].age, 
               students[i].gpa);
    }
    
    printf("+------+----------------------+------+------+\n");
}

int main() {
    // Khởi tạo mảng 3 sinh viên mẫu
    struct Student students[3] = {
        {1, "Nguyen Van An", 20, 3.75},
        {2, "Tran Thi Binh", 21, 3.85},
        {3, "Le Van Cuong", 19, 3.65}
    };
    
    // In danh sách sinh viên
    printf("DANH SACH SINH VIEN\n");
    printStudents(students, 3);
    
    return 0;
}

