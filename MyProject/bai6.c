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
 * Tính GPA trung bình của danh sách sinh viên
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param count Số lượng sinh viên trong mảng
 * @return GPA trung bình (float). Trả về -1.0 nếu danh sách rỗng hoặc count <= 0
 * 
 * @note Hàm sẽ trả về -1.0 nếu:
 *       - Danh sách rỗng (count <= 0)
 *       - Mảng students là NULL
 * 
 * @example
 *   struct Student students[3] = {{1, "An", 20, 3.5}, {2, "Binh", 21, 3.8}, {3, "Cuong", 19, 3.2}};
 *   float avg = calculateAverageGPA(students, 3);
 *   if (avg >= 0) {
 *       printf("GPA trung binh: %.2f\n", avg);
 *   }
 */
float calculateAverageGPA(struct Student students[], int count) {
    // Kiểm tra danh sách rỗng
    if (count <= 0 || students == NULL) {
        return -1.0;
    }
    
    float sum = 0.0;
    
    // Tính tổng GPA
    for (int i = 0; i < count; i++) {
        sum += students[i].gpa;
    }
    
    // Tính trung bình
    return sum / count;
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

// Hàm khởi tạo 10 sinh viên mẫu với GPA khác nhau
void initializeSampleStudents(struct Student students[], int *count) {
    struct Student sampleStudents[10] = {
        {1, "Nguyen Van An", 20, 2.50},      // GPA thấp
        {2, "Tran Thi Binh", 21, 3.25},      // GPA trung bình thấp
        {3, "Le Van Cuong", 19, 3.75},       // GPA khá
        {4, "Pham Thi Dung", 22, 4.00},      // GPA xuất sắc
        {5, "Hoang Van Em", 20, 2.00},       // GPA rất thấp
        {6, "Vu Thi Phuong", 21, 3.50},      // GPA trung bình
        {7, "Dao Van Giang", 19, 3.90},      // GPA cao
        {8, "Bui Thi Hoa", 20, 2.75},        // GPA trung bình thấp
        {9, "Ngo Van Inh", 22, 3.60},        // GPA khá
        {10, "Dinh Thi Kieu", 21, 3.85}      // GPA cao
    };
    
    *count = 10;
    for (int i = 0; i < 10; i++) {
        students[i] = sampleStudents[i];
    }
}

// Hàm test tính GPA trung bình
void testCalculateAverageGPA() {
    printf("\n=== TEST TINH GPA TRUNG BINH ===\n\n");
    
    // Test case 1: Danh sách có 10 sinh viên với GPA khác nhau
    printf("Test case 1: Danh sach co 10 sinh vien\n");
    struct Student students[10];
    int count;
    
    initializeSampleStudents(students, &count);
    
    printf("Danh sach sinh vien:\n");
    printStudents(students, count);
    
    float avgGPA = calculateAverageGPA(students, count);
    if (avgGPA >= 0) {
        printf("\nGPA trung binh: %.2f\n", avgGPA);
        
        // Tính thủ công để kiểm tra
        float sum = 0;
        for (int i = 0; i < count; i++) {
            sum += students[i].gpa;
        }
        float expected = sum / count;
        printf("GPA trung binh (tinh thu cong): %.2f\n", expected);
        
        if (avgGPA == expected) {
            printf("✓ Test case 1: THANH CONG - Ket qua dung!\n");
        } else {
            printf("✗ Test case 1: THAT BAI - Ket qua khong khop!\n");
        }
    } else {
        printf("✗ Test case 1: THAT BAI - Khong tinh duoc GPA!\n");
    }
    
    printf("\n");
    
    // Test case 2: Danh sách rỗng
    printf("Test case 2: Danh sach rong (count = 0)\n");
    struct Student emptyStudents[10];
    float avgGPA2 = calculateAverageGPA(emptyStudents, 0);
    
    if (avgGPA2 < 0) {
        printf("Ket qua: %.2f (gia tri dac biet cho danh sach rong)\n", avgGPA2);
        printf("✓ Test case 2: THANH CONG - Xu ly dung truong hop danh sach rong!\n");
    } else {
        printf("✗ Test case 2: THAT BAI - Khong xu ly dung truong hop danh sach rong!\n");
    }
    
    printf("\n");
    
    // Test case 3: Danh sách với count âm
    printf("Test case 3: Danh sach voi count am (count = -1)\n");
    float avgGPA3 = calculateAverageGPA(students, -1);
    
    if (avgGPA3 < 0) {
        printf("Ket qua: %.2f (gia tri dac biet cho count khong hop le)\n", avgGPA3);
        printf("✓ Test case 3: THANH CONG - Xu ly dung truong hop count am!\n");
    } else {
        printf("✗ Test case 3: THAT BAI - Khong xu ly dung truong hop count am!\n");
    }
    
    printf("\n");
    
    // Test case 4: Danh sách với 1 sinh viên
    printf("Test case 4: Danh sach voi 1 sinh vien\n");
    struct Student singleStudent[1] = {{1, "Test Student", 20, 3.75}};
    float avgGPA4 = calculateAverageGPA(singleStudent, 1);
    
    if (avgGPA4 >= 0 && avgGPA4 == 3.75) {
        printf("GPA trung binh: %.2f\n", avgGPA4);
        printf("✓ Test case 4: THANH CONG - Ket qua dung cho 1 sinh vien!\n");
    } else {
        printf("✗ Test case 4: THAT BAI - Ket qua khong dung!\n");
    }
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
    struct Student students[100]; // Mảng để lưu sinh viên
    int count;
    
    printf("=== CHUONG TRINH QUAN LY SINH VIEN ===\n");
    
    // Khởi tạo 10 sinh viên mẫu với GPA khác nhau
    printf("Khoi tao 10 sinh vien mau voi GPA khac nhau...\n");
    initializeSampleStudents(students, &count);
    
    // In danh sách sinh viên
    printf("\n=== DANH SACH SINH VIEN ===\n");
    printStudents(students, count);
    
    // Tính và hiển thị GPA trung bình
    float avgGPA = calculateAverageGPA(students, count);
    if (avgGPA >= 0) {
        printf("\n=== KET QUA ===\n");
        printf("GPA trung binh cua %d sinh vien: %.2f\n", count, avgGPA);
    }
    
    // Chạy các test case
    testCalculateAverageGPA();
    
    return 0;
}

