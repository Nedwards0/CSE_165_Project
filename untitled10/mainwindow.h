#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QtCharts/QChartGlobal>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGraphicsGridLayout>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtCharts/QBarSeries>

QT_CHARTS_USE_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
    void createSeries();
    void showLegendSpinbox();
    void hideLegendSpinbox();

public Q_SLOTS:
    void toggleAttached();
    void addBarset();
    void removeBarset();
    void sort();
    void backwardssort();
    void setLegendAlignment();

    void fontSizeChanged();

    void updateLegendLayout();

private:
    QChart *chart;
    QBarSeries *m_series;
    QChartView *c_view;
    QChart *c;
    QBarSeries c_series;

    QChartView *chartView;
    QGridLayout *mainLayout;
    QGridLayout *buttonLayout;
    QGridLayout *m_fontLayout;

    QDoubleSpinBox *fontSize;

    QGroupBox *m_legendSettings;
    QDoubleSpinBox *legend_X;
    QDoubleSpinBox *legend_Y;
    QDoubleSpinBox *legend_Width;
    QDoubleSpinBox *legend_Height;
};

#endif // MAINWIDGET_H
