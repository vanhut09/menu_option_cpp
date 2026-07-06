#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> 
#include <limits>
#include <windows.h>
#include <vector>
using namespace std;

struct KhachHang {
    int ID_customer;
    string Name_customer;
    string Phone;
};

struct TaiKhoandichvu {
    int ID;
    int ID_customer_buy; 
    string Service_type;  
    double Price;
};

void xoaManHinh() {
    #ifdef _WIN32
        system("cls");
    #else
        cout << "\033[2J\033[1;1H";
    #endif
}

void dungManHinh() {
    cout << "\n Nhấn Enter để tiếp tục...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
}

vector<KhachHang> danhsachKH;
vector<TaiKhoandichvu> danhsachdichvu;

void dangnhap() {
    vector<string> DS_ADMIN = {"Akira", "Khoa", "Hieu", "khanh"};
    vector<string> DS_PASSWORK = {"1412", "1234", "1234", "1234"};
    vector<string> DS_PHANCAP = {"ADMIN", "MANAGER", "DEVELOPER", "TESTER"};
    string tk, mk;

    while (true) {
        xoaManHinh();
        cout << "=== HỆ THỐNG ĐĂNG NHẬP ===\n";
        cout << "Tên tài khoản: "; getline(cin, tk);
        cout << "Mật khẩu: ";     getline(cin, mk);

        bool check = false;
        string PHANCAP = "";

        for (size_t i = 0; i < DS_ADMIN.size(); i++) {
            if (tk == DS_ADMIN[i] && mk == DS_PASSWORK[i]) {
                check = true;
                PHANCAP = DS_PHANCAP[i];
                break;
            }
        }

        if (check == true) {
            cout << "\nĐăng nhập thành công! Chào mừng " << PHANCAP << " đã trở lại";
            Sleep(3667);
            break;
        } else {
            cout << "\nSai rồi nhập lại đi";
        }
        dungManHinh();
    }
}

int timDichVuTheoID(int id) {
    for (size_t i = 0; i < danhsachdichvu.size(); i++) {
        if (danhsachdichvu[i].ID == id) {
            return i;
        }
    }
    return -1;
}

int timKhachHangTheoID(int id) {
    for (size_t i = 0; i < danhsachKH.size(); i++) {
        if (danhsachKH[i].ID_customer == id) {
            return i;
        }
    }
    return -1;
}

void themDichVu() {
    TaiKhoandichvu dv;
    cout << "Nhập ID dịch vụ: ";
    cin >> dv.ID;

    if (timDichVuTheoID(dv.ID) != -1) {
        cout << "Lỗi: ID dịch vụ đã tồn tại!\n";
        return;
    }
    cout << "Nhập ID khách hàng mua dịch vụ: ";
    cin >> dv.ID_customer_buy;
    if (timKhachHangTheoID(dv.ID_customer_buy) == -1) {
        cout << "Lỗi: Không tìm thấy khách hàng có ID này! Vui lòng thêm khách hàng trước.\n";
        return;
    }

    cin.ignore();

    cout << "Nhập loại dịch vụ: ";
    getline(cin, dv.Service_type);

    cout << "Nhập giá tiền: ";
    cin >> dv.Price;

    danhsachdichvu.push_back(dv);
    cout << "Thêm tài khoản dịch vụ thành công!\n";
}

void hienThiDichVu() {
    if (danhsachdichvu.empty()) {
        cout << "Chưa có tài khoản dịch vụ nào!\n";
        return;
    }

    cout << left
         << setw(10) << "ID DV"
         << setw(20) << "ID Khach hang"
         << setw(30) << "Loai dich vu"
         << setw(15) << "Gia tien" << endl;

    cout << "-----------------------------------------------------------------------------\n";

    for (const auto& dv : danhsachdichvu) {
        cout << left
             << setw(10) << dv.ID
             << setw(20) << dv.ID_customer_buy
             << setw(30) << dv.Service_type
             << setw(15) << dv.Price
             << endl;
    }
}

void suaDichVu() {
    int id;
    cout << "Nhập ID dịch vụ cần sửa: ";
    cin >> id;

    int vitri = timDichVuTheoID(id);
    if (vitri == -1) {
        cout << "Lỗi: Không tìm thấy dịch vụ!\n";
        return;
    }

    int id_kh_moi;
    cout << "Nhập ID khách hàng mới (Hiện tại: " << danhsachdichvu[vitri].ID_customer_buy << "): ";
    cin >> id_kh_moi;
    if (timKhachHangTheoID(id_kh_moi) == -1) {
        cout << "Lỗi: Khách hàng không tồn tại! Hủy cập nhật.\n";
        return;
    }
    danhsachdichvu[vitri].ID_customer_buy = id_kh_moi;

    cin.ignore();

    cout << "Nhập loại dịch vụ mới: ";
    getline(cin, danhsachdichvu[vitri].Service_type);

    cout << "Nhập giá tiền mới: ";
    cin >> danhsachdichvu[vitri].Price;

    cout << "Cập nhật dịch vụ thành công!\n";
}

void xoaDichVu() {
    int id;
    cout << "Nhập ID dịch vụ cần xóa: ";
    cin >> id;
    int vitri = timDichVuTheoID(id);
    if (vitri == -1) {
        cout << "Lỗi: Không tìm thấy dịch vụ!\n";
        return;
    }
    danhsachdichvu.erase(danhsachdichvu.begin() + vitri);
    cout << "Xóa tài khoản dịch vụ thành công!\n";
}

void themKhachHang() {
    KhachHang kh;

    cout << "Nhập ID khách hàng: ";
    cin >> kh.ID_customer;

    if (timKhachHangTheoID(kh.ID_customer) != -1) {
        cout << "ID đã tồn tại!\n";
        return;
    }

    cin.ignore();

    cout << "Nhập tên khách hàng: ";
    getline(cin, kh.Name_customer);

    cout << "Nhập số điện thoại: ";
    getline(cin, kh.Phone);

    danhsachKH.push_back(kh);

    cout << "Thêm khách hàng thành công!\n";
}

void hienThiKhachHang() {
    if (danhsachKH.empty()) {
        cout << "Chưa có khách hàng nào!\n";
        return;
    }

    cout << left
         << setw(10) << "ID"
         << setw(30) << "Ten khach hang"
         << setw(20) << "So dien thoai" << endl;

    cout << "------------------------------------------------------------\n";

    for (const auto& kh : danhsachKH) {
        cout << left
             << setw(10) << kh.ID_customer
             << setw(30) << kh.Name_customer
             << setw(20) << kh.Phone
             << endl;
    }
}

void suaKhachHang() {
    int id;

    cout << "Nhập ID khách hàng cần sửa: ";
    cin >> id;

    int vitri = timKhachHangTheoID(id);

    if (vitri == -1) {
        cout << "Không tìm thấy khách hàng!\n";
        return;
    }

    cin.ignore();

    cout << "Nhập tên mới: ";
    getline(cin, danhsachKH[vitri].Name_customer);

    cout << "Nhập số điện thoại mới: ";
    getline(cin, danhsachKH[vitri].Phone);

    cout << "Cập nhật thành công!\n";
}

void xoaKhachHang() {
    int id;
    cout << "Nhập ID khách hàng cần xóa: ";
    cin >> id;
    int vitri = timKhachHangTheoID(id);
    if (vitri == -1) {
        cout << "Không tìm thấy khách hàng!\n";
        return;
    }
    for (const auto& dv : danhsachdichvu) {
        if (dv.ID_customer_buy == id) {
            cout << "Lỗi: Không thể xóa! Khách hàng này đang sở hữu dịch vụ (ID DV: " << dv.ID << ").\n";
            return;
        }
    }

    danhsachKH.erase(danhsachKH.begin() + vitri);
    cout << "Xóa khách hàng thành công!\n";
}

void luuDuLieu() {
    ofstream fout("dulieu.txt");

    if (!fout) {
        cout << "Khong mo duoc file de ghi!\n";
        return;
    }

    fout << "===== DANH SACH KHACH HANG =====\n";
    fout << danhsachKH.size() << "\n";

    for (const auto &kh : danhsachKH) {
        fout << kh.ID_customer << endl;
        fout << kh.Name_customer << endl;
        fout << kh.Phone << endl;
    }

    fout << "===== DANH SACH DICH VU =====\n";
    fout << danhsachdichvu.size() << "\n";

    for (const auto &dv : danhsachdichvu) {
        fout << dv.ID << endl;
        fout << dv.ID_customer_buy << endl;
        fout << dv.Service_type << endl;
        fout << dv.Price << endl;
    }

    fout.close();
    cout << "Da luu du lieu vao file dulieu.txt thanh cong!\n";
}

void docDuLieu() {
    ifstream fin("dulieu.txt");
    if (!fin) return;

    string line;
    getline(fin, line); 
    int soKH = 0;
    if (fin >> soKH) {
        fin.ignore();
        for (int i = 0; i < soKH; i++) {
            KhachHang kh;
            fin >> kh.ID_customer;
            fin.ignore();
            getline(fin, kh.Name_customer);
            getline(fin, kh.Phone);
            danhsachKH.push_back(kh);
        }
    }

    fin.ignore(); 
    getline(fin, line); 
    int soDV = 0;
    if (fin >> soDV) {
        fin.ignore();
        for (int i = 0; i < soDV; i++) {
            TaiKhoandichvu dv;
            fin >> dv.ID;
            fin >> dv.ID_customer_buy;
            fin.ignore();
            getline(fin, dv.Service_type);
            fin >> dv.Price;
            fin.ignore();
            danhsachdichvu.push_back(dv);
        }
    }
    fin.close();
}

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    int choice;

    docDuLieu();
    xoaManHinh();
    dangnhap();
    
    while (true) {
        xoaManHinh();
        cout << "=============================================================================\n";
        cout << "       Chào mừng đến với siêu hệ thống quản lý các dịch vụ tiện ích          \n";
        cout << "=============================================================================\n";
        cout << "[1]. Đăng ký tài khoản người dùng\n";
        cout << "[2]. Hiển thị tài khoản người dùng\n";
        cout << "[3]. Chỉnh sửa tài khoản người dùng\n";
        cout << "[4]. Xóa tài khoản người dùng\n";
        cout << "[5]. Thêm tài khoản dịch vụ\n";
        cout << "[6]. Hiển thị tài khoản dịch vụ\n";
        cout << "[7]. Chỉnh sửa tài khoản dịch vụ\n";
        cout << "[8]. Xóa tài khoản dịch vụ\n";
        cout << "[0]. Lưu dữ liệu/Thoát chương trình\n";
        cout << "-----------------------------------------------------------------------------\n";
        cout << "Nhập lựa chọn của bạn (0-8): \n";

        if (!(cin >> choice)) {
            cout << "Lỗi: Vui lòng chỉ nhập số!\n";
            cin.clear();
            dungManHinh();
            continue;
        }
        
        cin.ignore();

        if (choice == 0) {
            luuDuLieu();
            cout << "Dang chuan bi thoat he thong...\n";
            Sleep(1000);
            xoaManHinh();
            break;
        }

        switch (choice) {
            case 1:
                xoaManHinh();
                themKhachHang();
                dungManHinh();
                break;
            case 2:
                xoaManHinh();
                hienThiKhachHang();
                dungManHinh();
                break;
            case 3:
                xoaManHinh();
                suaKhachHang();
                dungManHinh();
                break;
            case 4:
                xoaManHinh();
                xoaKhachHang();
                dungManHinh();
                break;
            case 5:
                xoaManHinh();
                themDichVu();
                dungManHinh();
                break;
            case 6:
                xoaManHinh();
                hienThiDichVu();
                dungManHinh();
                break;
            case 7:
                xoaManHinh();
                suaDichVu();
                dungManHinh();
                break;
            case 8:
                xoaManHinh();
                xoaDichVu();
                dungManHinh();
                break;
            default:
                dungManHinh();
                break;
        }
    }
    return 0;
}