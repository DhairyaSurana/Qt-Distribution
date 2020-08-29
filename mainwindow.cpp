#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <random>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<qreal> data = *createData(10000, "norm");
    graphData(data);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::graphData(QVector<qreal> data) {

    //std::sort(data.begin(), data.end());
    //qDebug() << data[0] << data[1] << data[2] << data[3];
    QVector<qreal>::iterator min = std::min_element(data.begin(), data.end());
    QVector<qreal>::iterator max = std::max_element(data.begin(), data.end());

    //qDebug() << "min: " << *min;
    //qDebug() << "max: " << *max;

    qreal range = *max - *min;
    //qDebug() << "range: " << range;
    qreal bin_length = range / 20;
    //qDebug() << "bin length: " << bin_length;

    QVector<qreal> categories_num;
    QStringList categories;

    for(qreal i = *min+bin_length; i <= *max; i+=bin_length) {

        categories << QString::number(i);
        categories_num.append(i);
    }



    QMap<float, int> freq;
    for(int c = 0; c < categories_num.size(); c++) {
        freq[categories_num[c]] = 0;
    }

    for(int i = 0; i < data.size(); i++) {

        for(int c = 0; c < categories_num.size()-1; c++) {

            qreal lower_bound = categories_num[c];
            qreal upper_bound = categories_num[c+1];

            if(lower_bound <= data[i] && data[i] <= upper_bound) {

                freq[upper_bound] += 1;
                break;
            }
        }
    }

    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Data");

    //qDebug() << "size: " << freq.values().size();
    QList<int> freq_list = freq.values();
    //qDebug() << freq_list[0] << freq_list[1] << freq_list[2] << freq_list[3] << freq_list[4] << freq_list[5] << freq_list[6] << freq_list[7] << freq_list[8] << freq_list[9] << freq_list[10] << freq_list[11] << freq_list[12] << freq_list[13] << freq_list[14] << freq_list[15] << freq_list[16] << freq_list[17] << freq_list[18] << freq_list[19];
    *set << freq_list[0] << freq_list[1] << freq_list[2] << freq_list[3] << freq_list[4] << freq_list[5] << freq_list[6] << freq_list[7] << freq_list[8] << freq_list[9] << freq_list[10] << freq_list[11] << freq_list[12] << freq_list[13] << freq_list[14] << freq_list[15] << freq_list[16] << freq_list[17] << freq_list[18] << freq_list[19];
    series->append(set);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsAngle(-90);

    QValueAxis *axisY = new QValueAxis();
    QList<int>::iterator maxY = std::max_element(freq_list.begin(), freq_list.end());
    axisY->setRange(0, *maxY);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Sample Data Distribution");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->graphicsView->setChart(chart);






    // Assign names to the set of bars used
//    QBarSet *set0 = new QBarSet("Altuve");
//    QBarSet *set1 = new QBarSet("Martinez");
//    QBarSet *set2 = new QBarSet("Segura");
//    QBarSet *set3 = new QBarSet("Simmons");
//    QBarSet *set4 = new QBarSet("Trout");

//    // Assign values for each bar
//    *set0 << 283;
//    *set1 << 250;
//    *set2 << 294;
//    *set3 << 248;
//    *set4 << 323;

//    // Add all sets of data to the chart as a whole
//    // 1. Bar Chart
//    QBarSeries *series = new QBarSeries();

//    // 2. Stacked bar chart
//    // QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
//    series->append(set0);
//    series->append(set1);
//    series->append(set2);
//    series->append(set3);
//    series->append(set4);

//    // Used to define the bar chart to display, title
//    // legend,
//    QChart *chart = new QChart();

//    // Add the chart
//    chart->addSeries(series);

//    // Set title
//    chart->setTitle("Sample Data Distribution");

//    // Define starting animation
//    // NoAnimation, GridAxisAnimations, SeriesAnimations
//    chart->setAnimationOptions(QChart::AllAnimations);

//    // Holds the category titles
//    QStringList categories;
//    categories << "2013" << "2014" << "2015" << "2016" << "2017";

//    // Adds categories to the axes
//    QBarCategoryAxis *axis = new QBarCategoryAxis();
//    axis->append(categories);
//    chart->createDefaultAxes();

//    // 1. Bar chart
//    chart->addAxis(axis, Qt::AlignBottom);
//    //chart->setAxisX(axis, series);

//    // 2. Stacked Bar chart
//    // chart->setAxisY(axis, series);

//    // Define where the legend is displayed
//    chart->legend()->setVisible(true);
//    chart->legend()->setAlignment(Qt::AlignBottom);

//    // create graph and assign data to it:
//    ui->graphicsView->setChart(chart);

}


void MainWindow::on_uni_button_toggled(bool checked)
{
    if(checked) {
        qDebug() << "Uniform selected";
        QVector<qreal> data = *createData(10000, "unif");

        graphData(data);

    }
}

void MainWindow::on_norm_button_toggled(bool checked)
{
    if(checked) {
        qDebug() << "Normal selected";
        QVector<qreal> data = *createData(10000, "norm");

        graphData(data);


    }

}

void MainWindow::on_other_button_toggled(bool checked)
{
    if(checked) {
        qDebug() << "Other selected";
        QVector<qreal> data = *createData(10000, "other");

        graphData(data);


    }

}


// Function to fill a QVector with samples from a specified distribution
// must #include <random> to use this function
//
QVector<qreal>* MainWindow::createData(int num, QString theType){

    QVector<qreal> *dat = new QVector<qreal>;

    std::default_random_engine generator;
    // the distribution type is determined by string input
    if (theType.contains("unif"))
    {
        std::uniform_real_distribution<double> distribution(0, 99.9999);
        // params are arbitrarily chosen
        for (int incr = 0; incr < num; incr++)
            dat->push_front(distribution(generator));
    }
    else if (theType.contains("oth"))
    {
        std::gamma_distribution<double> distribution(5.0, 2.5);
        // params are arbitrarily chosen
        for (int incr = 0; incr < num; incr++)
            dat->push_front(distribution(generator));
    }
    else // default behavior is the normal distribution
    {
        std::normal_distribution<double> distribution(10.0, 2.0);
        // params are arbitrarily chosen
        for (int incr = 0; incr < num; incr++)
            dat->push_front(distribution(generator));
    }
    return dat;
}
