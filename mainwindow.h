#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QRegularExpression>
#include <QList>

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

    int openBracketsCounter = 0;

    bool lastAddedIsNumber = false;
    bool lastAddedIsOpeningBracket = false;
    bool lastAddedIsClosingBracket = false;
    bool lastAddedIsBinaryOperator = false;
    bool lastAddedIsUnaryOperator = false;

    bool checkIfNumberIsZero();
    int calculateExpression(QString expression);
    void numberButtonClick(QString number);
    void setOperationsButtonsCheckable(bool checkable);
    void printDebugInfo(bool end, QString methodName);

private slots:
    void on_buttonDelete_clicked();

    void on_buttonAddition_clicked();
    void on_buttonSubtraction_clicked();
    void on_buttonMultiplication_clicked();
    void on_buttonDivision_clicked();

    void on_buttonSquare_clicked();
    void on_buttonSquareRoot_clicked();

    void on_buttonOpeningBracket_clicked();
    void on_buttonClosingBracket_clicked();

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
