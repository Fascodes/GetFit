#include "DialogBoxes.h"

EditMealDialog::EditMealDialog(const QString& foodName, int grams, QWidget* parent)
    : QDialog(parent), grams(grams)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel(QString("Edit grams for %1").arg(foodName));
    layout->addWidget(label);

    lineEditGrams = new QLineEdit();
    layout->addWidget(lineEditGrams);

    QPushButton* buttonOk = new QPushButton("OK");
    layout->addWidget(buttonOk);

    connect(buttonOk, &QPushButton::clicked, this, &EditMealDialog::accept);
}

int EditMealDialog::getGrams() const
{
    return lineEditGrams->text().toInt();
}

void EditMealDialog::accept()
{
    grams = lineEditGrams->text().toInt();
    QDialog::accept();
}

NewFoodDialog::NewFoodDialog(QWidget* parent)
    : QDialog(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* nameLayout = new QHBoxLayout();
    QLabel* nameLabel = new QLabel("Name:", this);
    nameLineEdit = new QLineEdit(this);
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(nameLineEdit);
    mainLayout->addLayout(nameLayout);

    QHBoxLayout* caloriesLayout = new QHBoxLayout();
    QLabel* caloriesLabel = new QLabel("Calories per 100g:", this);
    caloriesLineEdit = new QLineEdit(this);
    caloriesLayout->addWidget(caloriesLabel);
    caloriesLayout->addWidget(caloriesLineEdit);
    mainLayout->addLayout(caloriesLayout);

    QHBoxLayout* proteinLayout = new QHBoxLayout();
    QLabel* proteinLabel = new QLabel("Protein per 100g:", this);
    proteinLineEdit = new QLineEdit(this);
    proteinLayout->addWidget(proteinLabel);
    proteinLayout->addWidget(proteinLineEdit);
    mainLayout->addLayout(proteinLayout);

    QHBoxLayout* carbsLayout = new QHBoxLayout();
    QLabel* carbsLabel = new QLabel("Carbs per 100g:", this);
    carbsLineEdit = new QLineEdit(this);
    carbsLayout->addWidget(carbsLabel);
    carbsLayout->addWidget(carbsLineEdit);
    mainLayout->addLayout(carbsLayout);

    QHBoxLayout* fatLayout = new QHBoxLayout();
    QLabel* fatLabel = new QLabel("Fat per 100g:", this);
    fatLineEdit = new QLineEdit(this);
    fatLayout->addWidget(fatLabel);
    fatLayout->addWidget(fatLineEdit);
    mainLayout->addLayout(fatLayout);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    addButton = new QPushButton("Add", this);
    cancelButton = new QPushButton("Cancel", this);
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonsLayout);

    connect(addButton, &QPushButton::clicked, this, &NewFoodDialog::onAddButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString NewFoodDialog::getName() const
{
    return nameLineEdit->text();
}

int NewFoodDialog::getCalories() const
{
    return caloriesLineEdit->text().toInt();
}

double NewFoodDialog::getProtein() const
{
    return proteinLineEdit->text().toDouble();
}

double NewFoodDialog::getCarbs() const
{
    return carbsLineEdit->text().toDouble();
}

double NewFoodDialog::getFat() const
{
    return fatLineEdit->text().toDouble();
}

void NewFoodDialog::onAddButtonClicked()
{
    if (getName().isEmpty() || getCalories() <= 0 || getProtein() <= 0 || getCarbs() <= 0 || getFat() <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please provide valid values for all fields.");
        return;
    }
    accept();
}