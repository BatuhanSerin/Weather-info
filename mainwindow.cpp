#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

using namespace std;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    check_weather();
    QPixmap pix(":/image/background1.png");
    ui->label_2->setPixmap(pix);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::downloadfinished(QNetworkReply *rep){

    QByteArray bts = rep->readAll();
    QString str(bts);
    //ui->plainTextEdit->setPlainText(str);
    cout << str.toStdString()<< endl << endl;

/*
    QJsonArray jsonArray;
    QJsonObject branchObject;

    branchObject.insert(str, branchObject);
    jsonArray.append(branchObject);

    QJsonDocument jsonDocument;
    jsonDocument.setObject(branchObject);
    QByteArray byteArray = jsonDocument.toJson(QJsonDocument::Indented);
    QFile file("weather.json");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << QString("fail to open the file: %1, %2, %3").arg(__FILE__).arg(__LINE__).arg(__FUNCTION__);
        return;
    }
    QTextStream out(&file);
    out << byteArray;
    file.close();

    //qDebug() << byteArray;
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString data = file.readAll();
    file.close();

    //QJsonDocument object = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject object = jsonDocument.object();
    QJsonValue name = object.value("main").toArray();

    QString decodedData = "";

    decodedData.append(name.toString());

    ui->plainTextEdit->setPlainText(decodedData);
*/


    QJsonDocument jsonresponse = QJsonDocument::fromJson(str.toUtf8());

    QJsonObject object = jsonresponse.object();
    QJsonObject object2 = object["main"].toObject();

    QJsonValue value = object.value("weather");
    QJsonArray array = value.toArray();
    foreach (const QJsonValue & v, array){
        QString cond = v.toObject().value("icon").toString();
        code = cond.toStdString();
        qDebug() << cond;
}
    cout << code ;
    background(code);
    int degree = object2["temp"].toDouble();

    degree = degree -  273;

    cout<< endl << degree << endl ;

    ui->label->setText(QString::fromStdString(MainWindow::city) + "\n\n\n\n\nDegree :" + QString::number(degree) + " C\n\n\n\n\n" + QString::fromStdString(description));
}

void MainWindow::background(string x){
    if(x == "01d" || x == "01n"){
        description="Clear Sky";
        QPixmap pix(":/image/01n.png");
        ui->label_2->setPixmap(pix);
    }
    else if(x == "02d" || x == "02n"){
        description="Few Clouds";
        QPixmap pix(":/image/02n.png");
        ui->label_2->setPixmap(pix);
    }
    else if(x == "03d" || x == "03n"){
        description="Scattered Clouds";
        QPixmap pix(":/image/02n.png");
        ui->label_2->setPixmap(pix);
    }
    else if(x == "04d" || x == "04n"){
        description="Broken Clouds";
        QPixmap pix(":/image/04n.png");
        ui->label_2->setPixmap(pix);
    }
    else if(x == "09d" || x == "09n"){
        description="Shower Rain";
        QPixmap pix(":/image/09n.png");
        ui->label_2->setPixmap(pix);
    }
    else if(x == "10d" || x == "10n"){
        description="Rain";
        QPixmap pix(":/image/10n.png");
        ui->label_2->setPixmap(pix);
    }
    else if(x == "11d" || x == "11n"){
        description="Thunderstorm";
        QPixmap pix(":/image/11n.png");
        ui->label_2->setPixmap(pix);
    }
    else if(x == "13d" || x == "13n"){
        description="Snow";
        QPixmap pix(":/image/13n.png");
        ui->label_2->setPixmap(pix);
    }
    else if(x == "50d" || x == "50n"){
        description="Mist";
        QPixmap pix(":/image/50n.png");
        ui->label_2->setPixmap(pix);
    }


}

void MainWindow::check_weather()
{


    QString settings;
    QFile file;
    file.setFileName(":/image/iller.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    settings = file.readAll();
    file.close();

    QJsonDocument sd = QJsonDocument::fromJson(settings.toUtf8());

    QJsonObject sett2 = sd.object();



    for(int i=1;i<=81;i++){
        QString s = QString::number(i);
        qDebug() << sett2.value(QString(s)).toString();
        ui->comboBox->addItem(sett2.value(QString(s)).toString());

    }



       QNetworkAccessManager * mgr = new QNetworkAccessManager(this);
       connect(mgr,SIGNAL(finished(QNetworkReply*)),this,SLOT(downloadfinished(QNetworkReply*)));
       connect(mgr,SIGNAL(finished(QNetworkReply*)),mgr,SLOT(deleteLater()));


       mgr->get(QNetworkRequest(QUrl("https://api.openweathermap.org/data/2.5/weather?q=" + ui->comboBox->currentText() + "&appid=95edf34d0dd7709f36b7ac7f67cf2399")));

       city = ui->comboBox->currentText().toStdString();




}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    /*
    if(index == 1){
        //city = ui->comboBox->currentText();
        city = "Eskisehir";
    }
    else if(index == 2){
        city = "Izmir";
    }
    else if(index == 3){
        city = "Istanbul";
    }
    else {
        city = "Ankara";
    }
    */
    check_weather();
}

