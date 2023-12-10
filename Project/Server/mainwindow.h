#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTcpServer>
#include<QTcpSocket>
#include <QtWidgets/QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void server_New_Connect();
    void socket_Recv_Data();
    void socket_Disconnect();

    void on_pushButton_send_clicked();

    void on_pushButton_listen_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer *m_Server;
    QTcpSocket *m_Socket;
};
#endif // MAINWINDOW_H
