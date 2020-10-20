#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void graphData(QVector<qreal> data, int bin_num);

    QVector<qreal>* createData(int num, QString theType);

    void on_uni_button_toggled(bool checked);
    void on_norm_button_toggled(bool checked);
    void on_other_button_toggled(bool checked);

    void on_horizontalSlider_sliderMoved(int position);

private:
    Ui::MainWindow *ui;

    QVector<qreal> norm_data;
    QVector<qreal> unif_data;
    QVector<qreal> other_data;

    int bins;
};
#endif // MAINWINDOW_H
