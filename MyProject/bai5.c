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

// Hàm in thông tin một sinh viên
void printStudent(struct Student *student) {
    if (student == NULL) {
        printf("Sinh vien khong ton tai!\n");
        return;
    }
    
    printf("\n+------+----------------------+------+------+\n");
    printf("|  ID  |        Name          | Age  | GPA  |\n");
    printf("+------+----------------------+------+------+\n");
    printf("| %-4d | %-20s | %-4d | %-4.2f |\n",
           student->id,
           student->name,
           student->age,
           student->gpa);
    printf("+------+----------------------+------+------+\n");
}

/**
 * Tìm kiếm sinh viên theo ID trong danh sách
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param count Số lượng sinh viên trong mảng
 * @param id ID của sinh viên cần tìm
 * @return Con trỏ đến struct Student nếu tìm thấy, NULL nếu không tìm thấy
 * 
 * @note Hàm sẽ trả về NULL nếu:
 *       - ID không tồn tại trong danh sách
 *       - ID là số âm (không hợp lệ)
 *       - Danh sách rỗng
 * 
 * @example
 *   struct Student students[3] = {{1, "An", 20, 3.5}, ...};
 *   struct Student *found = searchByID(students, 3, 1);
 *   if (found != NULL) {
 *       printf("Tim thay: %s\n", found->name);
 *   }
 */
struct Student* searchByID(struct Student students[], int count, int id) {
    // Kiểm tra ID hợp lệ (ID phải là số dương)
    if (id < 0) {
        return NULL;
    }
    
    // Kiểm tra danh sách rỗng
    if (count <= 0) {
        return NULL;
    }
    
    // Tìm kiếm tuyến tính
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return &students[i]; // Trả về địa chỉ của sinh viên tìm thấy
        }
    }
    
    // Không tìm thấy
    return NULL;
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

// Hàm test tìm kiếm sinh viên
void testSearchByID(struct Student students[], int count) {
    printf("\n=== TEST TIM KIEM SINH VIEN THEO ID ===\n\n");
    
    // Test case 1: ID tồn tại
    printf("Test case 1: Tim kiem ID ton tai (ID = 2)\n");
    struct Student *found1 = searchByID(students, count, 2);
    if (found1 != NULL) {
        printf("Ket qua: Tim thay sinh vien!\n");
        printStudent(found1);
    } else {
        printf("Ket qua: KHONG tim thay sinh vien!\n");
    }
    
    printf("\n");
    
    // Test case 2: ID không tồn tại
    printf("Test case 2: Tim kiem ID khong ton tai (ID = 999)\n");
    struct Student *found2 = searchByID(students, count, 999);
    if (found2 != NULL) {
        printf("Ket qua: Tim thay sinh vien!\n");
        printStudent(found2);
    } else {
        printf("Ket qua: KHONG tim thay sinh vien (ID = 999 khong ton tai)!\n");
    }
    
    printf("\n");
    
    // Test case 3: ID âm (không hợp lệ)
    printf("Test case 3: Tim kiem ID am (ID = -1)\n");
    struct Student *found3 = searchByID(students, count, -1);
    if (found3 != NULL) {
        printf("Ket qua: Tim thay sinh vien!\n");
        printStudent(found3);
    } else {
        printf("Ket qua: KHONG tim thay sinh vien (ID am khong hop le)!\n");
    }
    
    printf("\n");
    
    // Test case bổ sung: ID = 0 (có thể hợp lệ hoặc không, tùy thiết kế)
    printf("Test case 4: Tim kiem ID = 0\n");
    struct Student *found4 = searchByID(students, count, 0);
    if (found4 != NULL) {
        printf("Ket qua: Tim thay sinh vien!\n");
        printStudent(found4);
    } else {
        printf("Ket qua: KHONG tim thay sinh vien (ID = 0 khong ton tai)!\n");
    }
}

int main() {
    struct Student students[100]; // Mảng để lưu sinh viên đọc từ file
    int count;
    
    printf("=== CHUONG TRINH QUAN LY SINH VIEN ===\n");
    
    // Đọc danh sách từ file
    printf("Dang doc danh sach sinh vien tu file students.txt...\n");
    count = loadFromFile(students, 100, "students.txt");
    
    if (count > 0) {
        printf("Da doc thanh cong %d sinh vien tu file!\n", count);
        
        // In danh sách sinh viên ra màn hình
        printf("\n=== DANH SACH SINH VIEN ===\n");
        printStudents(students, count);
        
        // Chạy các test case tìm kiếm
        testSearchByID(students, count);
    } else {
        // Nếu không đọc được từ file, khởi tạo dữ liệu mẫu để test
        printf("Khong the doc duoc danh sach sinh vien tu file!\n");
        printf("Khoi tao du lieu mau de test...\n\n");
        
        // Khởi tạo 3 sinh viên mẫu
        struct Student sampleStudents[3] = {
            {1, "Nguyen Van An", 20, 3.75},
            {2, "Tran Thi Binh", 21, 3.85},
            {3, "Le Van Cuong", 19, 3.65}
        };
        
        count = 3;
        // Copy vào mảng students
        for (int i = 0; i < count; i++) {
            students[i] = sampleStudents[i];
        }
        
        printf("=== DANH SACH SINH VIEN MAU ===\n");
        printStudents(students, count);
        
        // Chạy các test case tìm kiếm
        testSearchByID(students, count);
    }
    
    return 0;
}

