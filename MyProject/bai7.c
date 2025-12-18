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
 * Sắp xếp danh sách sinh viên theo GPA giảm dần sử dụng thuật toán Bubble Sort
 * 
 * THUẬT TOÁN BUBBLE SORT:
 * - Ý tưởng: So sánh từng cặp phần tử liền kề và đổi chỗ nếu chúng không đúng thứ tự
 * - Cách hoạt động:
 *   1. Duyệt qua mảng từ đầu đến cuối
 *   2. So sánh phần tử hiện tại với phần tử kế tiếp
 *   3. Nếu phần tử trước < phần tử sau (theo thứ tự giảm dần), đổi chỗ chúng
 *   4. Lặp lại cho đến khi không còn cặp nào cần đổi chỗ
 * 
 * - Độ phức tạp: O(n²) trong trường hợp xấu nhất
 * - Ưu điểm: Dễ hiểu, dễ implement, ổn định (stable)
 * - Nhược điểm: Chậm với dữ liệu lớn
 * 
 * LOGIC CỤ THỂ:
 * - Vòng lặp ngoài (i): Chạy từ 0 đến count-1, đảm bảo phần tử lớn nhất "nổi" lên trên
 * - Vòng lặp trong (j): So sánh từng cặp phần tử liền kề
 * - Điều kiện đổi chỗ: students[j].gpa < students[j+1].gpa (sắp xếp giảm dần)
 * - Nếu điều kiện đúng, đổi chỗ toàn bộ struct Student
 * 
 * @param students Mảng chứa danh sách sinh viên cần sắp xếp
 * @param count Số lượng sinh viên trong mảng
 * 
 * @note Hàm sẽ sắp xếp trực tiếp trên mảng students (in-place sorting)
 * @note Nếu có nhiều sinh viên có cùng GPA, thứ tự ban đầu sẽ được giữ nguyên (stable sort)
 * 
 * @example
 *   struct Student students[3] = {{1, "An", 20, 3.5}, {2, "Binh", 21, 3.8}, {3, "Cuong", 19, 3.2}};
 *   sortByGPADescending(students, 3);
 *   // Sau khi sắp xếp: Binh (3.8) -> An (3.5) -> Cuong (3.2)
 */
void sortByGPADescending(struct Student students[], int count) {
    // Kiểm tra danh sách rỗng hoặc chỉ có 1 phần tử
    if (count <= 1 || students == NULL) {
        return; // Không cần sắp xếp
    }
    
    // Bubble Sort: Sắp xếp giảm dần theo GPA
    // Vòng lặp ngoài: Chạy count-1 lần
    for (int i = 0; i < count - 1; i++) {
        // Biến cờ để tối ưu: Nếu không có đổi chỗ nào trong vòng lặp này, mảng đã được sắp xếp
        int swapped = 0;
        
        // Vòng lặp trong: So sánh từng cặp phần tử liền kề
        // count - 1 - i: Giảm số lần so sánh vì phần tử lớn nhất đã "nổi" lên trên
        for (int j = 0; j < count - 1 - i; j++) {
            // So sánh GPA: Nếu GPA của phần tử trước < GPA của phần tử sau
            if (students[j].gpa < students[j + 1].gpa) {
                // Đổi chỗ hai phần tử
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
                swapped = 1; // Đánh dấu đã có đổi chỗ
            }
        }
        
        // Tối ưu: Nếu không có đổi chỗ nào, mảng đã được sắp xếp, dừng sớm
        if (swapped == 0) {
            break;
        }
    }
}

/**
 * Tính GPA trung bình của danh sách sinh viên
 * 
 * @param students Mảng chứa danh sách sinh viên
 * @param count Số lượng sinh viên trong mảng
 * @return GPA trung bình (float). Trả về -1.0 nếu danh sách rỗng hoặc count <= 0
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

// Hàm copy mảng sinh viên (để test không làm thay đổi dữ liệu gốc)
void copyStudents(struct Student dest[], struct Student src[], int count) {
    for (int i = 0; i < count; i++) {
        dest[i] = src[i];
    }
}

// Hàm kiểm tra mảng đã được sắp xếp giảm dần theo GPA chưa
int isSortedDescending(struct Student students[], int count) {
    if (count <= 1) {
        return 1; // Mảng rỗng hoặc 1 phần tử được coi là đã sắp xếp
    }
    
    for (int i = 0; i < count - 1; i++) {
        if (students[i].gpa < students[i + 1].gpa) {
            return 0; // Không sắp xếp đúng
        }
    }
    
    return 1; // Đã sắp xếp đúng
}

// Hàm test sắp xếp theo GPA
void testSortByGPADescending() {
    printf("\n=== TEST SAP XEP THEO GPA GIAM DAN ===\n\n");
    
    // Test case 1: GPA bằng nhau
    printf("Test case 1: Danh sach voi GPA bang nhau\n");
    struct Student students1[5] = {
        {1, "Nguyen Van An", 20, 3.50},
        {2, "Tran Thi Binh", 21, 3.50},
        {3, "Le Van Cuong", 19, 3.50},
        {4, "Pham Thi Dung", 22, 3.50},
        {5, "Hoang Van Em", 20, 3.50}
    };
    
    struct Student test1[5];
    copyStudents(test1, students1, 5);
    
    printf("Danh sach truoc khi sap xep:\n");
    printStudents(test1, 5);
    
    sortByGPADescending(test1, 5);
    
    printf("\nDanh sach sau khi sap xep:\n");
    printStudents(test1, 5);
    
    if (isSortedDescending(test1, 5)) {
        printf(" Test case 1: THANH CONG - Sap xep dung (GPA bang nhau, giu nguyen thu tu)!\n");
    } else {
        printf(" Test case 1: THAT BAI - Sap xep khong dung!\n");
    }
    
    printf("\n");
    
    // Test case 2: GPA tăng dần sẵn (cần đảo ngược)
    printf("Test case 2: Danh sach voi GPA tang dan san (can dao nguoc)\n");
    struct Student students2[5] = {
        {1, "Nguyen Van An", 20, 2.00},      // GPA thấp nhất
        {2, "Tran Thi Binh", 21, 2.50},
        {3, "Le Van Cuong", 19, 3.00},
        {4, "Pham Thi Dung", 22, 3.50},
        {5, "Hoang Van Em", 20, 4.00}        // GPA cao nhất
    };
    
    struct Student test2[5];
    copyStudents(test2, students2, 5);
    
    printf("Danh sach truoc khi sap xep (GPA tang dan):\n");
    printStudents(test2, 5);
    
    sortByGPADescending(test2, 5);
    
    printf("\nDanh sach sau khi sap xep (GPA giam dan):\n");
    printStudents(test2, 5);
    
    if (isSortedDescending(test2, 5)) {
        printf(" Test case 2: THANH CONG - Sap xep dung (dao nguoc tu tang dan sang giam dan)!\n");
    } else {
        printf(" Test case 2: THAT BAI - Sap xep khong dung!\n");
    }
    
    printf("\n");
    
    // Test case 3: GPA ngẫu nhiên
    printf("Test case 3: Danh sach voi GPA ngau nhien\n");
    struct Student students3[10] = {
        {1, "Nguyen Van An", 20, 2.50},
        {2, "Tran Thi Binh", 21, 3.25},
        {3, "Le Van Cuong", 19, 3.75},
        {4, "Pham Thi Dung", 22, 4.00},
        {5, "Hoang Van Em", 20, 2.00},
        {6, "Vu Thi Phuong", 21, 3.50},
        {7, "Dao Van Giang", 19, 3.90},
        {8, "Bui Thi Hoa", 20, 2.75},
        {9, "Ngo Van Inh", 22, 3.60},
        {10, "Dinh Thi Kieu", 21, 3.85}
    };
    
    struct Student test3[10];
    copyStudents(test3, students3, 10);
    
    printf("Danh sach truoc khi sap xep (GPA ngau nhien):\n");
    printStudents(test3, 10);
    
    sortByGPADescending(test3, 10);
    
    printf("\nDanh sach sau khi sap xep (GPA giam dan):\n");
    printStudents(test3, 10);
    
    if (isSortedDescending(test3, 10)) {
        printf(" Test case 3: THANH CONG - Sap xep dung (GPA ngau nhien)!\n");
    } else {
        printf(" Test case 3: THAT BAI - Sap xep khong dung!\n");
    }
    
    // Kiểm tra thứ tự cụ thể
    printf("\nKiem tra thu tu cu the:\n");
    int correct = 1;
    float expected[] = {4.00, 3.90, 3.85, 3.75, 3.60, 3.50, 3.25, 2.75, 2.50, 2.00};
    for (int i = 0; i < 10; i++) {
        if (test3[i].gpa != expected[i]) {
            correct = 0;
            break;
        }
    }
    
    if (correct) {
        printf("✓ Thu tu GPA dung: 4.00 -> 3.90 -> 3.85 -> 3.75 -> 3.60 -> 3.50 -> 3.25 -> 2.75 -> 2.50 -> 2.00\n");
    } else {
        printf("✗ Thu tu GPA khong dung!\n");
    }
    
    printf("\n");
    
    // Test case 4: Danh sách rỗng
    printf("Test case 4: Danh sach rong\n");
    struct Student empty[10];
    sortByGPADescending(empty, 0);
    printf("✓ Test case 4: THANH CONG - Xu ly dung truong hop danh sach rong!\n");
    
    printf("\n");
    
    // Test case 5: Danh sách có 1 phần tử
    printf("Test case 5: Danh sach co 1 phan tu\n");
    struct Student single[1] = {{1, "Test Student", 20, 3.75}};
    struct Student test5[1];
    copyStudents(test5, single, 1);
    
    sortByGPADescending(test5, 1);
    
    if (test5[0].gpa == 3.75) {
        printf(" Test case 5: THANH CONG - Xu ly dung truong hop 1 phan tu!\n");
    } else {
        printf(" Test case 5: THAT BAI - Xu ly khong dung!\n");
    }
}

int main() {
    struct Student students[100];
    int count = 10;
    
    printf("=== CHUONG TRINH QUAN LY SINH VIEN ===\n");
    printf("=== SAP XEP THEO GPA GIAM DAN ===\n");
    
    // Khởi tạo 10 sinh viên mẫu với GPA khác nhau
    struct Student sampleStudents[10] = {
        {1, "Nguyen Van An", 20, 2.50},
        {2, "Tran Thi Binh", 21, 3.25},
        {3, "Le Van Cuong", 19, 3.75},
        {4, "Pham Thi Dung", 22, 4.00},
        {5, "Hoang Van Em", 20, 2.00},
        {6, "Vu Thi Phuong", 21, 3.50},
        {7, "Dao Van Giang", 19, 3.90},
        {8, "Bui Thi Hoa", 20, 2.75},
        {9, "Ngo Van Inh", 22, 3.60},
        {10, "Dinh Thi Kieu", 21, 3.85}
    };
    
    for (int i = 0; i < count; i++) {
        students[i] = sampleStudents[i];
    }
    
    // In danh sách trước khi sắp xếp
    printf("\n=== DANH SACH SINH VIEN TRUOC KHI SAP XEP ===\n");
    printStudents(students, count);
    
    // Sắp xếp theo GPA giảm dần
    sortByGPADescending(students, count);
    
    // In danh sách sau khi sắp xếp
    printf("\n=== DANH SACH SINH VIEN SAU KHI SAP XEP (GPA GIAM DAN) ===\n");
    printStudents(students, count);
    
    // Tính và hiển thị GPA trung bình
    float avgGPA = calculateAverageGPA(students, count);
    if (avgGPA >= 0) {
        printf("\n=== KET QUA ===\n");
        printf("GPA trung binh cua %d sinh vien: %.2f\n", count, avgGPA);
    }
    
    // Chạy các test case
    testSortByGPADescending();
    
    return 0;
}

