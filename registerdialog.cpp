#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>

RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    networkManager = new QNetworkAccessManager(this);

    // 🚀 SỬA LỖI: Liên kết đúng tên nút bấm thực tế là "BtnRegister" trên giao diện của bạn
    if (ui->BtnRegister) {
        connect(ui->BtnRegister, &QPushButton::clicked, this, &RegisterDialog::on_BtnRegisterConfirm_clicked);
    }
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

// Xử lý sự kiện khi người dùng nhấn nút Xác nhận Đăng ký tài khoản mới
void RegisterDialog::on_BtnRegisterConfirm_clicked()
{
    // Kiểm tra an toàn linh kiện UI thực tế từ hình image_2b962b.jpg
    if (!ui->TxtRegisterUser || !ui->TxtRegisterPassword) {
        QMessageBox::critical(this, "Lỗi hệ thống", "Không tìm thấy ô nhập liệu TxtRegisterUser hoặc TxtRegisterPassword!");
        return;
    }

    QString username = ui->TxtRegisterUser->text().trimmed();
    QString password = ui->TxtRegisterPassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Thông báo", "Vui lòng nhập đầy đủ thông tin tài khoản và mật khẩu mới!");
        return;
    }

    // Cấu hình Request gửi tới API endpoint Register của Python FastAPI
    QUrl url("http://127.0.0.1:3000/api/register");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Đóng gói dữ liệu JSON
    QJsonObject data;
    data["username"] = username;
    data["password"] = password;
    QJsonDocument doc(data);

    // Tiến hành POST dữ liệu đăng ký lên Server
    QNetworkReply *reply = networkManager->post(request, doc.toJson());

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument resDoc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject jsonObj = resDoc.object();

            if (jsonObj["success"].toBool()) {
                QMessageBox::information(this, "Thành công", "Đăng ký tài khoản thành công!");
                this->accept(); // Đóng màn hình đăng ký và quay lại màn hình đăng nhập
            } else {
                QString errorMsg = jsonObj["message"].toString();
                if (errorMsg.isEmpty()) errorMsg = "Tài khoản đã tồn tại hoặc đăng ký thất bại!";
                QMessageBox::warning(this, "Thất bại", errorMsg);
            }
        } else {
            QMessageBox::critical(this, "Lỗi", "Không thể kết nối tới Server Python FastAPI!\nHãy chắc chắn bạn đã chạy Backend.");
        }
        reply->deleteLater();
    });
}