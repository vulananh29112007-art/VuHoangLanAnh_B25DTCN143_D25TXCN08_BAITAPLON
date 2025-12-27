#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_NAME = 100;

// ==================== LOP DOI TUONG ====================

class Classroom {
private:
    string classId;
    string className;
    string major;
    string type; // "CNTT" hoac "Ngoai ngu"

public:
    Classroom() {}
    Classroom(string id, string name, string maj, string t)
        : classId(id), className(name), major(maj), type(t) {}

    // Getter
    string getClassId() const { return classId; }
    string getClassName() const { return className; }
    string getMajor() const { return major; }
    string getType() const { return type; }

    // Setter
    void setClassName(string name) { className = name; }
    void setMajor(string maj) { major = maj; }
    void setType(string t) { type = t; }

    void display() const {
        cout << left
             << setw(15) << classId
             << setw(25) << className
             << setw(20) << major
             << setw(10) << type << endl;
    }

    void input() {
        cout << "Nhap ma lop: ";
        cin >> classId;
        cin.ignore();
        cout << "Nhap ten lop: ";
        getline(cin, className);
        cout << "Nhap chuyen nganh: ";
        getline(cin, major);
        cout << "Nhap loai lop (CNTT / Ngoai ngu): ";
        cin >> type;
    }
};

class Student {
private:
    string studentId;
    string name;
    string birthDate; // dd/mm/yyyy
    string email;
    string phone;

public:
    Student() {}
    Student(string id, string n, string bd, string e, string p)
        : studentId(id), name(n), birthDate(bd), email(e), phone(p) {}

    // Getter
    string getStudentId() const { return studentId; }
    string getName() const { return name; }
    string getBirthDate() const { return birthDate; }
    string getEmail() const { return email; }
    string getPhone() const { return phone; }

    // Setter
    void setName(string n) { name = n; }
    void setBirthDate(string bd) { birthDate = bd; }
    void setEmail(string e) { email = e; }
    void setPhone(string p) { phone = p; }

    void display() const {
        cout << left
             << setw(15) << studentId
             << setw(25) << name
             << setw(12) << birthDate
             << setw(25) << email
             << setw(15) << phone << endl;
    }

    void input() {
        cout << "Nhap ma sinh vien: ";
        cin >> studentId;
        cin.ignore();
        cout << "Nhap ho ten: ";
        getline(cin, name);
        cout << "Nhap ngay sinh (dd/mm/yyyy): ";
        cin >> birthDate;
        cout << "Nhap email: ";
        cin >> email;
        cout << "Nhap so dien thoai: ";
        cin >> phone;
    }
};

// ==================== L?P CHA TR?U TÝ?NG ====================

class Manageable {
public:
    virtual void display() const = 0;
    virtual void add() = 0;
    virtual void remove() = 0;  // Xóa
    virtual void update() = 0;
    virtual ~Manageable() {} // Virtual destructor
};

class ClassManager : public Manageable {
private:
    vector<Classroom> classes;

    int findIndex(string id) const {
        for (int i = 0; i < classes.size(); i++) {
            if (classes[i].getClassId() == id) return i;
        }
        return -1;
    }

public:
    void display() const override {
        cout << "\n=== DANH SACH LOP HOC (" << classes.size() << ") ===\n";
        cout << left
             << setw(15) << "Ma lop"
             << setw(25) << "Ten lop"
             << setw(20) << "Chuyen nganh"
             << setw(10) << "Loai" << endl;
        for (const auto& c : classes) {
            c.display();
        }
    }

    void add() override {
        Classroom c;
        c.input();
        classes.push_back(c);
        cout << "Them lop thanh cong!\n";
    }

    void remove() override {
        string id;
        cout << "Nhap ma lop can xoa: ";
        cin >> id;
        int index = findIndex(id);
        if (index != -1) {
            classes.erase(classes.begin() + index);
            cout << "Xoa lop thanh cong!\n";
        } else {
            cout << "Khong tim thay lop co ma " << id << endl;
        }
    }

    void update() override {
        string id;
        cout << "Nhap ma sinh vien can cap nhat: ";
        cin >> id;
        int index = findIndex(id);
        if (index != -1) {
            cin.ignore();
            string newName, newMajor, newType;
            cout << "Nhap ten lop moi: ";
            getline(cin, newName);
            cout << "Nhap chuyen nganh moi: ";
            getline(cin, newMajor);
            cout << "Nhap loai lop moi (CNTT / Ngoai ngu): ";
            cin >> newType;

            classes[index].setClassName(newName);
            classes[index].setMajor(newMajor);
            classes[index].setType(newType);
            cout << "Cap nhat thanh cong!\n";
        } else {
            cout << "Khong tim thay lop!\n";
        }
    }
};

// ==================== QU?N L? SINH VIÊN ====================

class StudentManager : public Manageable {
private:
    vector<Student> students;

    int findIndex(string id) const {
        for (int i = 0; i < students.size(); i++) {
            if (students[i].getStudentId() == id) return i;
        }
        return -1;
    }

public:
    void display() const override {
        cout << "\n=== DANH SACH SINH VIEN (" << students.size() << ") ===\n";
        cout << left
             << setw(15) << "MSSV"
             << setw(25) << "Ho ten"
             << setw(12) << "Ngay sinh"
             << setw(25) << "Email"
             << setw(15) << "SÐT" << endl;
        for (const auto& s : students) {
            s.display();
        }
    }

    void add() override {
        Student s;
        s.input();
        students.push_back(s);
        cout << "Them sinh vien thanh cong!\n";
    }

    void remove() override {
        string id;
        cout << "Nhap ma sinh vien can co: ";
        cin >> id;
        int index = findIndex(id);
        if (index != -1) {
            students.erase(students.begin() + index);
            cout << "Xoa sinh vien thanh cong!\n";
        } else {
            cout << "Khong tim thay sinh vien co ma " << id << endl;
        }
    }

    void update() override {
        string id;
        cout << "Nhap ma sinh vien can cap nhat: ";
        cin >> id;
        int index = findIndex(id);
        if (index != -1) {
            cin.ignore();
            string newName, newBirth, newEmail, newPhone;
            cout << "Nhap ten moi: ";
            getline(cin, newName);
            cout << "Nhap ngay sinh moi (dd/mm/yyyy): ";
            cin >> newBirth;
            cout << "Nhap email moi: ";
            cin >> newEmail;
            cout << "Nhap SÐT moi: ";
            cin >> newPhone;

            students[index].setName(newName);
            students[index].setBirthDate(newBirth);
            students[index].setEmail(newEmail);
            students[index].setPhone(newPhone);
            cout << "Cap nhat thannh cong!\n";
        } else {
            cout << "Khong tim thay sinh vien!\n";
        }
    }
};

// ==================== MENU ====================

void menuClass(Manageable* manager) {
    int choice;
    do {
        cout << "\n----- QUAN LY LOP HOC -----\n";
        cout << "1. Hien thi danh sach\n";
        cout << "2. Them moi\n";
        cout << "3. Xoa\n";
        cout << "4. Cap nhat\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
            case 1: manager->display(); break;
            case 2: manager->add(); break;
            case 3: manager->remove(); break;
            case 4: manager->update(); break;
            case 0: break;
            default: cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}

void menuStudent(Manageable* manager) {
    int choice;
    do {
        cout << "\n----- QUAN LI SINH VIEN -----\n";
        cout << "1. Hien thi danh sach\n";
        cout << "2. Them moi\n";
        cout << "3. Xoa\n";
        cout << "4. Cap nhat\n";
        cout << "0. Quay lai\n";
        cout << "Chon: ";
        cin >> choice;

        switch (choice) {
            case 1: manager->display(); break;
            case 2: manager->add(); break;
            case 3: manager->remove(); break;
            case 4: manager->update(); break;
            case 0: break;
            default: cout << "Lua chon khong hop le?!\n";
        }
    } while (choice != 0);
}

int main() {
    ClassManager classMgr;
    StudentManager studentMgr;

    int choice;
    do {
        cout << "\n===== HE THONG QUAN LY SINH VIEN - RIKKEI EDU =====\n";
        cout << "1. Quan li lop hoc\n";
        cout << "2. Quan li sinh vien\n";
        cout << "0. Thoat\n";
        cout << "Chon chuc nang: ";
        cin >> choice;

        switch (choice) {
            case 1: menuClass(&classMgr); break;
            case 2: menuStudent(&studentMgr); break;
            case 0: cout << "Tam biet!\n"; break;
            default: cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);

    return 0;
}
