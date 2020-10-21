#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Startup
    bins = 20;

    norm_data = *createData(10000, "norm");
    unif_data = *createData(10000, "unif");
    other_data = *createData(10000, "other");

    graphData(norm_data, bins);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Creates a histogram in the graphicsView object (QChartView class)
void MainWindow::graphData(QVector<qreal> data, int bin_num) {

    qDebug() << "bins: " << bins;

    // Get min and max of data
    QVector<qreal>::iterator min = std::min_element(data.begin(), data.end());
    QVector<qreal>::iterator max = std::max_element(data.begin(), data.end());

    // Calculate range and bin length
    qreal range = *max - *min;
    qreal bin_length = range / bin_num;

    QVector<qreal> categories_num;  // Numeric representation of categories on x axis
    QStringList categories; // String representation of categories on x axis

    // Determine categories based on min, max, and bin length
    for(qreal i = *min+bin_length; i <= *max; i+=bin_length) {

        categories << QString::number(i);
        categories_num.append(i);
    }

    // Used to store frequencies of each data point's occurrence within a category
    QMap<float, int> freq;

    // Add categories to QMap and set frequenceis to 0
    for(int c = 0; c < categories_num.size(); c++) {
        freq[categories_num[c]] = 0;
    }

    // Update QMap by traversing data
    for(int i = 0; i < data.size(); i++) {

        for(int c = 0; c < categories_num.size()-1; c++) {

            qreal lower_bound = categories_num[c];
            qreal upper_bound = categories_num[c+1];

            // Increment frequency of category if data fits within bounds
            if(lower_bound <= data[i] && data[i] <= upper_bound) {

                freq[upper_bound] += 1;
                break;
            }
        }
    }

    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Data");

    // Construct set based on QMap values
    qDebug() << "Length: " << freq.values().length();
    QList<int> freq_list = freq.values();

    for(int i = 0; i < freq_list.length(); i++)
        *set << freq_list[i];
    //*set << freq_list[0] << freq_list[1] << freq_list[2] << freq_list[3] << freq_list[4] << freq_list[5] << freq_list[6] << freq_list[7] << freq_list[8] << freq_list[9] << freq_list[10] << freq_list[11] << freq_list[12] << freq_list[13] << freq_list[14] << freq_list[15] << freq_list[16] << freq_list[17] << freq_list[18] << freq_list[19];
    series->append(set);

    // Setup x axis
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsAngle(-90); // x axis labels are printed vertically

    // Setup y axis
    QValueAxis *axisY = new QValueAxis();
    QList<int>::iterator maxY = std::max_element(freq_list.begin(), freq_list.end());
    axisY->setRange(0, *maxY);

    // Setup chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Sample Data Distribution");
    chart->setAnimationOptions(QChart::SeriesAnimations);   // adds rising up animation of histogram bars
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->graphicsView->setChart(chart);
}

// Graphs a uniform distribution when "uniform" radio button is selected
void MainWindow::on_uni_button_toggled(bool checked)
{
    if(checked) {
        qDebug() << "Uniform selected";
        //QVector<qreal> data = *createData(10000, "unif");

        graphData(unif_data, bins);

    }
}

// Graphs a normal distribution when "normal" radio button is selected
void MainWindow::on_norm_button_toggled(bool checked)
{
    if(checked) {
        qDebug() << "Normal selected";
        //QVector<qreal> data = *createData(10000, "norm");

        graphData(norm_data, bins);


    }

}

// Graphs the other distribution when "other" radio button is selected
void MainWindow::on_other_button_toggled(bool checked)
{
    if(checked) {
        qDebug() << "Other selected";
        //QVector<qreal> data = *createData(10000, "other");

        graphData(other_data, bins);



    }

}


// Function to fill a QVector with samples from a specified distribution
// must #include <random> to use this function
// (This function is taken from the Professor's code given in the spec sheet)
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

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    bins = position;
    ui->bin_num->setText(QString::number(bins));

}
