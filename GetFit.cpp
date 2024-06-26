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
#include <QCoreApplication>
#include <fstream>

GetFit::GetFit(QWidget* parent)
    : QMainWindow(parent)
{
    qRegisterMetaType<FoodData>("FoodData");

    ui.setupUi(this);

    
    sumLabelBreakfast = ui.sumLabelBreakfast;
    sumLabelLunch = ui.sumLabelLunch;
    sumLabelDinner = ui.sumLabelDinner;
    sumLabelSnack = ui.sumLabelSnack;
    sumLabelSupper = ui.sumLabelSupper;
    sumLabelDay = ui.sumLabelDay;

    
    populateComboBox(ui.comboBoxBreakfast);
    populateComboBox(ui.comboBoxLunch);
    populateComboBox(ui.comboBoxDinner);
    populateComboBox(ui.comboBoxSnack);
    populateComboBox(ui.comboBoxSupper);

    
    connect(ui.addButtonBreakfast, &QPushButton::clicked, [this]() {
        addMeal(&day.getMeal(Day::Breakfast), ui.verticalLayoutScrollAreaBreakfast, sumLabelBreakfast, ui.comboBoxBreakfast, ui.lineEditGramsBreakfast); });

    connect(ui.addButtonLunch, &QPushButton::clicked, [this]() {
        addMeal(&day.getMeal(Day::Lunch), ui.verticalLayoutScrollAreaLunch, sumLabelLunch, ui.comboBoxLunch, ui.lineEditGramsLunch); });

    connect(ui.addButtonDinner, &QPushButton::clicked, [this]() {
        addMeal(&day.getMeal(Day::Dinner), ui.verticalLayoutScrollAreaDinner, sumLabelDinner, ui.comboBoxDinner, ui.lineEditGramsDinner); });

    connect(ui.addButtonSnack, &QPushButton::clicked, [this]() {
        addMeal(&day.getMeal(Day::Snack), ui.verticalLayoutScrollAreaSnack, sumLabelSnack, ui.comboBoxSnack, ui.lineEditGramsSnack); });

    connect(ui.addButtonSupper, &QPushButton::clicked, [this]() {
        addMeal(&day.getMeal(Day::Supper), ui.verticalLayoutScrollAreaSupper, sumLabelSupper, ui.comboBoxSupper, ui.lineEditGramsSupper); });

    
    connect(ui.removeAllBreakfast, &QPushButton::clicked, [this]() {
        removeMeal(&day.getMeal(Day::Breakfast), ui.verticalLayoutScrollAreaBreakfast, sumLabelBreakfast); });

    connect(ui.removeAllLunch, &QPushButton::clicked, [this]() {
        removeMeal(&day.getMeal(Day::Lunch), ui.verticalLayoutScrollAreaLunch, sumLabelLunch); });

    connect(ui.removeAllDinner, &QPushButton::clicked, [this]() {
        removeMeal(&day.getMeal(Day::Dinner), ui.verticalLayoutScrollAreaDinner, sumLabelDinner); });

    connect(ui.removeAllSnack, &QPushButton::clicked, [this]() {
        removeMeal(&day.getMeal(Day::Snack), ui.verticalLayoutScrollAreaSnack, sumLabelSnack); });

    connect(ui.removeAllSupper, &QPushButton::clicked, [this]() {
        removeMeal(&day.getMeal(Day::Supper), ui.verticalLayoutScrollAreaSupper, sumLabelSupper); });

    // Connect the button for adding new Food
    connect(ui.addNewFoodButton, &QPushButton::clicked, this, &GetFit::addNewFood);

    // Connect the comboBoxViewSelection to switch the stacked widget views
    connect(ui.comboBoxViewSelection, QOverload<int>::of(&QComboBox::currentIndexChanged),
        ui.stackedWidget, &QStackedWidget::setCurrentIndex);
}

GetFit::~GetFit()
{}

void GetFit::populateComboBox(QComboBox* comboBox) {
    comboBox->clear();

    foods.readFood("foods.txt");
    if (foods.getFood().empty()) {
        QMessageBox::warning(this, "Error: Reading File", "Check the foods.txt file");
        QCoreApplication::quit();
        exit(-1);
    }

    for (const auto& food : foods.getFood()) {
        QString itemText = QString("%1 - %2 calories %3 protein %4 carbs %5 fat / 100g")
            .arg(QString::fromStdString(food.name))
            .arg(food.caloriesPer100g)
            .arg(food.proteinPer100g)
            .arg(food.carbsPer100g)
            .arg(food.fatPer100g);
        FoodData foodData = { food.name, food.caloriesPer100g, food.proteinPer100g, food.carbsPer100g, food.fatPer100g };
        comboBox->addItem(itemText, QVariant::fromValue(foodData));
    }
}

void GetFit::addMeal(Meal* meal, QVBoxLayout* layout, QLabel* sumLabel, QComboBox* comboBox, QLineEdit* lineEdit) {
    QString selectedMeal = comboBox->currentText();
    bool ok;
    constexpr size_t foodLimit = 20;
    int grams = lineEdit->text().toInt(&ok);
    if (!ok || grams <= 0 || grams > 10000) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid number of grams.");
        return;
    }

    size_t currSize = meal->getSize();
    if (currSize >= foodLimit) {
        QMessageBox::warning(this, "Limit reached", "You have reached the limit of foods for this meal.");
        return;
    }

    FoodData foodData = comboBox->currentData().value<FoodData>();
    int totalCalories = (foodData.caloriesPer100g * grams) / 100;
    double totalProtein = (foodData.proteinPer100g * grams) / 100;
    double totalCarbs = (foodData.carbsPer100g * grams) / 100;
    double totalFat = (foodData.fatPer100g * grams) / 100;
    
    if (meal->foodExists(foodData.name)) {
        QMessageBox::warning(this, "Duplicate detected", "This food has already been added, edit to change the amount");
        return;
    };
    meal->addFood(foodData, grams);

    QString mealText = QString("%1 - %2 grams - %3 Calories - %4g Protein - %5g Carbs - %6g Fat")
        .arg(selectedMeal.split(" - ").first())
        .arg(grams)
        .arg(totalCalories)
        .arg(totalProtein)
        .arg(totalCarbs)
        .arg(totalFat);

    
    QWidget* containerWidget = new QWidget();
    QHBoxLayout* hLayout = new QHBoxLayout(containerWidget);
    hLayout->setContentsMargins(0, 0, 0, 0);

    
    QLabel* newLabel = new QLabel(mealText);
    QPushButton* removeButton = new QPushButton("Remove");
    QPushButton* editButton = new QPushButton("Edit");

    // Add label and buttons to the layout
    hLayout->addWidget(newLabel);
    hLayout->addStretch();
    hLayout->addWidget(removeButton);
    hLayout->addWidget(editButton);

    // Add the container widget to the main layout
    layout->addWidget(containerWidget);

    // Connect buttons to their respective slots (assuming you have implemented them)
    connect(removeButton, &QPushButton::clicked, [this, containerWidget, meal, layout, sumLabel, foodData, grams]() {
        meal->removeFood(foodData, grams);
        layout->removeWidget(containerWidget);
        containerWidget->deleteLater();
        updateSumLabel(meal, sumLabel);
     });

    connect(editButton, &QPushButton::clicked, [this, containerWidget, meal, layout, sumLabel, foodData, grams, newLabel]() {
        EditMealDialog editDialog(QString::fromStdString(foodData.name), grams, this);
        if (editDialog.exec() == QDialog::Accepted) {
            int newGrams = editDialog.getGrams();
            if (newGrams <= 0 || newGrams > 10000) {
                QMessageBox::warning(this, "Invalid Input", "Please enter a valid number of grams.");
                return;
            }
            meal->editFood(foodData, grams, newGrams);
            newLabel->setText(QString("%1 - %2 grams - %3 Calories - %4g Protein - %5g Carbs - %6g Fat")
                .arg(QString::fromStdString(foodData.name))
                .arg(newGrams)
                .arg((foodData.caloriesPer100g * newGrams) / 100)
                .arg((foodData.proteinPer100g * newGrams) / 100)
                .arg((foodData.carbsPer100g * newGrams) / 100)
                .arg((foodData.fatPer100g * newGrams) / 100));
            updateSumLabel(meal, sumLabel);
        }
     });

    updateSumLabel(meal, sumLabel);
}

void GetFit::removeMeal(Meal* meal, QVBoxLayout* layout, QLabel* sumLabel) {
    
    meal->clear();

    // Remove all widgets from the layout
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }
    meal->sumFood();

    updateSumLabel(meal, sumLabel);
}

void GetFit::updateSumLabel(Meal* meal, QLabel* sumLabel) {
    meal->sumFood();
    QString sumText = QString("Total: %1 Calories, %2g Protein, %3g Carbs, %4g Fat")
        .arg(meal->getCalories())
        .arg(meal->getProtein())
        .arg(meal->getCarbs())
        .arg(meal->getFat());

    sumLabel->setText(sumText);
    updateDayLabel();
}

void GetFit::updateDayLabel() {
    day.sumMacros();
    QString daySumText = QString("Day Total: %1 Calories, %2g Protein, %3g Carbs, %4g Fat")
        .arg(this->day.getCalories())
        .arg(this->day.getProtein())
        .arg(this->day.getCarbs())
        .arg(this->day.getFat());

    sumLabelDay->setText(daySumText);
};

void GetFit::addNewFood() {
    NewFoodDialog newFoodDialog(this);
    if (newFoodDialog.exec() == QDialog::Accepted) {
        FoodData newFood;
        newFood.name = newFoodDialog.getName().toStdString();
        newFood.caloriesPer100g = newFoodDialog.getCalories();
        newFood.proteinPer100g = newFoodDialog.getProtein();
        newFood.carbsPer100g = newFoodDialog.getCarbs();
        newFood.fatPer100g = newFoodDialog.getFat();

        
        foods.writeFood(newFood, "foods.txt");

        populateComboBox(ui.comboBoxBreakfast);
        populateComboBox(ui.comboBoxLunch);
        populateComboBox(ui.comboBoxDinner);
        populateComboBox(ui.comboBoxSnack);
        populateComboBox(ui.comboBoxSupper);
    }
}
