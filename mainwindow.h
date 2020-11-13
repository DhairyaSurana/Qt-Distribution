#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QLineSeries>
#include <QValueAxis>

#include <QNetworkAccessManager>
#include <QNetworkRequest>


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

    void graphData(QVector<qreal> data);

    QVector<qreal>* createData(int num, QString theType);

    void on_uni_button_toggled(bool checked);
    void on_norm_button_toggled(bool checked);

    void on_bin_slider_valueChanged(int value);
    void on_bin_slider_sliderReleased();


    void on_checkBox_toggled(bool checked);

    void on_rt_button_toggled(bool checked);

    void on_max_slider_valueChanged(int value);

    void managerFinished(QNetworkReply *reply);

    //void authenticate(QNetworkReply* reply, QAuthenticator* auth);

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
};
#endif // MAINWINDOW_H
