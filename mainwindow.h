#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    int firstNumber;
    int secondNumber;

    bool firstNumberSet = false;
    bool secondNumberSet = false;

    bool additionClicked = false;
    bool subtractionClicked = false;
    bool multiplicationClicked = false;
    bool divisionClicked = false;

    bool checkIfNumberIsZero();
    void numberButtonClick(QString number);
    void setBinaryOperationsButtonsCheckable(bool checkable);
    void printDebugInfo(bool end, QString methodName);

private slots:
    void on_buttonDelete_clicked();

    void on_buttonAddition_clicked();
    void on_buttonSubtraction_clicked();
    void on_buttonMultiplication_clicked();
    void on_buttonDivision_clicked();

    void on_buttonResault_clicked();

    void on_buttonOne_clicked();
    void on_buttonTwo_clicked();
    void on_buttonThree_clicked();
    void on_buttonFour_clicked();
    void on_buttonFive_clicked();
    void on_buttonSix_clicked();
    void on_buttonSeven_clicked();
    void on_buttonEight_clicked();
    void on_buttonNine_clicked();
    void on_buttonZero_clicked();
};
#endif // MAINWINDOW_H
