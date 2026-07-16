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

    if (ui->BtnRegister) {
        connect(ui->BtnRegister, &QPushButton::clicked, this, &RegisterDialog::on_BtnRegisterConfirm_clicked);
    }
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_BtnRegisterConfirm_clicked()
{
    if (!ui->TxtRegisterEmail || !ui->TxtRegisterNumber || !ui->TxtRegisterUser || !ui->TxtRegisterPassword) {
        QMessageBox::critical(this, "Lỗi hệ thống", "Không tìm thấy đầy đủ các ô nhập liệu trên giao diện!");
        return;
    }

    QString email = ui->TxtRegisterEmail->text().trimmed();
    QString phoneNumber = ui->TxtRegisterNumber->text().trimmed();
    QString username = ui->TxtRegisterUser->text().trimmed();
    QString password = ui->TxtRegisterPassword->text();

    if (email.isEmpty() || phoneNumber.isEmpty() || username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Thông báo", "Vui lòng nhập đầy đủ các thông tin: Email, Số điện thoại, Tài khoản và Mật khẩu!");
        return;
    }

    QUrl url("http://127.0.0.1:3000/api/register");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject data;
    data["email"] = email;
    data["phone_number"] = phoneNumber;
    data["username"] = username;
    data["password"] = password;
    QJsonDocument doc(data);

    QNetworkReply *reply = networkManager->post(request, doc.toJson());

    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument resDoc = QJsonDocument::fromJson(reply->readAll());
            QJsonObject jsonObj = resDoc.object();

            if (jsonObj["success"].toBool()) {
                QMessageBox::information(this, "Thành công", "Đăng ký tài khoản thành công!");
                this->accept();
            } else {
                QString errorMsg = jsonObj["message"].toString();
                if (errorMsg.isEmpty()) errorMsg = "Tài khoản/Email/SĐT đã tồn tại hoặc đăng ký thất bại!";
                QMessageBox::warning(this, "Thất bại", errorMsg);
            }
        } else {
            QMessageBox::critical(this, "Lỗi", "Không thể kết nối tới Server Python FastAPI!\nHãy chắc chắn bạn đã chạy Backend.");
        }
        reply->deleteLater();
    });
}