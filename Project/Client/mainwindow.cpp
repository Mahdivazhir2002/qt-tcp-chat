#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_socket=new QTcpSocket(this);
    QObject::connect(m_socket,&QTcpSocket::readyRead,this,&MainWindow::Socket_recive_data);
   QObject::connect(m_socket,&QTcpSocket::disconnected,this,&MainWindow::socket_disconnect);
   ui->pushButton_send->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete m_socket;
    delete ui;

}



void MainWindow::on_pushButton_connect_clicked()
{
    QString IP;
    qint16 port;

    if(ui->pushButton_connect->text() == QString("Connect"))
    {
        IP = ui->lineEdit_IP->text();
        port = ui->lineEdit_Port->text().toInt();

        m_socket->abort();
        m_socket->connectToHost(IP,port);
        if(!m_socket->waitForConnected())
        {
            QMessageBox::warning(this,"error","cant connect to host","ok");
        }
        else
        {
            ui->pushButton_send->setEnabled(true);
            QMessageBox::information(this, "secsuss","can connect to host","ok");
            ui->pushButton_connect->setText("Disconnect");
        }
    }
    else
    {
        m_socket->disconnectFromHost();

        ui->pushButton_connect->setText("Connect");
        ui->pushButton_send->setEnabled(false);
    }
}


void MainWindow::on_pushButton_send_clicked()
{

    ui->textBrowser->append("From Client: ");
    ui->textBrowser->append(ui->textEdit->toPlainText().toUtf8());

    m_socket->write(ui->textEdit->toPlainText().toUtf8());
    m_socket->flush();
    ui->textEdit->clear();
}

void MainWindow::Socket_recive_data()
{
    QByteArray data_tmp;
    data_tmp = m_socket->readAll();
    if(!data_tmp.isEmpty())
    {
        QString str = QString(data_tmp);
        ui->textBrowser->append("From Server :");
        ui->textBrowser->append(str);
    }
}

void MainWindow::socket_disconnect()
{
    ui->pushButton_send->setEnabled(false);
    ui->pushButton_connect->setText("Connect");
    QMessageBox::warning(this, "error","disconect to host");
}
