#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setFixedSize(this->size());

    ui->labelReslutDisplay->setAlignment(Qt::AlignRight);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkIfNumberIsZero(){
    return ui->labelReslutDisplay->text() == "0";
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
        labelContent.chop(1);
        ui->labelReslutDisplay->setText(labelContent);
    } else {
        firstNumberSet = false;
        ui->buttonAddition->setCheckable(false);
        ui->buttonSubtraction->setCheckable(false);
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


void MainWindow::on_buttonOne_clicked(){
    printDebugInfo(false, "on_buttonOne_clicked");
    if(checkIfNumberIsZero())
        ui->labelReslutDisplay->setText("");

    if(!additionClicked && !subtractionClicked)
        firstNumberSet = true;
    else
        secondNumberSet = true;

    ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append(("1")));
    printDebugInfo(true, "on_buttonOne_clicked");
}

void MainWindow::on_buttonTwo_clicked(){
    printDebugInfo(false, "on_buttonTwo_clicked");
    if(checkIfNumberIsZero())
        ui->labelReslutDisplay->setText("");

    if(!additionClicked && !subtractionClicked){
        firstNumberSet = true;
        ui->buttonAddition->setCheckable(true);
        ui->buttonSubtraction->setCheckable(true);
    }
    else
        secondNumberSet = true;

    ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append(("2")));
    printDebugInfo(true, "on_buttonTwo_clicked");
}

void MainWindow::on_buttonThree_clicked(){
    printDebugInfo(false, "on_buttonThree_clicked");
    if(checkIfNumberIsZero())
        ui->labelReslutDisplay->setText("");

    if(!additionClicked && !subtractionClicked){
        firstNumberSet = true;
        ui->buttonAddition->setCheckable(true);
        ui->buttonSubtraction->setCheckable(true);
    }
    else
        secondNumberSet = true;

    ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append(("3")));
    printDebugInfo(true, "on_buttonThree_clicked");
}

void MainWindow::on_buttonFour_clicked(){
    printDebugInfo(false, "on_buttonFour_clicked");
    if(checkIfNumberIsZero())
        ui->labelReslutDisplay->setText("");

    if(!additionClicked && !subtractionClicked){
        firstNumberSet = true;
        ui->buttonAddition->setCheckable(true);
        ui->buttonSubtraction->setCheckable(true);
    }
    else
        secondNumberSet = true;

    ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append(("4")));
    printDebugInfo(true, "on_buttonFour_clicked");
}

void MainWindow::on_buttonFive_clicked(){
    printDebugInfo(false, "on_buttonFive_clicked");
    if(checkIfNumberIsZero())
        ui->labelReslutDisplay->setText("");

    if(!additionClicked && !subtractionClicked){
        firstNumberSet = true;
        ui->buttonAddition->setCheckable(true);
        ui->buttonSubtraction->setCheckable(true);
    }
    else
        secondNumberSet = true;

    ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append(("5")));
    printDebugInfo(true, "on_buttonFive_clicked");
}

void MainWindow::on_buttonSix_clicked(){
    printDebugInfo(false, "on_buttonSix_clicked");
    if(checkIfNumberIsZero())
        ui->labelReslutDisplay->setText("");

    if(!additionClicked && !subtractionClicked){
        firstNumberSet = true;
        ui->buttonAddition->setCheckable(true);
        ui->buttonSubtraction->setCheckable(true);
    }
    else
        secondNumberSet = true;

    ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append(("6")));
    printDebugInfo(true, "on_buttonSix_clicked");
}

void MainWindow::on_buttonSeven_clicked(){
    printDebugInfo(false, "on_buttonSeven_clicked");
    if(checkIfNumberIsZero())
        ui->labelReslutDisplay->setText("");

    if(!additionClicked && !subtractionClicked){
        firstNumberSet = true;
        ui->buttonAddition->setCheckable(true);
        ui->buttonSubtraction->setCheckable(true);
    }
    else
        secondNumberSet = true;

    ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append(("7")));
    printDebugInfo(true, "on_buttonSeven_clicked");
}

void MainWindow::on_buttonEight_clicked(){
    printDebugInfo(false, "on_buttonEight_clicked");
    if(checkIfNumberIsZero())
        ui->labelReslutDisplay->setText("");

    if(!additionClicked && !subtractionClicked){
        firstNumberSet = true;
        ui->buttonAddition->setCheckable(true);
        ui->buttonSubtraction->setCheckable(true);
    }
    else
        secondNumberSet = true;

    ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append(("8")));
    printDebugInfo(true, "on_buttonEight_clicked");
}

void MainWindow::on_buttonNine_clicked(){
    printDebugInfo(false, "on_buttonNine_clicked");
    if(checkIfNumberIsZero())
        ui->labelReslutDisplay->setText("");

    if(!additionClicked && !subtractionClicked){
        firstNumberSet = true;
        ui->buttonAddition->setCheckable(true);
        ui->buttonSubtraction->setCheckable(true);
    }
    else
        secondNumberSet = true;

    ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append(("9")));
    printDebugInfo(true, "on_buttonNine_clicked");
}

void MainWindow::on_buttonZero_clicked(){
    printDebugInfo(false, "on_buttonZero_clicked");
    if(checkIfNumberIsZero())
        ui->labelReslutDisplay->setText("");

    if(!additionClicked && !subtractionClicked){
        firstNumberSet = true;
        ui->buttonAddition->setCheckable(true);
        ui->buttonSubtraction->setCheckable(true);
    }
    else
        secondNumberSet = true;

    ui->labelReslutDisplay->setText(ui->labelReslutDisplay->text().append(("0")));
    printDebugInfo(true, "on_buttonZero_clicked");
}

