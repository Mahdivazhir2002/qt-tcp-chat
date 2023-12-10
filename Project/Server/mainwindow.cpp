#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_send->setEnabled(false);
    m_Server=new QTcpServer;
    connect(m_Server,&QTcpServer::newConnection,this,&::MainWindow::server_New_Connect);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_listen_clicked()
{
    if(m_Server->listen(QHostAddress::Any,9999)){
        qDebug()<<"server is ready";
    }
    else {
        qDebug()<<"server cant ready";
    }
}
void MainWindow::on_pushButton_send_clicked()
{

 m_Socket->write(ui->textEdit->toPlainText().toUtf8());
 ui->textBrowser->append("From server : \n"+ui->textEdit->toPlainText().toUtf8());

 m_Socket->flush();
 ui->textEdit->clear();


}


void MainWindow::server_New_Connect()
{
    m_Socket = m_Server->nextPendingConnection();
    QObject::connect(m_Socket,&QTcpSocket::readyRead,this,&MainWindow::socket_Recv_Data);
    QObject::connect(m_Socket,&QTcpSocket::disconnected,this,&MainWindow::socket_Disconnect);


    ui->textBrowser->append(tr("Client Connect ! %1\n"));
    ui->pushButton_send->setEnabled(true);
}

void MainWindow::socket_Recv_Data()
{
    QByteArray Data_from_client;
    Data_from_client+=m_Socket->readAll();
    QString cdata=QString(Data_from_client);
    ui->textBrowser->append("From Client: ");
    ui->textBrowser->append(cdata);


}

void MainWindow::socket_Disconnect()
{
    ui->pushButton_send->setEnabled(false);
}


