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

// Hàm lưu danh sách sinh viên vào file students.txt
int saveToFile(struct Student students[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("Khong the mo file %s de ghi!\n", filename);
        return 0;
    }
    
    // Ghi header vào file
    fprintf(file, "+------+----------------------+------+------+\n");
    fprintf(file, "|  ID  |        Name          | Age  | GPA  |\n");
    fprintf(file, "+------+----------------------+------+------+\n");
    
    // Ghi thông tin từng sinh viên
    for (int i = 0; i < count; i++) {
        fprintf(file, "| %-4d | %-20s | %-4d | %-4.2f |\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].gpa);
    }
    
    fprintf(file, "+------+----------------------+------+------+\n");
    
    fclose(file);
    return 1;
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
    
    // Lưu danh sách vào file
    printf("\nDang luu danh sach sinh vien vao file students.txt...\n");
    if (saveToFile(students, 3, "students.txt")) {
        printf("Da luu thanh cong danh sach sinh vien vao file students.txt!\n");
    } else {
        printf("Loi khi luu file!\n");
        return 1;
    }
    
    return 0;
}

