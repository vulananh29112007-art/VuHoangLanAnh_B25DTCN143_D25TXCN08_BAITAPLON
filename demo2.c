#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLASSES 100
#define MAX_STUDENTS 1000
#define MAX_NAME 100


typedef struct {
    char classId[20];
    char className[MAX_NAME];
    char major[MAX_NAME];
    char type[20]; // CNTT/NGOAI NGU 
} Classroom;

typedef struct {
    char studentId[20];
    char name[MAX_NAME];
    char birthDate[12]; // dd/mm/yyyy
    char email[50];
    char phone[15];
} Student;


typedef struct {
    void (*display)(void* self);
    void (*add)(void* self);
    void (*delete)(void* self);
    void (*update)(void* self);
} Manageable;

// ------------------- quan li lop hoc -------------------

typedef struct {
    Manageable base;            // ke thua
    Classroom classes[MAX_CLASSES];
    int classCount;
} ClassManager;

void class_display(void* self);
void class_add(void* self);
void class_delete(void* self);
void class_update(void* self);

ClassManager classManager = {
    {class_display, class_add, class_delete, class_update},
    {}, 0
};

// ------------------- QUAN LI SINH VIÊN -------------------

typedef struct {
    Manageable base;            // Ke thua
    Student students[MAX_STUDENTS];
    int studentCount;
} StudentManager;

void student_display(void* self);
void student_add(void* self);
void student_delete(void* self);
void student_update(void* self);

StudentManager studentManager = {
    {student_display, student_add, student_delete, student_update},
    {}, 0
};

// ------------------- trien khai -------------------

void class_display(void* self) {
    ClassManager* cm = (ClassManager*)self;
    printf("\n=== DANH SACH LOP HOC (%d) ===\n", cm->classCount);
    printf("%-15s %-25s %-20s %-10s\n", "Ma lop", "Ten lop", "Chuyên ngành", "Loai");
    for (int i = 0; i < cm->classCount; i++) {
        printf("%-15s %-25s %-20s %-10s\n",
               cm->classes[i].classId,
               cm->classes[i].className,
               cm->classes[i].major,
               cm->classes[i].type);
    }
}

void class_add(void* self) {
    ClassManager* cm = (ClassManager*)self;
    if (cm->classCount >= MAX_CLASSES) {
        printf("Danh sach lop!\n");
        return;
    }
    Classroom c;
    printf("Nhap ma lop: ");
    scanf("%s", c.classId);
    printf("Nhap ten lop: ");
    getchar(); // clear buffer
    fgets(c.className, MAX_NAME, stdin);
    c.className[strcspn(c.className, "\n")] = 0;
    printf("Nhap chuyen nganh: ");
    fgets(c.major, MAX_NAME, stdin);
    c.major[strcspn(c.major, "\n")] = 0;
    printf("Nhap loai lop (CNTT / Ngoai ngu): ");
    scanf("%s", c.type);

    cm->classes[cm->classCount++] = c;
    printf("Them lop thanh cong!\n");
}

void class_delete(void* self) {
    ClassManager* cm = (ClassManager*)self;
    char id[20];
    printf("Nhap ma lop can xoa: ");
    scanf("%s", id);
    for (int i = 0; i < cm->classCount; i++) {
        if (strcmp(cm->classes[i].classId, id) == 0) {
            for (int j = i; j < cm->classCount - 1; j++) {
                cm->classes[j] = cm->classes[j + 1];
            }
            cm->classCount--;
            printf("Xoa lop thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay lop co ma %s\n", id);
}

void class_update(void* self) {
    ClassManager* cm = (ClassManager*)self;
    char id[20];
    printf("Nhap ma lop can cap nhat: ");
    scanf("%s", id);
    for (int i = 0; i < cm->classCount; i++) {
        if (strcmp(cm->classes[i].classId, id) == 0) {
            printf("Nhap ten lop moi: ");
            getchar();
            fgets(cm->classes[i].className, MAX_NAME, stdin);
            cm->classes[i].className[strcspn(cm->classes[i].className, "\n")] = 0;
            printf("Nhap chuyen nganh moi: ");
            fgets(cm->classes[i].major, MAX_NAME, stdin);
            cm->classes[i].major[strcspn(cm->classes[i].major, "\n")] = 0;
            printf("Nhap loai lop moi (CNTT / Ngo?i ng?): ");
            scanf("%s", cm->classes[i].type);
            printf("Cap nhat thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay lop!\n");
}

// ------------------- TRI?N KHAI CH?C NÃNG SINH VIÊN -------------------

void student_display(void* self) {
    StudentManager* sm = (StudentManager*)self;
    printf("\n=== DANH SACH SINH VIEN (%d) ===\n", sm->studentCount);
    printf("%-15s %-25s %-12s %-25s %-15s\n", "MSSV", "Ho ten", "Ngay sinh", "Email", "SÐT");
    for (int i = 0; i < sm->studentCount; i++) {
        printf("%-15s %-25s %-12s %-25s %-15s\n",
               sm->students[i].studentId,
               sm->students[i].name,
               sm->students[i].birthDate,
               sm->students[i].email,
               sm->students[i].phone);
    }
}

void student_add(void* self) {
    StudentManager* sm = (StudentManager*)self;
    if (sm->studentCount >= MAX_STUDENTS) {
        printf("Danh sach sinh vien !\n");
        return;
    }
    Student s;
    printf("Nhap ma sinh vien: ");
    scanf("%s", s.studentId);
    printf("Nhap ho ten: ");
    getchar();
    fgets(s.name, MAX_NAME, stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    printf("Nhap ngay sinh (dd/mm/yyyy): ");
    scanf("%s", s.birthDate);
    printf("Nhap email: ");
    scanf("%s", s.email);
    printf("Nhap so dien thoai: ");
    scanf("%s", s.phone);

    sm->students[sm->studentCount++] = s;
    printf("Them sinh vien thanh cong!\n");
}

void student_delete(void* self) {
    StudentManager* sm = (StudentManager*)self;
    char id[20];
    printf("Nhap ma sinh vien can xoa: ");
    scanf("%s", id);
    for (int i = 0; i < sm->studentCount; i++) {
        if (strcmp(sm->students[i].studentId, id) == 0) {
            for (int j = i; j < sm->studentCount - 1; j++) {
                sm->students[j] = sm->students[j + 1];
            }
            sm->studentCount--;
            printf("Xoa sinh vien thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien co ma %s\n", id);
}

void student_update(void* self) {
    StudentManager* sm = (StudentManager*)self;
    char id[20];
    printf("Nhap ma sinh vien can cap nhat: ");
    scanf("%s", id);
    for (int i = 0; i < sm->studentCount; i++) {
        if (strcmp(sm->students[i].studentId, id) == 0) {
            printf("Nhap ho ten moi: ");
            getchar();
            fgets(sm->students[i].name, MAX_NAME, stdin);
            sm->students[i].name[strcspn(sm->students[i].name, "\n")] = 0;
            printf("Nhap ngay sinh moi: ");
            scanf("%s", sm->students[i].birthDate);
            printf("Nhap email moi: ");
            scanf("%s", sm->students[i].email);
            printf("Nhap SDT moi: ");
            scanf("%s", sm->students[i].phone);
            printf("Cap nhat thanh cong!\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien!\n");
}

// ------------------- MENU -------------------

void menuClass(ClassManager* cm) {
    int choice;
    do {
        printf("\n----- QUAN LY LOP HOC -----\n");
        printf("1. Hien thi danh sach\n");
        printf("2. Them moi\n");
        printf("3. Xoa\n");
        printf("4. Cap nhat\n");
        printf("0. Quay lai\n");
        printf("Chon: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: cm->base.display(cm); break;
            case 2: cm->base.add(cm); break;
            case 3: cm->base.delete(cm); break;
            case 4: cm->base.update(cm); break;
            case 0: break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);
}

void menuStudent(StudentManager* sm) {
    int choice;
    do {
        printf("\n----- QUAN LY SINH VIEN-----\n");
        printf("1. Hien thi danh sach\n");
        printf("2. Them moi\n");
        printf("3. Xoa\n");
        printf("4. Cap nhat\n");
        printf("0. Quay lai\n");
        printf("Chon: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: sm->base.display(sm); break;
            case 2: sm->base.add(sm); break;
            case 3: sm->base.delete(sm); break;
            case 4: sm->base.update(sm); break;
            case 0: break;
            default: printf("Lua chon khong hopw le!\n");
        }
    } while (choice != 0);
}

int main() {
    int choice;
    do {
        printf("\n===== HE THONG QUAN LY SINH VIEN - RIKKEI EDU =====\n");
        printf("1. Quan ly lop hoc\n");
        printf("2. Quan ly sinh vien\n");
        printf("0. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: menuClass(&classManager); break;
            case 2: menuStudent(&studentManager); break;
            case 0: printf("Tam biet!\n"); break;
            default: printf("Lua chon khong hop le!\n");
        }
    } while (choice != 0);

    return 0;
}


