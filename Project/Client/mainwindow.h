#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QTcpSocket>
#include <QtWidgets/QMessageBox>
#include <QMessageBox>

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
    void on_pushButton_connect_clicked();
    void on_pushButton_send_clicked();
    void Socket_recive_data();
    void socket_disconnect();


private:
    Ui::MainWindow *ui;
    QTcpSocket *m_socket;
};
#endif // MAINWINDOW_H
