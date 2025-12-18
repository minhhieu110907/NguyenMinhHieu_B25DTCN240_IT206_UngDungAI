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
 * Lưu danh sách sinh viên vào file với định dạng CSV
 * 
 * BƯỚC XỬ LÝ FILE:
 * 1. Mở file ở chế độ ghi (write mode) - "w"
 * 2. Kiểm tra file có mở thành công không
 * 3. Ghi số lượng sinh viên vào dòng đầu tiên
 * 4. Ghi thông tin từng sinh viên (mỗi dòng: id,name,age,gpa)
 * 5. Đóng file để đảm bảo dữ liệu được ghi vào đĩa
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param count Số lượng sinh viên
 * @param filename Tên file cần ghi (ví dụ: "classA.txt")
 * @return 1 nếu thành công, 0 nếu thất bại
 */
int saveToFile(struct Student students[], int count, const char *filename) {
    // BƯỚC 1: Mở file ở chế độ ghi
    // "w" = write mode: Tạo file mới hoặc ghi đè file cũ nếu đã tồn tại
    FILE *file = fopen(filename, "w");
    
    // BƯỚC 2: Kiểm tra file có mở thành công không
    // Nếu file == NULL, có nghĩa là không thể mở file (lỗi quyền truy cập, đĩa đầy, ...)
    if (file == NULL) {
        printf("Loi: Khong the mo file %s de ghi!\n", filename);
        return 0; // Trả về 0 để báo lỗi
    }
    
    // BƯỚC 3: Ghi số lượng sinh viên vào dòng đầu tiên
    // Điều này giúp khi đọc file, ta biết trước có bao nhiêu sinh viên
    fprintf(file, "%d\n", count);
    
    // BƯỚC 4: Ghi thông tin từng sinh viên
    // Mỗi dòng chứa: id,name,age,gpa (định dạng CSV - Comma Separated Values)
    for (int i = 0; i < count; i++) {
        // fprintf ghi dữ liệu vào file theo định dạng
        // %.2f để hiển thị GPA với 2 chữ số thập phân
        fprintf(file, "%d,%s,%d,%.2f\n",
                students[i].id,
                students[i].name,
                students[i].age,
                students[i].gpa);
    }
    
    // BƯỚC 5: Đóng file
    // Quan trọng: Phải đóng file để đảm bảo dữ liệu được ghi vào đĩa
    // Nếu không đóng file, dữ liệu có thể chỉ nằm trong buffer và chưa được ghi
    fclose(file);
    
    return 1; // Trả về 1 để báo thành công
}

/**
 * Đọc danh sách sinh viên từ file
 * 
 * BƯỚC XỬ LÝ ĐỌC FILE:
 * 1. Mở file ở chế độ đọc (read mode) - "r"
 * 2. Kiểm tra file có mở thành công không (file có tồn tại không)
 * 3. Đọc số lượng sinh viên từ dòng đầu tiên
 * 4. Kiểm tra số lượng hợp lệ (không âm, không vượt quá maxCount)
 * 5. Đọc từng dòng thông tin sinh viên
 * 6. Parse (phân tích) từng dòng để tách các trường: id, name, age, gpa
 * 7. Lưu vào mảng students
 * 8. Đóng file
 * 
 * @param students Mảng để lưu sinh viên đọc được
 * @param maxCount Số lượng tối đa sinh viên có thể đọc
 * @param filename Tên file cần đọc (ví dụ: "classA.txt")
 * @return Số lượng sinh viên đọc được, 0 nếu lỗi
 */
int loadFromFile(struct Student students[], int maxCount, const char *filename) {
    // BƯỚC 1: Mở file ở chế độ đọc
    // "r" = read mode: Chỉ đọc, không ghi. File phải tồn tại.
    FILE *file = fopen(filename, "r");
    
    // BƯỚC 2: Kiểm tra file có mở thành công không
    // Nếu file == NULL, có nghĩa là file không tồn tại hoặc không có quyền đọc
    if (file == NULL) {
        printf("Loi: Khong the mo file %s de doc!\n", filename);
        printf("Kiem tra lai ten file hoac duong dan file.\n");
        return 0; // Trả về 0 để báo lỗi
    }
    
    // BƯỚC 3: Đọc số lượng sinh viên từ dòng đầu tiên
    int count;
    // fscanf đọc dữ liệu từ file theo định dạng
    // Nếu đọc không thành công (không đúng định dạng), trả về số khác 1
    if (fscanf(file, "%d\n", &count) != 1) {
        printf("Loi: Khong the doc so luong sinh vien tu file %s!\n", filename);
        fclose(file); // Đóng file trước khi return
        return 0;
    }
    
    // BƯỚC 4: Kiểm tra số lượng hợp lệ
    // Đảm bảo số lượng không âm và không vượt quá kích thước mảng
    if (count < 0 || count > maxCount) {
        printf("Loi: So luong sinh vien khong hop le! (toi da %d, nhung file co %d)\n", maxCount, count);
        fclose(file);
        return 0;
    }
    
    // BƯỚC 5: Đọc thông tin từng sinh viên
    for (int i = 0; i < count; i++) {
        // Đọc một dòng từ file vào buffer
        char line[200]; // Buffer để lưu một dòng
        // fgets đọc một dòng từ file (tối đa 200 ký tự)
        // Nếu đọc không thành công (hết file sớm), trả về NULL
        if (fgets(line, sizeof(line), file) == NULL) {
            printf("Loi: Khong the doc thong tin sinh vien thu %d tu file %s!\n", i + 1, filename);
            fclose(file);
            return 0;
        }
        
        // BƯỚC 6: Parse (phân tích) dòng để tách các trường
        // Dòng có định dạng: id,name,age,gpa
        // Sử dụng strtok để tách chuỗi theo dấu phẩy
        
        char *token;
        char *rest = line; // Con trỏ đến phần còn lại của chuỗi
        
        // Parse ID: Tách phần đầu tiên trước dấu phẩy
        token = strtok(rest, ",");
        if (token == NULL) {
            printf("Loi: Khong the phan tich ID cua sinh vien thu %d!\n", i + 1);
            fclose(file);
            return 0;
        }
        // atoi chuyển chuỗi thành số nguyên
        students[i].id = atoi(token);
        
        // Parse Name: Tách phần thứ hai
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Loi: Khong the phan tich Name cua sinh vien thu %d!\n", i + 1);
            fclose(file);
            return 0;
        }
        // strcpy sao chép chuỗi vào mảng name
        strcpy(students[i].name, token);
        
        // Parse Age: Tách phần thứ ba
        token = strtok(NULL, ",");
        if (token == NULL) {
            printf("Loi: Khong the phan tich Age cua sinh vien thu %d!\n", i + 1);
            fclose(file);
            return 0;
        }
        students[i].age = atoi(token);
        
        // Parse GPA: Tách phần cuối (trước ký tự xuống dòng)
        token = strtok(NULL, "\n");
        if (token == NULL) {
            printf("Loi: Khong the phan tich GPA cua sinh vien thu %d!\n", i + 1);
            fclose(file);
            return 0;
        }
        // atof chuyển chuỗi thành số thực (float)
        students[i].gpa = atof(token);
    }
    
    // BƯỚC 7: Đóng file sau khi đọc xong
    fclose(file);
    
    // BƯỚC 8: Trả về số lượng sinh viên đọc được
    return count;
}

/**
 * Tạo dữ liệu giả lập cho một lớp học và lưu vào file
 * 
 * BƯỚC XỬ LÝ:
 * 1. Tạo mảng sinh viên mẫu với thông tin đa dạng
 * 2. Gọi hàm saveToFile để lưu vào file
 * 3. Thông báo kết quả
 * 
 * @param filename Tên file cần tạo (ví dụ: "classA.txt")
 * @param className Tên lớp (để hiển thị)
 */
void createSampleClassData(const char *filename, const char *className) {
    // Tạo dữ liệu mẫu cho lớp
    // Mỗi lớp có số lượng và phân bố GPA khác nhau để dễ phân biệt
    
    struct Student students[10];
    int count = 10;
    
    // Tạo dữ liệu khác nhau cho từng lớp
    if (strcmp(className, "A") == 0) {
        // Lớp A: Học sinh giỏi, GPA cao
        struct Student classA[10] = {
            {101, "Nguyen Van An", 20, 3.85},
            {102, "Tran Thi Binh", 21, 3.90},
            {103, "Le Van Cuong", 19, 3.75},
            {104, "Pham Thi Dung", 22, 4.00},
            {105, "Hoang Van Em", 20, 3.80},
            {106, "Vu Thi Phuong", 21, 3.95},
            {107, "Dao Van Giang", 19, 3.70},
            {108, "Bui Thi Hoa", 20, 3.88},
            {109, "Ngo Van Inh", 22, 3.92},
            {110, "Dinh Thi Kieu", 21, 3.85}
        };
        for (int i = 0; i < count; i++) {
            students[i] = classA[i];
        }
    } else if (strcmp(className, "B") == 0) {
        // Lớp B: Học sinh trung bình, GPA đa dạng
        struct Student classB[10] = {
            {201, "Le Van Anh", 20, 2.50},
            {202, "Tran Van Binh", 21, 3.25},
            {203, "Nguyen Thi Cuong", 19, 3.00},
            {204, "Pham Van Dung", 22, 2.75},
            {205, "Hoang Thi Em", 20, 3.50},
            {206, "Vu Van Phuong", 21, 2.90},
            {207, "Dao Thi Giang", 19, 3.30},
            {208, "Bui Van Hoa", 20, 2.80},
            {209, "Ngo Thi Inh", 22, 3.15},
            {210, "Dinh Van Kieu", 21, 3.40}
        };
        for (int i = 0; i < count; i++) {
            students[i] = classB[i];
        }
    } else if (strcmp(className, "C") == 0) {
        // Lớp C: Học sinh cần cải thiện, GPA thấp hơn
        struct Student classC[10] = {
            {301, "Tran Van An", 20, 2.00},
            {302, "Le Thi Binh", 21, 2.30},
            {303, "Nguyen Van Cuong", 19, 2.50},
            {304, "Pham Thi Dung", 22, 2.20},
            {305, "Hoang Van Em", 20, 2.40},
            {306, "Vu Thi Phuong", 21, 2.10},
            {307, "Dao Van Giang", 19, 2.60},
            {308, "Bui Thi Hoa", 20, 2.25},
            {309, "Ngo Van Inh", 22, 2.35},
            {310, "Dinh Thi Kieu", 21, 2.45}
        };
        for (int i = 0; i < count; i++) {
            students[i] = classC[i];
        }
    }
    
    // Lưu dữ liệu vào file
    if (saveToFile(students, count, filename)) {
        printf("Da tao thanh cong du lieu cho lop %s vao file %s (%d sinh vien)\n", 
               className, filename, count);
    } else {
        printf("Loi: Khong the tao du lieu cho lop %s!\n", className);
    }
}

/**
 * Tạo dữ liệu giả lập cho tất cả các lớp
 * 
 * BƯỚC XỬ LÝ NHIỀU FILE:
 * 1. Tạo dữ liệu cho từng lớp
 * 2. Mỗi lớp được lưu vào file riêng biệt
 * 3. Các file độc lập với nhau, có thể đọc riêng lẻ
 */
void createAllSampleClasses() {
    printf("\n=== TAO DU LIEU GIA LAP CHO CAC LOP ===\n");
    
    // Tạo dữ liệu cho lớp A
    createSampleClassData("classA.txt", "A");
    
    // Tạo dữ liệu cho lớp B
    createSampleClassData("classB.txt", "B");
    
    // Tạo dữ liệu cho lớp C
    createSampleClassData("classC.txt", "C");
    
    printf("\nDa tao xong du lieu cho 3 lop: classA.txt, classB.txt, classC.txt\n");
}

/**
 * Nhập tên file từ người dùng
 * 
 * BƯỚC XỬ LÝ NHẬP LIỆU:
 * 1. Hiển thị danh sách file có sẵn
 * 2. Yêu cầu người dùng nhập tên file
 * 3. Kiểm tra tên file hợp lệ
 * 4. Trả về tên file
 * 
 * @param filename Buffer để lưu tên file (tối đa 100 ký tự)
 */
void inputFileName(char *filename) {
    printf("\n=== CHON FILE DE DOC ===\n");
    printf("Cac file co san:\n");
    printf("  - classA.txt (Lop A - Hoc sinh gioi)\n");
    printf("  - classB.txt (Lop B - Hoc sinh trung binh)\n");
    printf("  - classC.txt (Lop C - Hoc sinh can cai thien)\n");
    printf("\nNhap ten file (vi du: classA.txt): ");
    
    // Đọc tên file từ bàn phím
    // fgets đọc cả dòng, bao gồm cả ký tự xuống dòng
    fgets(filename, 100, stdin);
    
    // Xóa ký tự xuống dòng ở cuối (nếu có)
    // strcspn tìm vị trí của ký tự xuống dòng
    int len = strcspn(filename, "\n");
    filename[len] = '\0'; // Thay ký tự xuống dòng bằng ký tự kết thúc chuỗi
    
    printf("Ban da chon file: %s\n", filename);
}

/**
 * Xử lý đọc và hiển thị dữ liệu từ file được chọn
 * 
 * BƯỚC XỬ LÝ TỔNG HỢP:
 * 1. Nhập tên file từ người dùng
 * 2. Đọc dữ liệu từ file
 * 3. Kiểm tra dữ liệu đọc được
 * 4. Hiển thị danh sách sinh viên
 * 5. Sắp xếp và tính toán thống kê
 * 6. Hiển thị kết quả
 */
void processSelectedClass() {
    char filename[100];
    struct Student students[100];
    int count;
    
    // BƯỚC 1: Nhập tên file từ người dùng
    inputFileName(filename);
    
    // BƯỚC 2: Đọc dữ liệu từ file
    printf("\nDang doc du lieu tu file %s...\n", filename);
    count = loadFromFile(students, 100, filename);
    
    // BƯỚC 3: Kiểm tra dữ liệu đọc được
    if (count > 0) {
        printf("Da doc thanh cong %d sinh vien tu file %s!\n", count, filename);
        
        // BƯỚC 4: Hiển thị danh sách sinh viên
        printf("\n=== DANH SACH SINH VIEN ===\n");
        printStudents(students, count);
        
        // BƯỚC 5: Sắp xếp theo GPA giảm dần
        sortByGPADescending(students, count);
        
        // BƯỚC 6: Hiển thị danh sách sau khi sắp xếp
        printf("\n=== DANH SACH SINH VIEN SAU KHI SAP XEP (GPA GIAM DAN) ===\n");
        printStudents(students, count);
        
        // BƯỚC 7: Tính và hiển thị thống kê
        float avgGPA = calculateAverageGPA(students, count);
        if (avgGPA >= 0) {
            printf("\n=== THONG KE ===\n");
            printf("So luong sinh vien: %d\n", count);
            printf("GPA trung binh: %.2f\n", avgGPA);
            printf("GPA cao nhat: %.2f\n", students[0].gpa);
            printf("GPA thap nhat: %.2f\n", students[count - 1].gpa);
        }
    } else {
        printf("Khong the doc duoc du lieu tu file %s!\n", filename);
        printf("Vui long kiem tra:\n");
        printf("  - Ten file co dung khong?\n");
        printf("  - File co ton tai khong?\n");
        printf("  - Chay chuc nang tao du lieu mau truoc.\n");
    }
}

int main() {
    int choice;
    
    printf("=== CHUONG TRINH QUAN LY NHIEU LOP HOC ===\n");
    printf("Moi lop co file rieng: classA.txt, classB.txt, classC.txt\n\n");
    
    do {
        printf("\n=== MENU ===\n");
        printf("1. Tao du lieu gia lap cho 3 lop\n");
        printf("2. Doc du lieu tu file (nhap ten file)\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        
        scanf("%d", &choice);
        getchar(); // Xóa ký tự xuống dòng còn lại
        
        switch (choice) {
            case 1:
                // Tạo dữ liệu giả lập cho tất cả các lớp
                createAllSampleClasses();
                break;
                
            case 2:
                // Đọc và xử lý dữ liệu từ file được chọn
                processSelectedClass();
                break;
                
            case 3:
                printf("Cam on ban da su dung chuong trinh!\n");
                break;
                
            default:
                printf("Lua chon khong hop le! Vui long chon lai.\n");
                break;
        }
    } while (choice != 3);
    
    return 0;
}

