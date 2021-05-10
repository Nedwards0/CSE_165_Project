#include "mainwindow.h"
#include "State.h"
#include <QtCharts/QChart>
#include <QtCharts/QChartView>



#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtCore/QDebug>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QLegend>
#include <QtWidgets/QFormLayout>


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QRandomGenerator>
#include <string>
#include<QDebug>
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

int logic=1;




using namespace std;
QT_CHARTS_USE_NAMESPACE
vector<state> vect;

vector<state>removed;

std::ofstream myFile("foo.csv");
int arr[50]={
    2996968,31366,33613,49648,58623,58755,63994,68324,74575,96624,108512,110021,118857, 123233, 156406,191405,199333,221434,
    312636, 317980, 337510,342718,367115,400417,415942, 452059,  453316, 461173, 525937, 530988,584517,606153, 666381,
    666650,697398,733040,838061,868830,961082,988016,1007894,1083609,1085449,1177967,1358716,1495777,2070603, 2269798,2914818,23486};
int startup=50;
int size=sizeof(arr);
string s[50]={"CA","MS","HI","OK","WY","MN","ME","AK","DE","NH","ND","MT","ID","SD","WV","OR","NM","KS","NV"
             ," AR"," CT"," IA"," UT"," WA"," KY"," MD"," LA"," CO"," AL"," SC"," MO"," NE"," WI"
             ," VA"," MA"," IN"," TN"," AZ"," MI"," NC" ," NJ"," OH"," GA"," PA"," IL"," RI"," NY"," FL"," TX"," VT"};
int totalcount=0;
int sorted=1;
int counter=0;
//API Call


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    for(int i=0;i<50;i++){
        state c(s[i],arr[i]);
        vect.push_back(c);

    }
    // Create buttons for ui
    buttonLayout = new QGridLayout();
    QPushButton *detachLegendButton = new QPushButton("Toggle attached");
    connect(detachLegendButton, &QPushButton::clicked, this, &MainWidget::toggleAttached);
    buttonLayout->addWidget(detachLegendButton, 0, 0);

    QPushButton *addSetButton = new QPushButton("add barset");
    connect(addSetButton, &QPushButton::clicked, this, &MainWidget::addBarset);
    buttonLayout->addWidget(addSetButton, 2, 0);
    QPushButton *removeBarsetButton = new QPushButton("remove barset");
    connect(removeBarsetButton, &QPushButton::clicked, this, &MainWidget::removeBarset);
    buttonLayout->addWidget(removeBarsetButton, 3, 0);

    QPushButton *alignButton = new QPushButton("Align (Bottom)");
    connect(alignButton, &QPushButton::clicked, this, &MainWidget::setLegendAlignment);
    buttonLayout->addWidget(alignButton, 4, 0);






    QPushButton *sortbutton = new QPushButton("Sort low to high");
    connect(sortbutton, &QPushButton::clicked, this, &MainWidget::sort);
    buttonLayout->addWidget(sortbutton, 10, 0);

    QPushButton *backwardsort = new QPushButton("Sort high to low");
    connect(backwardsort, &QPushButton::clicked, this, &MainWidget::backwardssort);
    buttonLayout->addWidget(backwardsort, 11, 0);

    legend_X = new QDoubleSpinBox();
    legend_Y = new QDoubleSpinBox();
    legend_Width = new QDoubleSpinBox();
    legend_Height = new QDoubleSpinBox();

    connect(legend_X,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateLegendLayout);
    connect(legend_Y,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateLegendLayout);
    connect(legend_Width,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateLegendLayout);
    connect(legend_Height,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateLegendLayout);

    QFormLayout *legendLayout = new QFormLayout();
    legendLayout->addRow("Legend_X", legend_X);
    legendLayout->addRow("Legend_Y", legend_Y);
    legendLayout->addRow("Width", legend_Width);
    legendLayout->addRow("Height", legend_Height);
    m_legendSettings = new QGroupBox("Detached legend");
    m_legendSettings->setLayout(legendLayout);
    buttonLayout->addWidget(m_legendSettings);
    m_legendSettings->setVisible(false);

    // Create chart view with the chart
    chart = new QChart();
    chartView = new QChartView(chart, this);

    // Create spinbox to modify font size
    fontSize = new QDoubleSpinBox();
    fontSize->setValue(chart->legend()->font().pointSizeF());
    connect(fontSize,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::fontSizeChanged);

    QFormLayout *fontLayout = new QFormLayout();
    fontLayout->addRow("Legend font size", fontSize);

    // Create layout for grid and detached legend
    mainLayout = new QGridLayout();
    mainLayout->addLayout(buttonLayout, 0, 0);
    mainLayout->addLayout(fontLayout, 1, 0);
    mainLayout->addWidget(chartView, 0, 1, 4, 1);
    setLayout(mainLayout);

    createSeries();
}

void MainWidget::createSeries()
{
    m_series = new QBarSeries();
    for(int i=0;i<50;i++){
        addBarset();


    }
    chart->addSeries(m_series);
    chart->setTitle("Covid Cases Per state");
    chart->createDefaultAxes();
//![1]
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
//![1]

    chartView->setRenderHint(QPainter::Antialiasing);
}

void MainWidget::showLegendSpinbox()
{
    m_legendSettings->setVisible(true);
    QRectF chartViewRect = chartView->rect();

    legend_X->setMinimum(0);
    legend_X->setMaximum(chartViewRect.width());
    legend_X->setValue(150);

    legend_Y->setMinimum(0);
    legend_Y->setMaximum(chartViewRect.height());
    legend_Y->setValue(150);

    legend_Width->setMinimum(0);
    legend_Width->setMaximum(chartViewRect.width());
    legend_Width->setValue(150);

    legend_Height->setMinimum(0);
    legend_Height->setMaximum(chartViewRect.height());
    legend_Height->setValue(75);
}

void MainWidget::hideLegendSpinbox()
{
    m_legendSettings->setVisible(false);
}


void MainWidget::toggleAttached()
{
    QLegend *legend = chart->legend();
    if (legend->isAttachedToChart()) {
        //![2]
        legend->detachFromChart();
        chart->legend()->setBackgroundVisible(true);
        chart->legend()->setBrush(QBrush(QColor(120, 120, 120, 120)));
        chart->legend()->setPen(QPen(QColor(200, 200, 200, 200)));
        //![2]
        showLegendSpinbox();
        updateLegendLayout();
    } else {
        //![3]
        legend->attachToChart();
        legend->setBackgroundVisible(false);
        //![3]
        hideLegendSpinbox();
    }
    update();
}

void MainWidget::addBarset()
{
    QList<QBarSet *> sets = m_series->barSets();
    if(startup!=0){
        counter++;


                QBarSet *barSet = new QBarSet(QString::fromStdString(vect[totalcount].name));
                *barSet << vect[totalcount].cases;
                m_series->append(barSet);
        startup--;
        totalcount++;


    }
    else
    {
        counter++;
        if (sets.count() < 50) {
            state c(removed[removed.size()-1].name,removed[removed.size()-1].cases);

            QBarSet *barSet = new QBarSet(QString::fromStdString(removed[removed.size()-1].name));
            *barSet << removed[removed.size()-1].cases;
            m_series->append(barSet);
            removed.pop_back();
            vect.push_back(c);

        }
    }

}

void MainWidget::removeBarset()
{
    QList<QBarSet *> sets = m_series->barSets();
    if (sets.count() > 0) {
        counter--;
        removed.push_back(vect[vect.size()-1]);
        vect.pop_back();
        m_series->remove(sets.at(sets.count() - 1));




    }
}

void MainWidget::setLegendAlignment()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    switch (chart->legend()->alignment()) {
    case Qt::AlignTop:
        chart->legend()->setAlignment(Qt::AlignLeft);
        if (button)
            button->setText("Align (Left)");
        break;
    case Qt::AlignLeft:
        chart->legend()->setAlignment(Qt::AlignBottom);
        if (button)
            button->setText("Align (Bottom)");
        break;
    case Qt::AlignBottom:
        chart->legend()->setAlignment(Qt::AlignRight);
        if (button)
            button->setText("Align (Right)");
        break;
    default:
        if (button)
            button->setText("Align (Top)");
        chart->legend()->setAlignment(Qt::AlignTop);
        break;
    }
}



void MainWidget::fontSizeChanged()
{
    QFont font = chart->legend()->font();
    font.setPointSizeF(fontSize->value());
    chart->legend()->setFont(font);
}

void MainWidget::updateLegendLayout()
{
//![4]
//!
    chart->legend()->setGeometry(QRectF(legend_X->value(),
                                          legend_Y->value(),
                                          legend_Width->value(),
                                          legend_Height->value()));
//![4]
}
void MainWidget::sort(){//Sort low to high.
    c = new QChart();
    c_view = new QChartView(c, this);
    //This needs to update charts

    if((vect.size() != 0))
    {
        int index=0;
        vector<state> temp;
        int size=vect.size();
        for(int i=0;i<size;i++){
            state lowest;//Using default constructor for MAX_Int
            for(int j=0;j<size;j++){
                 if(vect[j].cases<lowest.cases){
                     lowest=vect[j];
                     index=j;
                 }
             }
             temp.push_back(lowest);
             vect[index].cases=INT_MAX;

        }
        vect=temp;
        int c=vect.size();
        for(int i=0;i<c;i++){
            removeBarset();
        }
        for(int i=0;i<c;i++){
            addBarset();
        }



        //ui->item1->setText(QString::fromStdString(temp[0].name));
        //ui->item1->setMaximumHeight(vect[0].cases);


    }
}
void MainWidget::backwardssort(){

    if((vect.size() != 0))
    {
        int index=0;
        vector<state> temp;
        int size=vect.size();
        for(int i=0;i<size;i++){
            state highest("name",-500);//Using default constructor for MAX_Int
            for(int j=0;j<size;j++){
                 if(vect[j].cases>highest.cases){
                     highest=vect[j];
                     index=j;
                 }
             }
             temp.push_back(highest);
             vect[index].cases=-60;

        }
        vect=temp;
        int c=vect.size();
        for(int i=0;i<c;i++){
            removeBarset();
        }
        for(int i=0;i<c;i++){
            addBarset();
        }


     }

}
