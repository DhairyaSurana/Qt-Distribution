#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QLineSeries>
#include <QValueAxis>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // Histogram Functions
    void graphData(QVector<qreal> data);
    QVector<qreal>* createData(int num, QString type);
    void on_checkBox_toggled(bool checked);

    // Radio Button Functions
    void on_uni_button_toggled(bool checked);
    void on_norm_button_toggled(bool checked);
    void on_rt_button_toggled(bool checked);

    // Bin Slider Functions
    void on_bin_slider_valueChanged(int value);
    void on_bin_slider_sliderReleased();

    // Max Slider + NOAA REST API Functions
    void on_max_slider_valueChanged(int value);
    void on_max_slider_sliderReleased();
    void managerFinished(QNetworkReply *reply);



private:
    Ui::MainWindow *ui;

    QVector<qreal> norm_data;
    QVector<qreal> unif_data;

    bool show_cumulative;
    std::string dist_type;

    QtCharts::QLineSeries *line_series;
    QtCharts::QValueAxis *axisY_right;

    QNetworkAccessManager *manager;
    QNetworkRequest request;

    QString url;
    QString token;
};
#endif // MAINWINDOW_H
