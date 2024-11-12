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

    setOperationsButtonsCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::checkIfNumberIsZero(){
    return ui->labelReslutDisplay->text() == "0";
}

int MainWindow::calculateExpression(QString expression){
    QStringList numbersStrings = expression.split(QRegularExpression(" \\+ | \\- | x | / "), Qt::SkipEmptyParts);

    QList<int> numbers;

    qDebug() << expression;

    for(int j = 0; j < numbersStrings.length(); j++){
        qDebug() << " Number: " << numbersStrings[j].toInt();
        numbers.append(numbersStrings[j].toInt());
    }


    QStringList operators;
    for(int j = 0; j < expression.length(); j++){
        if(expression[j] == '+' || expression[j] == '-' || expression[j] == 'x' || expression[j] == '/'){
            if(expression[j] == '-' && (expression[j+1] > '0' && expression[j+1] < '9')){
                continue;
            }

            operators.append(expression[j]);
        }
    }

    for(int j = 0; j < operators.length(); j++){
        qDebug() << " Operator: " << operators[j];
    }

    if(operators.empty() && numbers.length() == 1){
        return numbers.back();
    }


    QList<int> numbersCalculated;

    int result = numbers[0];
    for(int j = 0; j < operators.length(); j++){
        qDebug() << "j = " << j << ", operation: " << operators[j];

        if(operators[j] == "/"){
            result = result / numbers[j + 1];
            qDebug() << "Result: " << result;
        } else if(operators[j] == "x"){
            result = result * numbers[j + 1];
            qDebug() << "Result: " << result;
        } else if(operators[j] == "+" || operators[j] == "-"){
            numbersCalculated.append(result);
            qDebug() << "Result added to list: " << result;
            result = numbers[j + 1];
            qDebug() << "Current result: " << result;

        }

        if(j == operators.length() - 1){
            numbersCalculated.append(result);
            if(operators[j] == "+" || operators[j] == "-") {
                numbersCalculated.append(numbers[j+1]);
            }
        }
    }

    for(int j = 0; j < numbersCalculated.length(); j++){
        qDebug() << "Number[" << j << "] = " << numbersCalculated[j];
    }

    operators.removeAll("/");
    operators.removeAll("x");

    result = numbersCalculated[0];

    for(int j = 0; j < operators.length(); j++){
        if(operators[j] == "+"){
            result = result + numbersCalculated[j + 1];
        } else if(operators[j] == "-"){
            result = result - numbersCalculated[j + 1];
        }
    }

    return result;
}

void MainWindow::numberButtonClick(QString number){
    QString expression = ui->labelReslutDisplay->text();

    QRegularExpression regex(" 0$");

    if(expression == "0" || regex.match(expression).hasMatch()){

        if(number != "0"){
            expression.chop(1);
            ui->labelReslutDisplay->setText(expression.append(number));

            lastAddedIsNumber = true;

            lastAddedIsBinaryOperator = false;
            lastAddedIsUnaryOperator = false;
            lastAddedIsOpeningBracket = false;
            lastAddedIsClosingBracket = false;
            return;
        } else {
            lastAddedIsNumber = true;

            lastAddedIsBinaryOperator = false;
            lastAddedIsUnaryOperator = false;
            lastAddedIsOpeningBracket = false;
            lastAddedIsClosingBracket = false;

            return;
        }
    }

    if(expression.isEmpty() || lastAddedIsBinaryOperator || lastAddedIsOpeningBracket || lastAddedIsUnaryOperator){
        lastAddedIsNumber = true;

        if(lastAddedIsBinaryOperator)
            lastAddedIsBinaryOperator = false;
        if(lastAddedIsUnaryOperator)
            lastAddedIsUnaryOperator = false;
        if(lastAddedIsOpeningBracket)
            lastAddedIsOpeningBracket = false;

        ui->labelReslutDisplay->setText(expression.append(number));
    } else if(lastAddedIsNumber){
        ui->labelReslutDisplay->setText(expression.append(number));
    }
}

void MainWindow::setOperationsButtonsCheckable(bool checkable){
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
    qDebug() << "Method " << methodName << "- openBracketsCounter: " << openBracketsCounter;
}


void MainWindow::on_buttonDelete_clicked(){
    QString expression = ui->labelReslutDisplay->text();

    if(!expression.isEmpty()){
        if(lastAddedIsBinaryOperator){
            expression.chop(3);

            lastAddedIsBinaryOperator = false;

            if(expression.back() == ')'){
                lastAddedIsClosingBracket = true;
            } else if(expression.back() >= '0' && expression.back() <= '9') {
                lastAddedIsNumber = true;
            }
        } else if(lastAddedIsUnaryOperator || lastAddedIsNumber){
            expression.chop(1);

            if(lastAddedIsUnaryOperator)
                lastAddedIsUnaryOperator = false;
            if(lastAddedIsNumber)
                lastAddedIsNumber = false;

            if(expression.back() == ' '){
                lastAddedIsBinaryOperator = true;
            } else if(expression.back() == '('){
                lastAddedIsOpeningBracket = true;
            } else if(expression.back() >= '0' && expression.back() <= '9'){
                lastAddedIsNumber = true;
            }
        } else if(lastAddedIsClosingBracket) {
            expression.chop(1);

            openBracketsCounter++;

            lastAddedIsClosingBracket = false;
            lastAddedIsNumber = true;
        } else if(lastAddedIsOpeningBracket) {
            expression.chop(1);

            openBracketsCounter--;

            lastAddedIsOpeningBracket = false;

            if(!expression.isEmpty())
                lastAddedIsBinaryOperator = true;
        }

        ui->labelReslutDisplay->setText(expression);
    }
}

void MainWindow::on_buttonResault_clicked(){
    printDebugInfo(false, "on_buttonResault_clicked");

    QString expression = ui->labelReslutDisplay->text();

    qDebug() << expression;

    if(openBracketsCounter == 0){
        int openCounter = 0;
        int closedCounter = 0;
        int lastOpenBracketIndex;

        while(expression.contains(QRegularExpression("[\\(\\)]"))){
            for(int i = 0; i < expression.length(); i++){
                if(expression[i] == '(' && expression[i+1] != '('){
                    lastOpenBracketIndex = i;
                    openCounter++;
                }
                if(expression[i] == ')'){
                    closedCounter++;
                    if(closedCounter == openCounter){
                        int closingBracketIndex =  i;
                        QString substring = expression.mid(lastOpenBracketIndex + 1, closingBracketIndex - lastOpenBracketIndex - openCounter);

                        expression.replace(lastOpenBracketIndex, closingBracketIndex - lastOpenBracketIndex + 1, QString::number(calculateExpression(substring)));

                        qDebug() << "Labela:" << expression;

                        closedCounter = 0;
                        openCounter = 0;


                        break;
                    }
                }
            }
        }
    }

    ui->labelReslutDisplay->setText(QString::number(calculateExpression(expression)));
    printDebugInfo(true, "on_buttonResault_clicked");
}

void MainWindow::on_buttonOpeningBracket_clicked(){
    QString expression = ui->labelReslutDisplay->text();

    if(lastAddedIsBinaryOperator || lastAddedIsUnaryOperator || lastAddedIsOpeningBracket ||expression.isEmpty()){
        lastAddedIsOpeningBracket = true;

        if(lastAddedIsBinaryOperator)
            lastAddedIsBinaryOperator = false;
        if(lastAddedIsUnaryOperator)
            lastAddedIsUnaryOperator = false;
        if(lastAddedIsNumber)
            lastAddedIsNumber = false;

        ui->labelReslutDisplay->setText(expression.append("("));
        openBracketsCounter++;
    }
}

void MainWindow::on_buttonClosingBracket_clicked(){
    QString expression = ui->labelReslutDisplay->text();
    if(openBracketsCounter > 0 && (lastAddedIsNumber || (lastAddedIsClosingBracket && openBracketsCounter > 0))){
        lastAddedIsClosingBracket = true;

        lastAddedIsNumber = false;

        ui->labelReslutDisplay->setText(expression.append(")"));
        openBracketsCounter--;
    }
}

void MainWindow::on_buttonAddition_clicked(){    
    QString expression = ui->labelReslutDisplay->text();

    if(lastAddedIsNumber || lastAddedIsClosingBracket){
        lastAddedIsBinaryOperator = true;

        if(lastAddedIsNumber)
            lastAddedIsNumber = false;
        if(lastAddedIsClosingBracket)
            lastAddedIsClosingBracket = false;

        ui->labelReslutDisplay->setText(expression.append((" + ")));
    }
}

void MainWindow::on_buttonSubtraction_clicked(){    
    QString expression = ui->labelReslutDisplay->text();

    if(lastAddedIsNumber || lastAddedIsClosingBracket){
        lastAddedIsBinaryOperator = true;

        if(lastAddedIsNumber)
            lastAddedIsNumber = false;
        if(lastAddedIsClosingBracket)
            lastAddedIsClosingBracket = false;

        ui->labelReslutDisplay->setText(expression.append(" - "));
    } else if(expression.isEmpty() || lastAddedIsOpeningBracket) {
        if(expression.endsWith(" + ") || expression.endsWith(" - "))
            return;

        lastAddedIsUnaryOperator = true;

        if(lastAddedIsOpeningBracket)
            lastAddedIsOpeningBracket = false;

        ui->labelReslutDisplay->setText(expression.append("-"));
    }
}

void MainWindow::on_buttonMultiplication_clicked(){
    QString expression = ui->labelReslutDisplay->text();

    if(lastAddedIsNumber || lastAddedIsClosingBracket){
        lastAddedIsBinaryOperator = true;

        if(lastAddedIsNumber)
            lastAddedIsNumber = false;
        if(lastAddedIsClosingBracket)
            lastAddedIsClosingBracket = false;

        ui->labelReslutDisplay->setText(expression.append(" x "));
    }
}

void MainWindow::on_buttonDivision_clicked(){
    QString expression = ui->labelReslutDisplay->text();

    if(lastAddedIsNumber || lastAddedIsClosingBracket){
        lastAddedIsBinaryOperator = true;

        if(lastAddedIsNumber)
            lastAddedIsNumber = false;
        if(lastAddedIsClosingBracket)
            lastAddedIsClosingBracket = false;

        ui->labelReslutDisplay->setText(expression.append(" / "));
    }
}

void MainWindow::on_buttonOne_clicked(){
    numberButtonClick("1");
}

void MainWindow::on_buttonTwo_clicked(){
    numberButtonClick("2");
}

void MainWindow::on_buttonThree_clicked(){
    numberButtonClick("3");
}

void MainWindow::on_buttonFour_clicked(){
    numberButtonClick("4");
}

void MainWindow::on_buttonFive_clicked(){
    numberButtonClick("5");
}

void MainWindow::on_buttonSix_clicked(){
    numberButtonClick("6");
}

void MainWindow::on_buttonSeven_clicked(){
    numberButtonClick("7");
}

void MainWindow::on_buttonEight_clicked(){
    numberButtonClick("8");
}

void MainWindow::on_buttonNine_clicked(){
    numberButtonClick("9");
}

void MainWindow::on_buttonZero_clicked(){
    numberButtonClick("0");
}

