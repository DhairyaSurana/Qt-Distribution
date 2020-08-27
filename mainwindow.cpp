#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    graphData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::graphData() {

    // Assign names to the set of bars used
    QBarSet *set0 = new QBarSet("Altuve");
    QBarSet *set1 = new QBarSet("Martinez");
    QBarSet *set2 = new QBarSet("Segura");
    QBarSet *set3 = new QBarSet("Simmons");
    QBarSet *set4 = new QBarSet("Trout");

    // Assign values for each bar
    *set0 << 283;
    *set1 << 250;
    *set2 << 294;
    *set3 << 248;
    *set4 << 323;

    // Add all sets of data to the chart as a whole
    // 1. Bar Chart
    QBarSeries *series = new QBarSeries();

    // 2. Stacked bar chart
    // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);

    // Used to define the bar chart to display, title
    // legend,
    QChart *chart = new QChart();

    // Add the chart
    chart->addSeries(series);

    // Set title
    chart->setTitle("Sample Data Distribution");

    // Define starting animation
    // NoAnimation, GridAxisAnimations, SeriesAnimations
    chart->setAnimationOptions(QChart::AllAnimations);

    // Holds the category titles
    QStringList categories;
    categories << "2013" << "2014" << "2015" << "2016" << "2017";

    // Adds categories to the axes
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();

    // 1. Bar chart
    chart->addAxis(axis, Qt::AlignBottom);
    //chart->setAxisX(axis, series);

    // 2. Stacked Bar chart
    // chart->setAxisY(axis, series);

    // Define where the legend is displayed
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    // create graph and assign data to it:
    ui->graphicsView->setChart(chart);

}


void MainWindow::on_uni_button_toggled(bool checked)
{
    if(checked)
        qDebug() << "Uniform selected";
}

void MainWindow::on_norm_button_toggled(bool checked)
{
    if(checked)
        qDebug() << "Normal selected";

}

void MainWindow::on_other_button_toggled(bool checked)
{
    if(checked)
        qDebug() << "Other selected";

}
