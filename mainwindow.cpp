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
    show_cumulative = false;

    norm_data = *createData(10000, "norm");
    unif_data = *createData(10000, "unif");
    other_data = *createData(10000, "other");

    graphData(norm_data);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Creates a histogram in the graphicsView object (QChartView class)
void MainWindow::graphData(QVector<qreal> data) {

    qDebug() << "bins: " << bins;

    // Get min and max of data
    QVector<qreal>::iterator min = std::min_element(data.begin(), data.end());
    QVector<qreal>::iterator max = std::max_element(data.begin(), data.end());

    // Calculate range and bin length
    qreal range = *max - *min;
    qreal bin_length = range / bins;

    QVector<qreal> categories_num;  // Numeric representation of categories on x axis
    QStringList categories; // String representation of categories on x axis

    // Determine categories based on min, max, and bin length
    for(qreal i = *min+bin_length; i <= *max; i+=bin_length) {

        categories << QString::number(i, 'g', 3) + " to " + QString::number(i+bin_length, 'g', 3);
        categories_num.append(i);
    }

    // Used to store frequencies of each data point's occurrence within a category
    QMap<float, int> freq;

    // Add categories to QMap and set frequencies to 0
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

    QBarSeries *bar_series = new QBarSeries();
    QBarSet *bar_set = new QBarSet("Data");

    line_series = new QLineSeries();    //Setting private variable

    // Construct set based on QMap values
    qDebug() << "Length: " << freq.values().length();
    QList<int> freq_list = freq.values();
    double s = 0;
    for(int i = 0; i < freq_list.length(); i++) {
        *bar_set << freq_list[i];
        s += freq_list[i];
        *line_series << QPointF(categories_num[i], s);
    }

    bar_series->append(bar_set);

    // Setup x axis
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsAngle(-90); // x axis labels are printed vertically

    // Setup y axis (left)
    QValueAxis *axisY_left = new QValueAxis();
    QList<int>::iterator maxY = std::max_element(freq_list.begin(), freq_list.end());
    axisY_left->setRange(0, *maxY);

    axisY_right = new QValueAxis();
    axisY_right->setRange(0, s);

    // Setup chart
    QChart *chart = new QChart();
    chart->addSeries(bar_series);
    chart->addSeries(line_series);

    line_series->setVisible(show_cumulative);


    chart->setTitle("Sample Data Distribution");
    chart->setAnimationOptions(QChart::SeriesAnimations);   // adds rising up animation of histogram bars
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY_left, Qt::AlignLeft);
    chart->addAxis(axisY_right, Qt::AlignRight);

    axisY_right->setVisible(show_cumulative);

    chart->legend()->setAlignment(Qt::AlignBottom);

    ui->graphicsView->setChart(chart);
}

// Graphs a uniform distribution when "uniform" radio button is selected
void MainWindow::on_uni_button_toggled(bool checked)
{
    if(checked) {
        qDebug() << "Uniform selected";
        graphData(unif_data);
    }
}

// Graphs a normal distribution when "normal" radio button is selected
void MainWindow::on_norm_button_toggled(bool checked)
{
    if(checked) {
        qDebug() << "Normal selected";
        graphData(norm_data);
    }

}

// Graphs the gamma distribution when "other" radio button is selected
void MainWindow::on_other_button_toggled(bool checked)
{
    if(checked) {
        qDebug() << "Other selected";
        graphData(other_data);
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

// Updates the number of bins
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    bins = value;
    ui->bin_num->setText("NBINS = " + QString::number(bins));
}

// Graphs a cumulative histogram when "cumulative" checkbox is toggled
void MainWindow::on_checkBox_toggled(bool checked)
{
     show_cumulative = checked;
     line_series->setVisible(show_cumulative);
     axisY_right->setVisible(show_cumulative);
}

QVector<qreal> getFileData() {

    // NOTE: the file must be manually added to the same directory as executable
    QFile file(QCoreApplication::applicationDirPath() + "/datasets_26073_33239_weight-height.csv");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
    }

    QVector<qreal> file_data;
    file.readLine(); // Ignores "Weight" category name
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        file_data.append(line.split(',')[2].simplified().toDouble());
    }

    return file_data;

}

// Graphs the weight distribution of csv file when "data file" button is toggled
void MainWindow::on_file_button_toggled(bool checked)
{
    if(checked) {

       QVector<qreal> data;
       QThread *inpThread = new QThread;


       qDebug() << "InpThread: " << inpThread->isRunning();
       inpThread->start();

       data = getFileData();

       qDebug() << "InpThread: " << inpThread->isRunning();

       inpThread->terminate();

       qDebug() << "InpThread: " << inpThread->isRunning();

       graphData(data);
    }
}
