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
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <QRandomGenerator>
#include <string>
#include<QDebug>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;
QT_CHARTS_USE_NAMESPACE
vector<state> vect;

//API Call



MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    // Create buttons for ui
    m_buttonLayout = new QGridLayout();
    QPushButton *detachLegendButton = new QPushButton("Toggle attached");
    connect(detachLegendButton, &QPushButton::clicked, this, &MainWidget::toggleAttached);
    m_buttonLayout->addWidget(detachLegendButton, 0, 0);

    QPushButton *addSetButton = new QPushButton("add barset");
    connect(addSetButton, &QPushButton::clicked, this, &MainWidget::addBarset);
    m_buttonLayout->addWidget(addSetButton, 2, 0);
    QPushButton *removeBarsetButton = new QPushButton("remove barset");
    connect(removeBarsetButton, &QPushButton::clicked, this, &MainWidget::removeBarset);
    m_buttonLayout->addWidget(removeBarsetButton, 3, 0);

    QPushButton *alignButton = new QPushButton("Align (Bottom)");
    connect(alignButton, &QPushButton::clicked, this, &MainWidget::setLegendAlignment);
    m_buttonLayout->addWidget(alignButton, 4, 0);

    QPushButton *boldButton = new QPushButton("Toggle bold");
    connect(boldButton, &QPushButton::clicked, this, &MainWidget::toggleBold);
    m_buttonLayout->addWidget(boldButton, 8, 0);

    QPushButton *italicButton = new QPushButton("Toggle italic");
    connect(italicButton, &QPushButton::clicked, this, &MainWidget::toggleItalic);
    m_buttonLayout->addWidget(italicButton, 9, 0);


    QPushButton *sortbutton = new QPushButton("Sort low to high");
    connect(sortbutton, &QPushButton::clicked, this, &MainWidget::sort);
    m_buttonLayout->addWidget(sortbutton, 10, 0);

    QPushButton *backwardsort = new QPushButton("Sort high to low");
    connect(backwardsort, &QPushButton::clicked, this, &MainWidget::sort);
    m_buttonLayout->addWidget(backwardsort, 11, 0);

    m_legendPosX = new QDoubleSpinBox();
    m_legendPosY = new QDoubleSpinBox();
    m_legendWidth = new QDoubleSpinBox();
    m_legendHeight = new QDoubleSpinBox();

    connect(m_legendPosX,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateLegendLayout);
    connect(m_legendPosY,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateLegendLayout);
    connect(m_legendWidth,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateLegendLayout);
    connect(m_legendHeight,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::updateLegendLayout);

    QFormLayout *legendLayout = new QFormLayout();
    legendLayout->addRow("HPos", m_legendPosX);
    legendLayout->addRow("VPos", m_legendPosY);
    legendLayout->addRow("Width", m_legendWidth);
    legendLayout->addRow("Height", m_legendHeight);
    m_legendSettings = new QGroupBox("Detached legend");
    m_legendSettings->setLayout(legendLayout);
    m_buttonLayout->addWidget(m_legendSettings);
    m_legendSettings->setVisible(false);

    // Create chart view with the chart
    m_chart = new QChart();
    m_chartView = new QChartView(m_chart, this);

    // Create spinbox to modify font size
    m_fontSize = new QDoubleSpinBox();
    m_fontSize->setValue(m_chart->legend()->font().pointSizeF());
    connect(m_fontSize,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this, &MainWidget::fontSizeChanged);

    QFormLayout *fontLayout = new QFormLayout();
    fontLayout->addRow("Legend font size", m_fontSize);

    // Create layout for grid and detached legend
    m_mainLayout = new QGridLayout();
    m_mainLayout->addLayout(m_buttonLayout, 0, 0);
    m_mainLayout->addLayout(fontLayout, 1, 0);
    m_mainLayout->addWidget(m_chartView, 0, 1, 4, 1);
    setLayout(m_mainLayout);

    createSeries();
}

void MainWidget::createSeries()
{
    m_series = new QBarSeries();
    for(int i=0;i<50;i++){
        addBarset();


    }
    m_chart->addSeries(m_series);
    m_chart->setTitle("Legend detach example");
    m_chart->createDefaultAxes();
//![1]
    m_chart->legend()->setVisible(true);
    m_chart->legend()->setAlignment(Qt::AlignBottom);
//![1]

    m_chartView->setRenderHint(QPainter::Antialiasing);
}

void MainWidget::showLegendSpinbox()
{
    m_legendSettings->setVisible(true);
    QRectF chartViewRect = m_chartView->rect();

    m_legendPosX->setMinimum(0);
    m_legendPosX->setMaximum(chartViewRect.width());
    m_legendPosX->setValue(150);

    m_legendPosY->setMinimum(0);
    m_legendPosY->setMaximum(chartViewRect.height());
    m_legendPosY->setValue(150);

    m_legendWidth->setMinimum(0);
    m_legendWidth->setMaximum(chartViewRect.width());
    m_legendWidth->setValue(150);

    m_legendHeight->setMinimum(0);
    m_legendHeight->setMaximum(chartViewRect.height());
    m_legendHeight->setValue(75);
}

void MainWidget::hideLegendSpinbox()
{
    m_legendSettings->setVisible(false);
}


void MainWidget::toggleAttached()
{
    QLegend *legend = m_chart->legend();
    if (legend->isAttachedToChart()) {
        //![2]
        legend->detachFromChart();
        m_chart->legend()->setBackgroundVisible(true);
        m_chart->legend()->setBrush(QBrush(QColor(128, 128, 128, 128)));
        m_chart->legend()->setPen(QPen(QColor(192, 192, 192, 192)));
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
    QBarSet *barSet = new QBarSet(QString("Califorina") + QString::number(m_series->count()));
    qreal delta = m_series->count() +1;

    *barSet << 2 + delta;//This needs to be api values
    m_series->append(barSet);
}

void MainWidget::removeBarset()
{
    QList<QBarSet *> sets = m_series->barSets();
    if (sets.count() > 0) {
        m_series->remove(sets.at(sets.count() - 1));
    }
}

void MainWidget::setLegendAlignment()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());

    switch (m_chart->legend()->alignment()) {
    case Qt::AlignTop:
        m_chart->legend()->setAlignment(Qt::AlignLeft);
        if (button)
            button->setText("Align (Left)");
        break;
    case Qt::AlignLeft:
        m_chart->legend()->setAlignment(Qt::AlignBottom);
        if (button)
            button->setText("Align (Bottom)");
        break;
    case Qt::AlignBottom:
        m_chart->legend()->setAlignment(Qt::AlignRight);
        if (button)
            button->setText("Align (Right)");
        break;
    default:
        if (button)
            button->setText("Align (Top)");
        m_chart->legend()->setAlignment(Qt::AlignTop);
        break;
    }
}

void MainWidget::toggleBold()
{
    QFont font = m_chart->legend()->font();
    font.setBold(!font.bold());
    m_chart->legend()->setFont(font);
}

void MainWidget::toggleItalic()
{
    QFont font = m_chart->legend()->font();
    font.setItalic(!font.italic());
    m_chart->legend()->setFont(font);
}

void MainWidget::fontSizeChanged()
{
    QFont font = m_chart->legend()->font();
    font.setPointSizeF(m_fontSize->value());
    m_chart->legend()->setFont(font);
}

void MainWidget::updateLegendLayout()
{
//![4]
//!
    m_chart->legend()->setGeometry(QRectF(m_legendPosX->value(),
                                          m_legendPosY->value(),
                                          m_legendWidth->value(),
                                          m_legendHeight->value()));
//![4]
}
void MainWidget::sort(){//Sort low to high.

    //This needs to update m_charts

    if(!(vect.size() == 0))
    {
        int index=0;
        vector<state> temp;
        int size=vect.size();
        for(int i=0;i<size;i++){
            state lowest;//Using default constructor for MAX_Int
            for(int j=0;j<size;j++){
                 if(vect[j].cases<lowest.cases){
                     lowest=vect[j];
                     //qInfo() << "test";
                     index=j;
                 }
             }
             //qInfo() << lowest.cases;
             temp.push_back(lowest);
             vect[index].cases=INT_MAX;

        }
        vect=temp;
        //ui->item1->setText(QString::fromStdString(temp[0].name));
        //ui->item1->setMaximumHeight(vect[0].cases);
        qInfo() << vect[0].cases;
    }
}
void MainWidget::backwardssort(){
    //This needs to update m_charts

}
