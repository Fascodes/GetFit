#include "GetFit.h"
#include <QVBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QScrollArea>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QMessageBox>

// Register the FoodData type with Qt's meta-object system

GetFit::GetFit(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // Populate the combo box with food items and their data per 100g
    FoodData apple = { 52, 0.3, 14, 0.2 };
    FoodData banana = { 89, 1.1, 23, 0.3 };
    FoodData orange = { 47, 0.9, 12, 0.1 };
    FoodData chickenBreast = { 165, 31, 0, 3.6 };
    FoodData rice = { 130, 2.4, 28, 0.3 };
    FoodData broccoli = { 34, 2.8, 7, 0.4 };

    ui.comboBox->addItem("Apple - 52 Calories", QVariant::fromValue(apple));
    ui.comboBox->addItem("Banana - 89 Calories", QVariant::fromValue(banana));
    ui.comboBox->addItem("Orange - 47 Calories", QVariant::fromValue(orange));
    ui.comboBox->addItem("Chicken Breast - 165 Calories", QVariant::fromValue(chickenBreast));
    ui.comboBox->addItem("Rice - 130 Calories", QVariant::fromValue(rice));
    ui.comboBox->addItem("Broccoli - 34 Calories", QVariant::fromValue(broccoli));

    // Connect the add button to a slot that adds new labels
    connect(ui.addButton, &QPushButton::clicked, this, &GetFit::addMeal);
}

GetFit::~GetFit()
{}

// Slot to add a new meal label based on the combo box selection and grams input
void GetFit::addMeal()
{
    QString selectedMeal = ui.comboBox->currentText();
    bool ok;
    int grams = ui.lineEdit->text().toInt(&ok);
    if (!ok || grams <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid number of grams.");
        return;
    }

    FoodData foodData = ui.comboBox->currentData().value<FoodData>();
    int totalCalories = (foodData.caloriesPer100g * grams) / 100;
    double totalProtein = (foodData.proteinPer100g * grams) / 100;
    double totalCarbs = (foodData.carbsPer100g * grams) / 100;
    double totalFat = (foodData.fatPer100g * grams) / 100;

    QString mealText = QString("%1 - %2 grams - %3 Calories - %4g Protein - %5g Carbs - %6g Fat")
        .arg(selectedMeal.split(" - ").first())
        .arg(grams)
        .arg(totalCalories)
        .arg(totalProtein)
        .arg(totalCarbs)
        .arg(totalFat);

    QLabel* newLabel = new QLabel(mealText, ui.scrollAreaWidgetContents);
    ui.scrollAreaWidgetContents->layout()->addWidget(newLabel);
}