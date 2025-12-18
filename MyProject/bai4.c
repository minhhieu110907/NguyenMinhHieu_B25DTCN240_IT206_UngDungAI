#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Định nghĩa struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

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

// Hàm lưu danh sách sinh viên vào file students.txt (định dạng đơn giản để dễ đọc)
int saveToFile(struct Student students[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("Khong the mo file %s de ghi!\n", filename);
        return 0;
    }
    
    // Ghi số lượng sinh viên trước
    fprintf(file, "%d\n", count);
    
    // Ghi thông tin từng sinh viên (mỗi dòng: id,name,age,gpa)
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%d,%.2f\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].gpa);
    }
    
    fclose(file);
    return 1;
}

// Hàm đọc danh sách sinh viên từ file students.txt
int loadFromFile(struct Student students[], int maxCount, const char *filename) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Khong the mo file %s de doc!\n", filename);
        return 0;
    }
    
    int count;
    // Đọc số lượng sinh viên
    if (fscanf(file, "%d\n", &count) != 1) {
        printf("Loi doc so luong sinh vien!\n");
        fclose(file);
        return 0;
    }
    
    // Kiểm tra số lượng hợp lệ
    if (count < 0 || count > maxCount) {
        printf("So luong sinh vien khong hop le! (toi da %d)\n", maxCount);
        fclose(file);
        return 0;
    }
    
    // Đọc thông tin từng sinh viên
    for (int i = 0; i < count; i++) {
        char line[200];
        if (fgets(line, sizeof(line), file) == NULL) {
            printf("Loi doc thong tin sinh vien thu %d!\n", i + 1);
            fclose(file);
            return 0;
        }
        
        // Parse dòng: id,name,age,gpa
        char *token;
        char *rest = line;
        
        // Đọc ID
        token = strtok(rest, ",");
        if (token == NULL) {
            printf("Loi parse ID sinh vien thu %d!\n", i + 1);
            fclose(file);
            return 0;
        }
        students[i].id = atoi(token);
        
        // Đọc Name
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Loi parse Name sinh vien thu %d!\n", i + 1);
            fclose(file);
            return 0;
        }
        strcpy(students[i].name, token);
        
        // Đọc Age
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Loi parse Age sinh vien thu %d!\n", i + 1);
            fclose(file);
            return 0;
        }
        students[i].age = atoi(token);
        
        // Đọc GPA
        token = strtok(NULL, "\n");
        if (token == NULL) {
            printf("Loi parse GPA sinh vien thu %d!\n", i + 1);
            fclose(file);
            return 0;
        }
        students[i].gpa = atof(token);
    }
    
    fclose(file);
    return count;
}

int main() {
    struct Student students[100]; // Mảng để lưu sinh viên đọc từ file
    int count;
    
    printf("=== DOC DANH SACH SINH VIEN TU FILE ===\n");
    
    // Đọc danh sách từ file
    printf("Dang doc danh sach sinh vien tu file students.txt...\n");
    count = loadFromFile(students, 100, "students.txt");
    
    if (count > 0) {
        printf("Da doc thanh cong %d sinh vien tu file!\n", count);
        
        // In danh sách sinh viên ra màn hình
        printf("\n=== DANH SACH SINH VIEN ===\n");
        printStudents(students, count);
    } else {
        printf("Khong the doc duoc danh sach sinh vien tu file!\n");
        printf("Vui long chay bai3.c truoc de tao file students.txt\n");
        return 1;
    }
    
    return 0;
}

