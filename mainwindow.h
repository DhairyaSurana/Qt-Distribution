#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QLineSeries>
#include <QValueAxis>


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
    void on_other_button_toggled(bool checked);

    void on_horizontalSlider_valueChanged(int value);

    void on_checkBox_toggled(bool checked);

    void on_file_button_toggled(bool checked);

    void on_horizontalSlider_sliderReleased();

private:
    Ui::MainWindow *ui;

    QVector<qreal> norm_data;
    QVector<qreal> unif_data;
    QVector<qreal> other_data;

    bool show_cumulative;
    std::string dist_type;

    QtCharts::QLineSeries *line_series;
    QtCharts::QValueAxis *axisY_right;
};
#endif // MAINWINDOW_H
