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

/**
 * Sắp xếp danh sách sinh viên theo GPA giảm dần sử dụng thuật toán Bubble Sort
 */
void sortByGPADescending(struct Student students[], int count) {
    if (count <= 1 || students == NULL) {
        return;
    }
    
    for (int i = 0; i < count - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < count - 1 - i; j++) {
            if (students[j].gpa < students[j + 1].gpa) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
    }
}

/**
 * Tính GPA trung bình của danh sách sinh viên
 */
float calculateAverageGPA(struct Student students[], int count) {
    if (count <= 0 || students == NULL) {
        return -1.0;
    }
    
    float sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += students[i].gpa;
    }
    
    return sum / count;
}

/**
 * Kiểm tra xem ID đã tồn tại trong danh sách chưa
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param count Số lượng sinh viên hiện tại
 * @param id ID cần kiểm tra
 * @return 1 nếu ID đã tồn tại, 0 nếu chưa tồn tại
 */
int isIDExists(struct Student students[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            return 1; // ID đã tồn tại
        }
    }
    return 0; // ID chưa tồn tại
}

/**
 * Thêm sinh viên mới vào danh sách
 * 
 * MÔ TẢ:
 * Hàm này thêm một sinh viên mới vào cuối danh sách. Trước khi thêm,
 * hàm sẽ kiểm tra xem ID của sinh viên mới có trùng với ID của sinh viên
 * nào trong danh sách hiện tại không.
 * 
 * CÁC BƯỚC XỬ LÝ:
 * 1. Kiểm tra danh sách đã đầy chưa (count >= maxCount)
 * 2. Kiểm tra ID có hợp lệ không (ID > 0)
 * 3. Kiểm tra ID có trùng với ID trong danh sách không
 * 4. Nếu tất cả điều kiện đều thỏa mãn, thêm sinh viên vào cuối danh sách
 * 5. Tăng số lượng sinh viên lên 1
 * 
 * @param students Mảng chứa danh sách sinh viên (sẽ được cập nhật)
 * @param count Con trỏ đến số lượng sinh viên hiện tại (sẽ được tăng lên 1 nếu thêm thành công)
 * @param maxCount Số lượng tối đa sinh viên có thể lưu trong mảng
 * @param newStudent Sinh viên mới cần thêm vào
 * 
 * @return 1 nếu thêm thành công, 0 nếu thất bại
 * 
 * @note Hàm sẽ trả về 0 (thất bại) trong các trường hợp:
 *       - Danh sách đã đầy (count >= maxCount)
 *       - ID không hợp lệ (ID <= 0)
 *       - ID đã tồn tại trong danh sách (trùng ID)
 * 
 * @example
 *   struct Student students[100];
 *   int count = 5;
 *   struct Student newStudent = {6, "Nguyen Van A", 20, 3.5};
 *   if (addStudent(students, &count, 100, newStudent)) {
 *       printf("Them thanh cong! So luong sinh vien: %d\n", count);
 *   } else {
 *       printf("Them that bai!\n");
 *   }
 */
int addStudent(struct Student students[], int *count, int maxCount, struct Student newStudent) {
    // BƯỚC 1: Kiểm tra danh sách đã đầy chưa
    if (*count >= maxCount) {
        printf("Loi: Danh sach da day! Khong the them sinh vien moi.\n");
        return 0; // Trả về 0 để báo lỗi
    }
    
    // BƯỚC 2: Kiểm tra ID có hợp lệ không
    if (newStudent.id <= 0) {
        printf("Loi: ID khong hop le! ID phai la so duong.\n");
        return 0;
    }
    
    // BƯỚC 3: Kiểm tra ID có trùng với ID trong danh sách không
    if (isIDExists(students, *count, newStudent.id)) {
        printf("Loi: ID %d da ton tai trong danh sach! Khong the them sinh vien trung ID.\n", newStudent.id);
        return 0; // Trả về 0 để báo lỗi trùng ID
    }
    
    // BƯỚC 4: Thêm sinh viên vào cuối danh sách
    students[*count] = newStudent;
    
    // BƯỚC 5: Tăng số lượng sinh viên lên 1
    (*count)++;
    
    printf("Da them thanh cong sinh vien: ID=%d, Ten=%s\n", newStudent.id, newStudent.name);
    return 1; // Trả về 1 để báo thành công
}

/**
 * Xóa sinh viên khỏi danh sách theo ID
 * 
 * MÔ TẢ:
 * Hàm này tìm và xóa sinh viên có ID trùng với ID được cung cấp khỏi danh sách.
 * Sau khi xóa, các sinh viên phía sau sẽ được dịch chuyển lên để lấp đầy vị trí trống.
 * 
 * CÁC BƯỚC XỬ LÝ:
 * 1. Kiểm tra danh sách có rỗng không (count <= 0)
 * 2. Tìm vị trí của sinh viên có ID trùng khớp
 * 3. Nếu không tìm thấy, báo lỗi và trả về 0
 * 4. Nếu tìm thấy, dịch chuyển tất cả các sinh viên phía sau lên 1 vị trí
 * 5. Giảm số lượng sinh viên xuống 1
 * 
 * @param students Mảng chứa danh sách sinh viên (sẽ được cập nhật)
 * @param count Con trỏ đến số lượng sinh viên hiện tại (sẽ được giảm xuống 1 nếu xóa thành công)
 * @param id ID của sinh viên cần xóa
 * 
 * @return 1 nếu xóa thành công, 0 nếu thất bại
 * 
 * @note Hàm sẽ trả về 0 (thất bại) trong các trường hợp:
 *       - Danh sách rỗng (count <= 0)
 *       - ID không tồn tại trong danh sách
 *       - ID không hợp lệ (ID <= 0)
 * 
 * @note Sau khi xóa, thứ tự của các sinh viên còn lại sẽ được giữ nguyên
 *       (chỉ dịch chuyển lên để lấp đầy vị trí trống)
 * 
 * @example
 *   struct Student students[100];
 *   int count = 5;
 *   if (deleteStudentByID(students, &count, 3)) {
 *       printf("Xoa thanh cong! So luong sinh vien con lai: %d\n", count);
 *   } else {
 *       printf("Xoa that bai! ID khong ton tai.\n");
 *   }
 */
int deleteStudentByID(struct Student students[], int *count, int id) {
    // BƯỚC 1: Kiểm tra danh sách có rỗng không
    if (*count <= 0) {
        printf("Loi: Danh sach rong! Khong co sinh vien nao de xoa.\n");
        return 0; // Trả về 0 để báo lỗi
    }
    
    // Kiểm tra ID có hợp lệ không
    if (id <= 0) {
        printf("Loi: ID khong hop le! ID phai la so duong.\n");
        return 0;
    }
    
    // BƯỚC 2: Tìm vị trí của sinh viên có ID trùng khớp
    int foundIndex = -1; // -1 nghĩa là chưa tìm thấy
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            foundIndex = i; // Lưu vị trí tìm thấy
            break; // Dừng vòng lặp khi đã tìm thấy
        }
    }
    
    // BƯỚC 3: Kiểm tra có tìm thấy sinh viên không
    if (foundIndex == -1) {
        printf("Loi: Khong tim thay sinh vien co ID = %d trong danh sach!\n", id);
        return 0; // Trả về 0 để báo lỗi không tìm thấy
    }
    
    // BƯỚC 4: Dịch chuyển tất cả các sinh viên phía sau lên 1 vị trí
    // Điều này sẽ ghi đè lên sinh viên cần xóa
    for (int i = foundIndex; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }
    
    // BƯỚC 5: Giảm số lượng sinh viên xuống 1
    (*count)--;
    
    printf("Da xoa thanh cong sinh vien co ID = %d! So luong sinh vien con lai: %d\n", id, *count);
    return 1; // Trả về 1 để báo thành công
}

/**
 * Nhập thông tin một sinh viên từ bàn phím
 * 
 * @param student Con trỏ đến struct Student để lưu thông tin nhập được
 */
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
}

/**
 * Lưu danh sách sinh viên vào file với định dạng CSV
 */
int saveToFile(struct Student students[], int count, const char *filename) {
    FILE *file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("Loi: Khong the mo file %s de ghi!\n", filename);
        return 0;
    }
    
    fprintf(file, "%d\n", count);
    
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

/**
 * Đọc danh sách sinh viên từ file
 */
int loadFromFile(struct Student students[], int maxCount, const char *filename) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Loi: Khong the mo file %s de doc!\n", filename);
        return 0;
    }
    
    int count;
    if (fscanf(file, "%d\n", &count) != 1) {
        printf("Loi doc so luong sinh vien!\n");
        fclose(file);
        return 0;
    }
    
    if (count < 0 || count > maxCount) {
        printf("So luong sinh vien khong hop le! (toi da %d)\n", maxCount);
        fclose(file);
        return 0;
    }
    
    for (int i = 0; i < count; i++) {
        char line[200];
        if (fgets(line, sizeof(line), file) == NULL) {
            printf("Loi doc thong tin sinh vien thu %d!\n", i + 1);
            fclose(file);
            return 0;
        }
        
        char *token;
        char *rest = line;
        
        token = strtok(rest, ",");
        if (token == NULL) {
            printf("Loi parse ID sinh vien thu %d!\n", i + 1);
            fclose(file);
            return 0;
        }
        students[i].id = atoi(token);
        
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Loi parse Name sinh vien thu %d!\n", i + 1);
            fclose(file);
            return 0;
        }
        strcpy(students[i].name, token);
        
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Loi parse Age sinh vien thu %d!\n", i + 1);
            fclose(file);
            return 0;
        }
        students[i].age = atoi(token);
        
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

/**
 * Test case cho hàm thêm sinh viên
 */
void testAddStudent() {
    printf("\n=== TEST THEM SINH VIEN ===\n\n");
    
    struct Student students[100];
    int count = 3;
    
    // Khởi tạo dữ liệu mẫu
    students[0] = (struct Student){1, "Nguyen Van An", 20, 3.5};
    students[1] = (struct Student){2, "Tran Thi Binh", 21, 3.8};
    students[2] = (struct Student){3, "Le Van Cuong", 19, 3.2};
    
    printf("Danh sach ban dau (%d sinh vien):\n", count);
    printStudents(students, count);
    
    // Test case 1: Thêm sinh viên thành công (ID mới)
    printf("\n--- Test case 1: Them sinh vien thanh cong (ID moi) ---\n");
    struct Student newStudent1 = {4, "Pham Thi Dung", 22, 3.9};
    int result1 = addStudent(students, &count, 100, newStudent1);
    if (result1 == 1 && count == 4) {
        printf("✓ Test case 1: THANH CONG - Them sinh vien thanh cong!\n");
        printStudents(students, count);
    } else {
        printf("✗ Test case 1: THAT BAI - Them sinh vien khong thanh cong!\n");
    }
    
    // Test case 2: Thêm sinh viên trùng ID
    printf("\n--- Test case 2: Them sinh vien trung ID ---\n");
    struct Student newStudent2 = {2, "Hoang Van Em", 20, 3.0}; // ID = 2 đã tồn tại
    int oldCount = count;
    int result2 = addStudent(students, &count, 100, newStudent2);
    if (result2 == 0 && count == oldCount) {
        printf("✓ Test case 2: THANH CONG - Tu choi them sinh vien trung ID!\n");
    } else {
        printf("✗ Test case 2: THAT BAI - Khong tu choi them sinh vien trung ID!\n");
    }
    
    // Test case 3: Thêm sinh viên với ID không hợp lệ (ID <= 0)
    printf("\n--- Test case 3: Them sinh vien voi ID khong hop le (ID = -1) ---\n");
    struct Student newStudent3 = {-1, "Test Student", 20, 3.0};
    oldCount = count;
    int result3 = addStudent(students, &count, 100, newStudent3);
    if (result3 == 0 && count == oldCount) {
        printf("✓ Test case 3: THANH CONG - Tu choi them sinh vien voi ID khong hop le!\n");
    } else {
        printf("✗ Test case 3: THAT BAI - Khong tu choi them sinh vien voi ID khong hop le!\n");
    }
    
    // Test case 4: Thêm khi danh sách đầy
    printf("\n--- Test case 4: Them khi danh sach day (maxCount = 4, count = 4) ---\n");
    struct Student newStudent4 = {5, "Test Student", 20, 3.0};
    int result4 = addStudent(students, &count, 4, newStudent4); // maxCount = 4, count đã = 4
    if (result4 == 0) {
        printf("✓ Test case 4: THANH CONG - Tu choi them khi danh sach day!\n");
    } else {
        printf("✗ Test case 4: THAT BAI - Khong tu choi them khi danh sach day!\n");
    }
}

/**
 * Test case cho hàm xóa sinh viên
 */
void testDeleteStudent() {
    printf("\n=== TEST XOA SINH VIEN ===\n\n");
    
    struct Student students[100];
    int count = 5;
    
    // Khởi tạo dữ liệu mẫu
    students[0] = (struct Student){1, "Nguyen Van An", 20, 3.5};
    students[1] = (struct Student){2, "Tran Thi Binh", 21, 3.8};
    students[2] = (struct Student){3, "Le Van Cuong", 19, 3.2};
    students[3] = (struct Student){4, "Pham Thi Dung", 22, 3.9};
    students[4] = (struct Student){5, "Hoang Van Em", 20, 3.0};
    
    printf("Danh sach ban dau (%d sinh vien):\n", count);
    printStudents(students, count);
    
    // Test case 1: Xóa sinh viên thành công (ID tồn tại)
    printf("\n--- Test case 1: Xoa sinh vien thanh cong (ID ton tai) ---\n");
    int oldCount = count;
    int result1 = deleteStudentByID(students, &count, 3); // Xóa ID = 3
    if (result1 == 1 && count == oldCount - 1) {
        printf("✓ Test case 1: THANH CONG - Xoa sinh vien thanh cong!\n");
        printf("Danh sach sau khi xoa:\n");
        printStudents(students, count);
        
        // Kiểm tra ID = 3 đã bị xóa chưa
        int found = 0;
        for (int i = 0; i < count; i++) {
            if (students[i].id == 3) {
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("✓ Xac nhan: ID = 3 da bi xoa khoi danh sach!\n");
        } else {
            printf("✗ Xac nhan: ID = 3 van con trong danh sach!\n");
        }
    } else {
        printf("✗ Test case 1: THAT BAI - Xoa sinh vien khong thanh cong!\n");
    }
    
    // Test case 2: Xóa sinh viên không tồn tại (ID không có trong danh sách)
    printf("\n--- Test case 2: Xoa sinh vien khong ton tai (ID = 999) ---\n");
    oldCount = count;
    int result2 = deleteStudentByID(students, &count, 999); // ID = 999 không tồn tại
    if (result2 == 0 && count == oldCount) {
        printf("✓ Test case 2: THANH CONG - Tu choi xoa sinh vien khong ton tai!\n");
    } else {
        printf("✗ Test case 2: THAT BAI - Khong tu choi xoa sinh vien khong ton tai!\n");
    }
    
    // Test case 3: Xóa với ID không hợp lệ (ID <= 0)
    printf("\n--- Test case 3: Xoa voi ID khong hop le (ID = -1) ---\n");
    oldCount = count;
    int result3 = deleteStudentByID(students, &count, -1);
    if (result3 == 0 && count == oldCount) {
        printf("✓ Test case 3: THANH CONG - Tu choi xoa voi ID khong hop le!\n");
    } else {
        printf("✗ Test case 3: THAT BAI - Khong tu choi xoa voi ID khong hop le!\n");
    }
    
    // Test case 4: Xóa khi danh sách rỗng
    printf("\n--- Test case 4: Xoa khi danh sach rong ---\n");
    struct Student emptyStudents[100];
    int emptyCount = 0;
    int result4 = deleteStudentByID(emptyStudents, &emptyCount, 1);
    if (result4 == 0 && emptyCount == 0) {
        printf("✓ Test case 4: THANH CONG - Tu choi xoa khi danh sach rong!\n");
    } else {
        printf("✗ Test case 4: THAT BAI - Khong tu choi xoa khi danh sach rong!\n");
    }
}

int main() {
    struct Student students[100];
    int count = 0;
    int choice;
    
    printf("=== CHUONG TRINH QUAN LY SINH VIEN ===\n");
    printf("Chuc nang: Them va xoa sinh vien\n\n");
    
    // Khởi tạo dữ liệu mẫu để test
    students[0] = (struct Student){1, "Nguyen Van An", 20, 3.5};
    students[1] = (struct Student){2, "Tran Thi Binh", 21, 3.8};
    students[2] = (struct Student){3, "Le Van Cuong", 19, 3.2};
    count = 3;
    
    printf("Danh sach sinh vien ban dau:\n");
    printStudents(students, count);
    
    do {
        printf("\n=== MENU ===\n");
        printf("1. Them sinh vien moi\n");
        printf("2. Xoa sinh vien theo ID\n");
        printf("3. Hien thi danh sach\n");
        printf("4. Chay test case\n");
        printf("5. Thoat\n");
        printf("Lua chon cua ban: ");
        
        scanf("%d", &choice);
        getchar(); // Xóa ký tự xuống dòng còn lại
        
        switch (choice) {
            case 1: {
                printf("\n=== THEM SINH VIEN MOI ===\n");
                struct Student newStudent;
                inputStudent(&newStudent);
                addStudent(students, &count, 100, newStudent);
                break;
            }
            
            case 2: {
                printf("\n=== XOA SINH VIEN THEO ID ===\n");
                int id;
                printf("Nhap ID sinh vien can xoa: ");
                scanf("%d", &id);
                deleteStudentByID(students, &count, id);
                break;
            }
            
            case 3: {
                printf("\n=== DANH SACH SINH VIEN ===\n");
                printStudents(students, count);
                if (count > 0) {
                    float avgGPA = calculateAverageGPA(students, count);
                    printf("\nGPA trung binh: %.2f\n", avgGPA);
                }
                break;
            }
            
            case 4: {
                // Chạy các test case
                testAddStudent();
                testDeleteStudent();
                break;
            }
            
            case 5: {
                printf("Cam on ban da su dung chuong trinh!\n");
                break;
            }
            
            default: {
                printf("Lua chon khong hop le! Vui long chon lai.\n");
                break;
            }
        }
    } while (choice != 5);
    
    return 0;
}

