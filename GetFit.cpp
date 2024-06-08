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

GetFit::GetFit(QWidget* parent)
    : QMainWindow(parent)
{
    qRegisterMetaType<FoodData>("FoodData");

    ui.setupUi(this);

    // Initialize the sum label and add it to the layout
    sumLabel = ui.sumLabel;

    // Assume that foods.readFood() is called somewhere to populate the foods vector
    populateComboBox(ui.comboBoxMeal);

    connect(ui.addButtonMeal, &QPushButton::clicked, this, &GetFit::addMeal);
}

GetFit::~GetFit()
{}

void GetFit::populateComboBox(QComboBox* comboBox)
{
    std::ifstream inputFile("foods.txt");
    Foods foods;
    foods.readFood(inputFile);
    if (foods.getFood().empty()) {
        QMessageBox::warning(this, "Error: Reading File", "Check the foods.txt file");
        QCoreApplication::quit();
        exit(-1);
    }

    const std::vector<FoodData>& temp_vector = foods.getFood();
    for (const auto& food : temp_vector)
    {
        QString itemText = QString("%1 - %2 calories %3 protein %4 carbs %5 fat / 100g").arg(QString::fromStdString(food.name)).arg(food.caloriesPer100g).arg(food.proteinPer100g).arg(food.carbsPer100g).arg(food.fatPer100g);
        FoodData foodData = { food.name, food.caloriesPer100g, food.proteinPer100g, food.carbsPer100g, food.fatPer100g };
        comboBox->addItem(itemText, QVariant::fromValue(foodData));
    };

}

void GetFit::addMeal()
{
    QString selectedMeal = ui.comboBoxMeal->currentText();
    bool ok;
    int grams = ui.lineEditGrams->text().toInt(&ok);
    if (!ok || grams <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid number of grams.");
        return;
    }

    FoodData foodData = ui.comboBoxMeal->currentData().value<FoodData>();
    int totalCalories = (foodData.caloriesPer100g * grams) / 100;
    double totalProtein = (foodData.proteinPer100g * grams) / 100;
    double totalCarbs = (foodData.carbsPer100g * grams) / 100;
    double totalFat = (foodData.fatPer100g * grams) / 100;
    breakfast.addFood(foodData, grams);

    QString mealText = QString("%1 - %2 grams - %3 Calories - %4g Protein - %5g Carbs - %6g Fat")
        .arg(selectedMeal.split(" - ").first())
        .arg(grams)
        .arg(totalCalories)
        .arg(totalProtein)
        .arg(totalCarbs)
        .arg(totalFat);

    QLabel* newLabel = new QLabel(mealText);
    ui.verticalLayoutScrollAreaMeal->addWidget(newLabel);

    updateSumLabel(breakfast);
}

void GetFit::updateSumLabel(Meal meal)
{
    QString sumText = QString("Total: %1 Calories, %2g Protein, %3g Carbs, %4g Fat")
        .arg(meal.getCalories())
        .arg(meal.getProtein())
        .arg(meal.getCarbs())
        .arg(meal.getFat());

    sumLabel->setText(sumText);
}