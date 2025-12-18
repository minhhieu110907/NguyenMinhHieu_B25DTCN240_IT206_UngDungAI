#include <stdio.h>
#include <string.h>

// Định nghĩa struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

// Hàm nhập thông tin một sinh viên
void inputStudent(struct Student *student) {
    printf("Nhap ID: ");
    scanf("%d", &student->id);
    getchar(); // Xóa ký tự xuống dòng còn lại
    
    printf("Nhap ten: ");
    fgets(student->name, sizeof(student->name), stdin);
    // Xóa ký tự xuống dòng ở cuối tên
    student->name[strcspn(student->name, "\n")] = 0;
    
    printf("Nhap tuoi: ");
    scanf("%d", &student->age);
    
    printf("Nhap GPA: ");
    scanf("%f", &student->gpa);
    printf("\n");
}

// Hàm nhập danh sách sinh viên (tối đa 5 sinh viên)
int inputStudents(struct Student students[], int maxCount) {
    int count;
    
    printf("Nhap so luong sinh vien (toi da %d): ", maxCount);
    scanf("%d", &count);
    
    // Kiểm tra số lượng hợp lệ
    if (count < 1 || count > maxCount) {
        printf("So luong khong hop le! Chi cho phep tu 1 den %d sinh vien.\n", maxCount);
        return 0;
    }
    
    printf("\n=== NHAP THONG TIN SINH VIEN ===\n");
    for (int i = 0; i < count; i++) {
        printf("\nSinh vien thu %d:\n", i + 1);
        inputStudent(&students[i]);
    }
    
    return count;
}

// Hàm in danh sách sinh viên dưới dạng bảng
void printStudents(struct Student students[], int count) {
    if (count == 0) {
        printf("Danh sach rong!\n");
        return;
    }
    
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
    struct Student students[5]; // Mảng chứa tối đa 5 sinh viên
    int count;
    
    printf("=== CHUONG TRINH QUAN LY SINH VIEN ===\n");
    
    // Nhập danh sách sinh viên từ bàn phím
    count = inputStudents(students, 5);
    
    if (count > 0) {
        // In danh sách sinh viên
        printf("\n=== DANH SACH SINH VIEN ===\n");
        printStudents(students, count);
        printf("\nDa nhap va xuat danh sach thanh cong!\n");
    } else {
        printf("Khong co sinh vien nao duoc nhap.\n");
    }
    
    return 0;
}

