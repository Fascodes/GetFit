#include "NewFoodDialog.h"

NewFoodDialog::NewFoodDialog(QWidget* parent)
    : QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* labelName = new QLabel(QString("Enter Name:"));
    layout->addWidget(labelName);

    lineEditName= new QLineEdit();
    layout->addWidget(lineEditName);

    QLabel* labelCalories = new QLabel(QString("Enter Calories:"));
    layout->addWidget(labelCalories);
    lineEditCalories = new QLineEdit();
    layout->addWidget(lineEditCalories);

    QLabel* labelProtein = new QLabel(QString("Enter Protein:"));
    layout->addWidget(labelProtein);
    lineEditProtein = new QLineEdit();
    layout->addWidget(lineEditProtein);

    QLabel* labelCarbs = new QLabel(QString("Enter Carbs:"));
    layout->addWidget(labelCarbs);
    lineEditCarbs = new QLineEdit();
    layout->addWidget(lineEditCarbs);

    QLabel* labelFat = new QLabel(QString("Enter Fat:"));
    layout->addWidget(labelFat);
    lineEditFat = new QLineEdit();
    layout->addWidget(lineEditFat);

    QPushButton* buttonOk = new QPushButton("OK");
    layout->addWidget(buttonOk);

    connect(buttonOk, &QPushButton::clicked, this, &NewFoodDialog::accept);
}

std::string NewFoodDialog::getName() const
{
    return lineEditName->text().toStdString();
}

int NewFoodDialog::getCalories() const
{
    return lineEditCalories->text().toInt();
}

double NewFoodDialog::getProtein() const
{
    return lineEditProtein->text().toDouble();
}

double NewFoodDialog::getCarbs() const
{
    return lineEditCarbs->text().toDouble();
}

double NewFoodDialog::getFat() const
{
    return lineEditFat->text().toDouble();
}



void NewFoodDialog::accept()
{
    QDialog::accept();
}