#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(this->size());


    QFile file("../styles.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = file.readAll();
        qApp->setStyleSheet(styleSheet);
        file.close();
    } else {
        qDebug() << "Could not open styles.qss";
    }

    ui->labelReslutDisplay->setAlignment(Qt::AlignRight);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkIfNumberIsZero(){
    return ui->labelReslutDisplay->text() == "0";
}

void MainWindow::numberButtonClick(QString number){
    if(checkIfNumberIsZero())
        ui->labelReslutDisplay->setText("");

    if(!additionClicked && !subtractionClicked && !multiplicationClicked && !divisionClicked){
        firstNumberSet = true;
        setBinaryOperationsButtonsCheckable(true);
    }
    else
        secondNumberSet = true;

    ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append(number));
}

void MainWindow::setBinaryOperationsButtonsCheckable(bool checkable){
    ui->buttonAddition->setCheckable(checkable);
    ui->buttonSubtraction->setCheckable(checkable);
    ui->buttonMultiplication->setCheckable(checkable);
    ui->buttonDivision->setCheckable(checkable);
}

void MainWindow::printDebugInfo(bool end, QString methodName){
    if(end){
        qDebug() << "END:";
    } else {
        qDebug() << "BEGIN:";
    }
    qDebug() << "Method " << methodName << "- firstNumberSet: " << firstNumberSet ;
    qDebug() << "Method " << methodName << "- secondNumberSet: " << secondNumberSet ;
    qDebug() << "Method " << methodName << "- additionClicked: " << additionClicked;
    qDebug() << "Method " << methodName << "- subtractionClicked: " << subtractionClicked;
    qDebug() << "Method " << methodName << "- multiplicationClicked: " << multiplicationClicked;
    qDebug() << "Method " << methodName << "- divisionClicked: " << divisionClicked;
}


void MainWindow::on_buttonDelete_clicked(){
    printDebugInfo(false, "on_buttonDelete_clicked");

    QString labelContent = ui->labelReslutDisplay->text();

    if(!labelContent.isEmpty()){
        if(labelContent.endsWith(" + ") || labelContent.endsWith(" - ") || labelContent.endsWith(" x ") || labelContent.endsWith(" / ")){
            if(additionClicked){
                additionClicked = false;
                ui->buttonAddition->setChecked(false);
            }
            else if(subtractionClicked){
                subtractionClicked = false;
                ui->buttonSubtraction->setChecked(false);
            }
            else if(multiplicationClicked){
                multiplicationClicked = false;
                ui->buttonMultiplication->setChecked(false);
            }
            else if(divisionClicked){
                divisionClicked = false;
                ui->buttonDivision->setChecked(false);
            }

            labelContent.chop(3);
            ui->labelReslutDisplay->setText(labelContent);
            printDebugInfo(true, "on_buttonDelete_clicked");
            return;
        }

        labelContent.chop(1);
        ui->labelReslutDisplay->setText(labelContent);

        if(labelContent.isEmpty()){
            firstNumberSet = false;
            setBinaryOperationsButtonsCheckable(false);
        }
    }

    printDebugInfo(true, "on_buttonDelete_clicked");
}

void MainWindow::on_buttonResault_clicked(){
    printDebugInfo(false, "on_buttonResault_clicked");
    if(additionClicked){
        additionClicked = false;
        ui->buttonAddition->setChecked(false);

        QStringList numbers = ui->labelReslutDisplay->text().split('+', Qt::SkipEmptyParts);
        firstNumber = numbers[0].trimmed().toInt();
        secondNumber = numbers[1].trimmed().toInt();

        ui->labelReslutDisplay->setText(QString::number(firstNumber + secondNumber));

        secondNumberSet = false;
    }
    else if(subtractionClicked){
        subtractionClicked = false;
        ui->buttonSubtraction->setChecked(false);

        QStringList numbers = ui->labelReslutDisplay->text().split('-', Qt::SkipEmptyParts);
        firstNumber = numbers[0].trimmed().toInt();
        secondNumber = numbers[1].trimmed().toInt();

        ui->labelReslutDisplay->setText(QString::number(firstNumber - secondNumber));

        secondNumberSet = false;
    } else if(multiplicationClicked) {
        multiplicationClicked = false;
        ui->buttonMultiplication->setChecked(false);

        QStringList numbers = ui->labelReslutDisplay->text().split('x', Qt::SkipEmptyParts);
        firstNumber = numbers[0].trimmed().toInt();
        secondNumber = numbers[1].trimmed().toInt();

        ui->labelReslutDisplay->setText(QString::number(firstNumber * secondNumber));

        secondNumberSet = false;
    } else if(divisionClicked) {
        divisionClicked = false;
        ui->buttonDivision->setChecked(false);

        QStringList numbers = ui->labelReslutDisplay->text().split('/', Qt::SkipEmptyParts);
        firstNumber = numbers[0].trimmed().toInt();
        secondNumber = numbers[1].trimmed().toInt();

        ui->labelReslutDisplay->setText(QString::number(firstNumber / secondNumber));

        secondNumberSet = false;
    }
    printDebugInfo(true, "on_buttonResault_clicked");
}

void MainWindow::on_buttonAddition_clicked(){
    printDebugInfo(false, "on_buttonAddition_clicked");
    if(!additionClicked && firstNumberSet){
        additionClicked = true;

        ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append((" + ")));
    }
    else {
        additionClicked = false;
    }
    printDebugInfo(true, "on_buttonAddition_clicked");
}

void MainWindow::on_buttonSubtraction_clicked(){
    printDebugInfo(false, "on_buttonSubtraction_clicked");
    if(!subtractionClicked && firstNumberSet){
        subtractionClicked = true;

        ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append((" - ")));
    }
    else {
        subtractionClicked = false;
    }
    printDebugInfo(true, "on_buttonSubtraction_clicked");
}

void MainWindow::on_buttonMultiplication_clicked(){
    printDebugInfo(false, "on_buttonMultiplication_clicked");
    if(!multiplicationClicked && firstNumberSet){
        multiplicationClicked = true;

        ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append((" x ")));
    }
    else {
        multiplicationClicked = false;
    }
    printDebugInfo(true, "on_buttonMultiplication_clicked");
}

void MainWindow::on_buttonDivision_clicked(){
    printDebugInfo(false, "on_buttonDivision_clicked");
    if(!divisionClicked && firstNumberSet){
        divisionClicked = true;

        ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append((" / ")));
    }
    else {
        divisionClicked = false;
    }
    printDebugInfo(true, "on_buttonDivision_clicked");
}

void MainWindow::on_buttonOne_clicked(){
    printDebugInfo(false, "on_buttonOne_clicked");

    numberButtonClick("1");

    printDebugInfo(true, "on_buttonOne_clicked");
}

void MainWindow::on_buttonTwo_clicked(){
    printDebugInfo(false, "on_buttonTwo_clicked");

    numberButtonClick("2");

    printDebugInfo(true, "on_buttonTwo_clicked");
}

void MainWindow::on_buttonThree_clicked(){
    printDebugInfo(false, "on_buttonThree_clicked");

    numberButtonClick("3");

    printDebugInfo(true, "on_buttonThree_clicked");
}

void MainWindow::on_buttonFour_clicked(){
    printDebugInfo(false, "on_buttonFour_clicked");

    numberButtonClick("4");

    printDebugInfo(true, "on_buttonFour_clicked");
}

void MainWindow::on_buttonFive_clicked(){
    printDebugInfo(false, "on_buttonFive_clicked");

    numberButtonClick("5");

    printDebugInfo(true, "on_buttonFive_clicked");
}

void MainWindow::on_buttonSix_clicked(){
    printDebugInfo(false, "on_buttonSix_clicked");

    numberButtonClick("6");

    printDebugInfo(true, "on_buttonSix_clicked");
}

void MainWindow::on_buttonSeven_clicked(){
    printDebugInfo(false, "on_buttonSeven_clicked");

    numberButtonClick("7");

    printDebugInfo(true, "on_buttonSeven_clicked");
}

void MainWindow::on_buttonEight_clicked(){
    printDebugInfo(false, "on_buttonEight_clicked");

    numberButtonClick("8");

    printDebugInfo(true, "on_buttonEight_clicked");
}

void MainWindow::on_buttonNine_clicked(){
    printDebugInfo(false, "on_buttonNine_clicked");

    numberButtonClick("9");

    printDebugInfo(true, "on_buttonNine_clicked");
}

void MainWindow::on_buttonZero_clicked(){
    printDebugInfo(false, "on_buttonZero_clicked");

    numberButtonClick("0");

    printDebugInfo(true, "on_buttonZero_clicked");
}

