#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <string>
#include <iostream>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    string description = "";

private:
    Ui::MainWindow *ui;
    QString myUrl ="https://google.com";
    string city = "Ankara";

    string code;
private slots:
    void downloadfinished(QNetworkReply *);
    void check_weather();
    void on_comboBox_currentIndexChanged(int index);
    void background(string str);
};
#endif // MAINWINDOW_H
