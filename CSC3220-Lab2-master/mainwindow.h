#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>
using namespace std;

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

    void on_queenRadio_toggled(bool checked);

    void on_standardRadio_toggled(bool checked);

    void on_nightsSpinBox_valueChanged(int arg1);

    void on_parkingCheckBox_stateChanged(int arg1);

    void calculatePreviewPrice();

    void on_nextPushButton_clicked();

    void on_backPushButton_clicked();

    void on_visaRadio_toggled(bool checked);

    void on_masterCardRadio_toggled(bool checked);

    void on_discoverRadio_toggled(bool checked);

    void on_americaexpressRadio_toggled(bool checked);

    void on_payPushButton_clicked();

    void on_confirmPushButton_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
