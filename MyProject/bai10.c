#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ============================================================================
// ĐỊNH NGHĨA CẤU TRÚC DỮ LIỆU
// ============================================================================

/**
 * Cấu trúc Student chứa thông tin của một sinh viên
 * - id: Mã số sinh viên (số nguyên dương)
 * - name: Tên sinh viên (chuỗi ký tự, tối đa 50 ký tự)
 * - age: Tuổi (số nguyên)
 * - gpa: Điểm trung bình (số thực từ 0.0 đến 4.0)
 */
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

// ============================================================================
// CÁC HÀM TIỆN ÍCH
// ============================================================================

/**
 * CHỨC NĂNG: In danh sách sinh viên dưới dạng bảng
 * 
 * MÔ TẢ:
 * Hàm này hiển thị danh sách sinh viên ra màn hình dưới dạng bảng có viền.
 * Nếu danh sách rỗng, sẽ hiển thị thông báo "Danh sach rong!".
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param count Số lượng sinh viên trong danh sách
 */
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
 * CHỨC NĂNG: Nhập thông tin một sinh viên từ bàn phím
 * 
 * MÔ TẢ:
 * Hàm này yêu cầu người dùng nhập từng trường thông tin của sinh viên
 * (ID, tên, tuổi, GPA) và lưu vào struct Student.
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
 * CHỨC NĂNG: Kiểm tra xem ID đã tồn tại trong danh sách chưa
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

// ============================================================================
// CÁC HÀM CHỨC NĂNG CHÍNH
// ============================================================================

/**
 * CHỨC NĂNG 1: Nhập sinh viên từ bàn phím
 * 
 * MÔ TẢ:
 * Cho phép người dùng nhập thông tin sinh viên mới từ bàn phím.
 * Kiểm tra ID không được trùng với sinh viên đã có trong danh sách.
 * 
 * @param students Mảng chứa danh sách sinh viên (sẽ được cập nhật)
 * @param count Con trỏ đến số lượng sinh viên (sẽ được tăng lên)
 * @param maxCount Số lượng tối đa sinh viên có thể lưu
 */
void nhapSinhVien(struct Student students[], int *count, int maxCount) {
    printf("\n=== NHAP SINH VIEN MOI ===\n");
    
    // Kiểm tra danh sách đã đầy chưa
    if (*count >= maxCount) {
        printf("Loi: Danh sach da day! Khong the them sinh vien moi.\n");
        return;
    }
    
    struct Student newStudent;
    inputStudent(&newStudent);
    
    // Kiểm tra ID hợp lệ
    if (newStudent.id <= 0) {
        printf("Loi: ID khong hop le! ID phai la so duong.\n");
        return;
    }
    
    // Kiểm tra ID trùng
    if (isIDExists(students, *count, newStudent.id)) {
        printf("Loi: ID %d da ton tai trong danh sach! Khong the them sinh vien trung ID.\n", newStudent.id);
        return;
    }
    
    // Thêm sinh viên vào danh sách
    students[*count] = newStudent;
    (*count)++;
    
    printf("Da them thanh cong sinh vien: ID=%d, Ten=%s\n", newStudent.id, newStudent.name);
}

/**
 * CHỨC NĂNG 2: In danh sách sinh viên
 * 
 * MÔ TẢ:
 * Hiển thị toàn bộ danh sách sinh viên hiện có trong mảng ra màn hình
 * dưới dạng bảng. Nếu danh sách rỗng, hiển thị thông báo.
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param count Số lượng sinh viên trong danh sách
 */
void inDanhSach(struct Student students[], int count) {
    printf("\n=== DANH SACH SINH VIEN ===\n");
    printStudents(students, count);
    
    if (count > 0) {
        // Tính và hiển thị thống kê
        float sum = 0.0;
        for (int i = 0; i < count; i++) {
            sum += students[i].gpa;
        }
        float avgGPA = sum / count;
        printf("\nThong ke:\n");
        printf("  - So luong sinh vien: %d\n", count);
        printf("  - GPA trung binh: %.2f\n", avgGPA);
    }
}

/**
 * CHỨC NĂNG 3: Ghi danh sách sinh viên vào file
 * 
 * MÔ TẢ:
 * Lưu toàn bộ danh sách sinh viên vào file với định dạng CSV.
 * File sẽ có cấu trúc:
 * - Dòng đầu: Số lượng sinh viên
 * - Các dòng tiếp theo: id,name,age,gpa (mỗi dòng một sinh viên)
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param count Số lượng sinh viên
 */
void ghiFile(struct Student students[], int count) {
    printf("\n=== GHI FILE ===\n");
    
    if (count == 0) {
        printf("Danh sach rong! Khong co du lieu de ghi.\n");
        return;
    }
    
    char filename[100];
    printf("Nhap ten file de ghi (vi du: students.txt): ");
    fgets(filename, sizeof(filename), stdin);
    // Xóa ký tự xuống dòng
    filename[strcspn(filename, "\n")] = 0;
    
    // Mở file để ghi
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Loi: Khong the mo file %s de ghi!\n", filename);
        return;
    }
    
    // Ghi số lượng sinh viên
    fprintf(file, "%d\n", count);
    
    // Ghi thông tin từng sinh viên
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%s,%d,%.2f\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].gpa);
    }
    
    fclose(file);
    printf("Da ghi thanh cong %d sinh vien vao file %s!\n", count, filename);
}

/**
 * CHỨC NĂNG 4: Đọc danh sách sinh viên từ file
 * 
 * MÔ TẢ:
 * Đọc dữ liệu sinh viên từ file đã lưu trước đó.
 * File phải có định dạng CSV như đã mô tả ở chức năng ghi file.
 * Dữ liệu đọc được sẽ thay thế toàn bộ danh sách hiện tại.
 * 
 * @param students Mảng để lưu sinh viên đọc được (sẽ được cập nhật)
 * @param count Con trỏ đến số lượng sinh viên (sẽ được cập nhật)
 * @param maxCount Số lượng tối đa sinh viên có thể đọc
 */
void docFile(struct Student students[], int *count, int maxCount) {
    printf("\n=== DOC FILE ===\n");
    
    char filename[100];
    printf("Nhap ten file de doc (vi du: students.txt): ");
    fgets(filename, sizeof(filename), stdin);
    // Xóa ký tự xuống dòng
    filename[strcspn(filename, "\n")] = 0;
    
    // Mở file để đọc
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Loi: Khong the mo file %s de doc!\n", filename);
        printf("Kiem tra lai ten file hoac duong dan file.\n");
        return;
    }
    
    // Đọc số lượng sinh viên
    int fileCount;
    if (fscanf(file, "%d\n", &fileCount) != 1) {
        printf("Loi: Khong the doc so luong sinh vien tu file!\n");
        fclose(file);
        return;
    }
    
    // Kiểm tra số lượng hợp lệ
    if (fileCount < 0 || fileCount > maxCount) {
        printf("Loi: So luong sinh vien khong hop le! (toi da %d, nhung file co %d)\n", maxCount, fileCount);
        fclose(file);
        return;
    }
    
    // Đọc thông tin từng sinh viên
    for (int i = 0; i < fileCount; i++) {
        char line[200];
        if (fgets(line, sizeof(line), file) == NULL) {
            printf("Loi: Khong the doc thong tin sinh vien thu %d!\n", i + 1);
            fclose(file);
            return;
        }
        
        // Parse dòng: id,name,age,gpa
        char *token;
        token = strtok(line, ",");
        if (token == NULL) {
            printf("Loi: Khong the phan tich ID sinh vien thu %d!\n", i + 1);
            fclose(file);
            return;
        }
        students[i].id = atoi(token);
        
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Loi: Khong the phan tich Name sinh vien thu %d!\n", i + 1);
            fclose(file);
            return;
        }
        strcpy(students[i].name, token);
        
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Loi: Khong the phan tich Age sinh vien thu %d!\n", i + 1);
            fclose(file);
            return;
        }
        students[i].age = atoi(token);
        
        token = strtok(NULL, "\n");
        if (token == NULL) {
            printf("Loi: Khong the phan tich GPA sinh vien thu %d!\n", i + 1);
            fclose(file);
            return;
        }
        students[i].gpa = atof(token);
    }
    
    fclose(file);
    *count = fileCount;
    printf("Da doc thanh cong %d sinh vien tu file %s!\n", fileCount, filename);
}

/**
 * CHỨC NĂNG 5: Tìm kiếm sinh viên theo ID
 * 
 * MÔ TẢ:
 * Tìm kiếm và hiển thị thông tin của sinh viên có ID trùng với ID được nhập.
 * Nếu không tìm thấy, hiển thị thông báo lỗi.
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param count Số lượng sinh viên trong danh sách
 */
void timKiem(struct Student students[], int count) {
    printf("\n=== TIM KIEM SINH VIEN ===\n");
    
    if (count == 0) {
        printf("Danh sach rong! Khong co sinh vien nao de tim kiem.\n");
        return;
    }
    
    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);
    
    // Kiểm tra ID hợp lệ
    if (id <= 0) {
        printf("Loi: ID khong hop le! ID phai la so duong.\n");
        return;
    }
    
    // Tìm kiếm sinh viên
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("\nTim thay sinh vien:\n");
            printf("+------+----------------------+------+------+\n");
            printf("|  ID  |        Name          | Age  | GPA  |\n");
            printf("+------+----------------------+------+------+\n");
            printf("| %-4d | %-20s | %-4d | %-4.2f |\n",
                   students[i].id,
                   students[i].name,
                   students[i].age,
                   students[i].gpa);
            printf("+------+----------------------+------+------+\n");
            found = 1;
            break;
        }
    }
    
    if (!found) {
        printf("Khong tim thay sinh vien co ID = %d trong danh sach!\n", id);
    }
}

/**
 * CHỨC NĂNG 6: Sắp xếp danh sách sinh viên theo GPA giảm dần
 * 
 * MÔ TẢ:
 * Sắp xếp danh sách sinh viên theo điểm GPA từ cao xuống thấp
 * sử dụng thuật toán Bubble Sort.
 * Sau khi sắp xếp, hiển thị lại danh sách.
 * 
 * @param students Mảng chứa danh sách sinh viên (sẽ được sắp xếp)
 * @param count Số lượng sinh viên trong danh sách
 */
void sapXep(struct Student students[], int count) {
    printf("\n=== SAP XEP THEO GPA GIAM DAN ===\n");
    
    if (count <= 1) {
        printf("Danh sach co it hon 2 sinh vien, khong can sap xep.\n");
        return;
    }
    
    // Bubble Sort: Sắp xếp giảm dần theo GPA
    for (int i = 0; i < count - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < count - 1 - i; j++) {
            if (students[j].gpa < students[j + 1].gpa) {
                // Đổi chỗ hai phần tử
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
                swapped = 1;
            }
        }
        // Tối ưu: Nếu không có đổi chỗ nào, mảng đã được sắp xếp
        if (swapped == 0) {
            break;
        }
    }
    
    printf("Da sap xep xong! Danh sach sau khi sap xep:\n");
    printStudents(students, count);
}

/**
 * CHỨC NĂNG 7: Thêm sinh viên mới vào danh sách
 * 
 * MÔ TẢ:
 * Thêm một sinh viên mới vào cuối danh sách.
 * Kiểm tra ID không được trùng và danh sách chưa đầy.
 * 
 * @param students Mảng chứa danh sách sinh viên (sẽ được cập nhật)
 * @param count Con trỏ đến số lượng sinh viên (sẽ được tăng lên)
 * @param maxCount Số lượng tối đa sinh viên có thể lưu
 */
void themSinhVien(struct Student students[], int *count, int maxCount) {
    printf("\n=== THEM SINH VIEN MOI ===\n");
    
    // Kiểm tra danh sách đã đầy chưa
    if (*count >= maxCount) {
        printf("Loi: Danh sach da day! Khong the them sinh vien moi.\n");
        return;
    }
    
    struct Student newStudent;
    inputStudent(&newStudent);
    
    // Kiểm tra ID hợp lệ
    if (newStudent.id <= 0) {
        printf("Loi: ID khong hop le! ID phai la so duong.\n");
        return;
    }
    
    // Kiểm tra ID trùng
    if (isIDExists(students, *count, newStudent.id)) {
        printf("Loi: ID %d da ton tai trong danh sach! Khong the them sinh vien trung ID.\n", newStudent.id);
        return;
    }
    
    // Thêm sinh viên vào cuối danh sách
    students[*count] = newStudent;
    (*count)++;
    
    printf("Da them thanh cong sinh vien: ID=%d, Ten=%s\n", newStudent.id, newStudent.name);
}

/**
 * CHỨC NĂNG 8: Xóa sinh viên theo ID
 * 
 * MÔ TẢ:
 * Tìm và xóa sinh viên có ID trùng với ID được nhập khỏi danh sách.
 * Sau khi xóa, các sinh viên phía sau sẽ được dịch chuyển lên.
 * 
 * @param students Mảng chứa danh sách sinh viên (sẽ được cập nhật)
 * @param count Con trỏ đến số lượng sinh viên (sẽ được giảm xuống)
 */
void xoaSinhVien(struct Student students[], int *count) {
    printf("\n=== XOA SINH VIEN ===\n");
    
    if (*count <= 0) {
        printf("Danh sach rong! Khong co sinh vien nao de xoa.\n");
        return;
    }
    
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    
    // Kiểm tra ID hợp lệ
    if (id <= 0) {
        printf("Loi: ID khong hop le! ID phai la so duong.\n");
        return;
    }
    
    // Tìm vị trí của sinh viên cần xóa
    int foundIndex = -1;
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            foundIndex = i;
            break;
        }
    }
    
    // Kiểm tra có tìm thấy không
    if (foundIndex == -1) {
        printf("Loi: Khong tim thay sinh vien co ID = %d trong danh sach!\n", id);
        return;
    }
    
    // Dịch chuyển các sinh viên phía sau lên 1 vị trí
    for (int i = foundIndex; i < *count - 1; i++) {
        students[i] = students[i + 1];
    }
    
    // Giảm số lượng sinh viên
    (*count)--;
    
    printf("Da xoa thanh cong sinh vien co ID = %d! So luong sinh vien con lai: %d\n", id, *count);
}

/**
 * CHỨC NĂNG: Khởi tạo dữ liệu mẫu (10 sinh viên giả lập)
 * 
 * MÔ TẢ:
 * Tạo sẵn 10 sinh viên mẫu với thông tin đa dạng để test chương trình.
 * 
 * @param students Mảng để lưu sinh viên mẫu (sẽ được cập nhật)
 * @param count Con trỏ đến số lượng sinh viên (sẽ được set = 10)
 */
void khoiTaoDuLieuMau(struct Student students[], int *count) {
    struct Student sampleStudents[10] = {
        {1, "Nguyen Van An", 20, 3.75},
        {2, "Tran Thi Binh", 21, 3.85},
        {3, "Le Van Cuong", 19, 3.65},
        {4, "Pham Thi Dung", 22, 4.00},
        {5, "Hoang Van Em", 20, 2.50},
        {6, "Vu Thi Phuong", 21, 3.50},
        {7, "Dao Van Giang", 19, 3.90},
        {8, "Bui Thi Hoa", 20, 2.75},
        {9, "Ngo Van Inh", 22, 3.60},
        {10, "Dinh Thi Kieu", 21, 3.85}
    };
    
    for (int i = 0; i < 10; i++) {
        students[i] = sampleStudents[i];
    }
    
    *count = 10;
    printf("Da khoi tao thanh cong 10 sinh vien mau!\n");
}

/**
 * CHỨC NĂNG: Hiển thị menu chính
 * 
 * MÔ TẢ:
 * In ra màn hình menu với các chức năng có sẵn.
 */
void hienThiMenu() {
    printf("\n");
    printf("========================================\n");
    printf("==== Student Manager ====\n");
    printf("========================================\n");
    printf("1. Nhap sinh vien\n");
    printf("2. In danh sach\n");
    printf("3. Ghi file\n");
    printf("4. Doc file\n");
    printf("5. Tim kiem\n");
    printf("6. Sap xep\n");
    printf("7. Them sinh vien\n");
    printf("8. Xoa sinh vien\n");
    printf("0. Thoat\n");
    printf("========================================\n");
    printf("Chon chuc nang: ");
}

// ============================================================================
// HÀM MAIN - LUỒNG CHẠY CHƯƠNG TRÌNH
// ============================================================================

/**
 * LUỒNG CHẠY CHƯƠNG TRÌNH:
 * 
 * 1. KHỞI TẠO:
 *    - Khai báo mảng students để lưu danh sách sinh viên (tối đa 100)
 *    - Khai báo biến count để đếm số lượng sinh viên hiện tại
 *    - Khởi tạo dữ liệu mẫu (10 sinh viên) để test
 * 
 * 2. VÒNG LẶP MENU:
 *    - Hiển thị menu với các chức năng
 *    - Đọc lựa chọn của người dùng
 *    - Xử lý từng chức năng tương ứng:
 *      * 1: Nhập sinh viên mới từ bàn phím
 *      * 2: In danh sách sinh viên ra màn hình
 *      * 3: Ghi danh sách vào file
 *      * 4: Đọc danh sách từ file
 *      * 5: Tìm kiếm sinh viên theo ID
 *      * 6: Sắp xếp danh sách theo GPA giảm dần
 *      * 7: Thêm sinh viên mới vào danh sách
 *      * 8: Xóa sinh viên theo ID
 *      * 0: Thoát chương trình
 *    - Lặp lại cho đến khi người dùng chọn 0 (Thoát)
 * 
 * 3. KẾT THÚC:
 *    - Hiển thị thông báo cảm ơn
 *    - Trả về 0 để kết thúc chương trình
 */
int main() {
    // ========================================================================
    // KHỞI TẠO CHƯƠNG TRÌNH
    // ========================================================================
    struct Student students[100]; // Mảng lưu tối đa 100 sinh viên
    int count = 0;                // Số lượng sinh viên hiện tại
    int choice;                   // Lựa chọn của người dùng
    
    printf("=== CHUONG TRINH QUAN LY SINH VIEN ===\n");
    printf("Khoi tao du lieu mau...\n");
    
    // Khởi tạo 10 sinh viên mẫu để test
    khoiTaoDuLieuMau(students, &count);
    
    printf("\nDanh sach sinh vien ban dau:\n");
    printStudents(students, count);
    
    // ========================================================================
    // VÒNG LẶP MENU CHÍNH
    // ========================================================================
    do {
        // Hiển thị menu
        hienThiMenu();
        
        // Đọc lựa chọn của người dùng
        scanf("%d", &choice);
        getchar(); // Xóa ký tự xuống dòng còn lại
        
        // Xử lý từng chức năng
        switch (choice) {
            case 1:
                // CHỨC NĂNG 1: Nhập sinh viên từ bàn phím
                nhapSinhVien(students, &count, 100);
                break;
                
            case 2:
                // CHỨC NĂNG 2: In danh sách sinh viên
                inDanhSach(students, count);
                break;
                
            case 3:
                // CHỨC NĂNG 3: Ghi danh sách vào file
                ghiFile(students, count);
                break;
                
            case 4:
                // CHỨC NĂNG 4: Đọc danh sách từ file
                docFile(students, &count, 100);
                break;
                
            case 5:
                // CHỨC NĂNG 5: Tìm kiếm sinh viên theo ID
                timKiem(students, count);
                break;
                
            case 6:
                // CHỨC NĂNG 6: Sắp xếp danh sách theo GPA giảm dần
                sapXep(students, count);
                break;
                
            case 7:
                // CHỨC NĂNG 7: Thêm sinh viên mới vào danh sách
                themSinhVien(students, &count, 100);
                break;
                
            case 8:
                // CHỨC NĂNG 8: Xóa sinh viên theo ID
                xoaSinhVien(students, &count);
                break;
                
            case 0:
                // THOÁT CHƯƠNG TRÌNH
                printf("\nCam on ban da su dung chuong trinh!\n");
                printf("Hen gap lai!\n");
                break;
                
            default:
                // Lựa chọn không hợp lệ
                printf("Lua chon khong hop le! Vui long chon lai.\n");
                break;
        }
        
        // Tạm dừng để người dùng xem kết quả (trừ khi chọn thoát)
        if (choice != 0) {
            printf("\nNhan Enter de tiep tuc...");
            getchar();
        }
        
    } while (choice != 0); // Lặp lại cho đến khi chọn 0 (Thoát)
    
    // ========================================================================
    // KẾT THÚC CHƯƠNG TRÌNH
    // ========================================================================
    return 0;
}

