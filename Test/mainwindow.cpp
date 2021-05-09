#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include<QDebug>

using namespace std;

class state{
public:
    int cases;//Amount of cases in state
    string name;//Name of State
    state(string name_s, int amount){//Constructor
        this->cases=amount;
        this->name=name_s;

    }
    state(){//Default constructor
        this->cases=INT_MAX;//This is done for making sorting easier
        this->name="<UNK>";
    }
};
vector<state> vect;
//Global vector for saving states throughout run

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Start_clicked()
{
    //This is temporary values for testing.

    //api call

    state c("Califorina",400);//temparay testing
    vect.push_back(c);
    state c_2("as",9);
    vect.push_back(c_2);
    //This needs to be replaced with api call add then pushed into vector
    //This should clear the vector before the api call.
}

void MainWindow::on_Sort_in_order_clicked()
{
   int index=0;
   vector<state> temp;
   int size=vect.size();
   for(int i=0;i<size;i++){
       state lowest;//Using default constructor for MAX_Int
       for(int j=0;j<size;j++){
            if(vect[j].cases<lowest.cases){
                lowest=vect[j];
                qInfo() << "test";
                index=j;
            }
        }
        qInfo() << lowest.cases;
        temp.push_back(lowest);
        vect[index].cases=INT_MAX;

   }
   vect=temp;
   //ui->item1->setText(QString::fromStdString(temp[0].name));
   //ui->item1->setMaximumHeight(vect[0].cases);
   qInfo() << vect[0].cases;

}

void MainWindow::on_pushButton_clicked()
{
    //This is sorting using sorting done above then inversing it.
    MainWindow::on_Sort_in_order_clicked();
    vector<state> temp;
    int size=vect.size();
    for(int i=size-1;i>=0;i--){
       temp.push_back(vect[i]);
    }
    qInfo() << temp[0].cases;

}


