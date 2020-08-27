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
    void graphData();
    QVector<qreal>* createData(int num, QString theType);


    void on_uni_button_toggled(bool checked);

    void on_norm_button_toggled(bool checked);

    void on_other_button_toggled(bool checked);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
