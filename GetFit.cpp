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

    // Initialize the sum labels
    sumLabelBreakfast = ui.sumLabelBreakfast;
    sumLabelLunch = ui.sumLabelLunch;
    sumLabelDinner = ui.sumLabelDinner;
    sumLabelSnack = ui.sumLabelSnack;
    sumLabelSupper = ui.sumLabelSupper;

    // Populate the comboBoxes with data
    populateComboBox(ui.comboBoxBreakfast);
    populateComboBox(ui.comboBoxLunch);
    populateComboBox(ui.comboBoxDinner);
    populateComboBox(ui.comboBoxSnack);
    populateComboBox(ui.comboBoxSupper);

    // Connect the add meal buttons
    connect(ui.addButtonBreakfast, &QPushButton::clicked, [this]() { addMeal(&breakfast, ui.verticalLayoutScrollAreaBreakfast, sumLabelBreakfast, ui.comboBoxBreakfast, ui.lineEditGramsBreakfast); });
    connect(ui.addButtonLunch, &QPushButton::clicked, [this]() { addMeal(&lunch, ui.verticalLayoutScrollAreaLunch, sumLabelLunch, ui.comboBoxLunch, ui.lineEditGramsLunch); });
    connect(ui.addButtonDinner, &QPushButton::clicked, [this]() { addMeal(&dinner, ui.verticalLayoutScrollAreaDinner, sumLabelDinner, ui.comboBoxDinner, ui.lineEditGramsDinner); });
    connect(ui.addButtonSnack, &QPushButton::clicked, [this]() { addMeal(&snack, ui.verticalLayoutScrollAreaSnack, sumLabelSnack, ui.comboBoxSnack, ui.lineEditGramsSnack); });
    connect(ui.addButtonSupper, &QPushButton::clicked, [this]() { addMeal(&supper, ui.verticalLayoutScrollAreaSupper, sumLabelSupper, ui.comboBoxSupper, ui.lineEditGramsSupper); });

    // Connect the comboBoxViewSelection to switch the stacked widget views
    connect(ui.comboBoxViewSelection, QOverload<int>::of(&QComboBox::currentIndexChanged),
        ui.stackedWidget, &QStackedWidget::setCurrentIndex);
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
    }
}

void GetFit::addMeal(Meal* meal, QVBoxLayout* layout, QLabel* sumLabel, QComboBox* comboBox, QLineEdit* lineEdit)
{
    QString selectedMeal = comboBox->currentText();
    bool ok;
    int grams = lineEdit->text().toInt(&ok);
    if (!ok || grams <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid number of grams.");
        return;
    }

    FoodData foodData = comboBox->currentData().value<FoodData>();
    int totalCalories = (foodData.caloriesPer100g * grams) / 100;
    double totalProtein = (foodData.proteinPer100g * grams) / 100;
    double totalCarbs = (foodData.carbsPer100g * grams) / 100;
    double totalFat = (foodData.fatPer100g * grams) / 100;
    meal->addFood(foodData, grams);

    QString mealText = QString("%1 - %2 grams - %3 Calories - %4g Protein - %5g Carbs - %6g Fat")
        .arg(selectedMeal.split(" - ").first())
        .arg(grams)
        .arg(totalCalories)
        .arg(totalProtein)
        .arg(totalCarbs)
        .arg(totalFat);

    // Create the container widget
    QWidget* containerWidget = new QWidget();
    QHBoxLayout* hLayout = new QHBoxLayout(containerWidget);
    hLayout->setContentsMargins(0, 0, 0, 0);  // Optional: to remove the margins

    // Create the label and buttons
    QLabel* newLabel = new QLabel(mealText);
    QPushButton* removeButton = new QPushButton("Remove");
    QPushButton* editButton = new QPushButton("Edit");

    // Add label and buttons to the layout
    hLayout->addWidget(newLabel);
    hLayout->addStretch();  // Add a stretch to push the buttons to the right
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
            if (editDialog.getGrams() <= 0) {
                QMessageBox::warning(this, "Invalid Input", "Please enter a valid number of grams.");
                return;
            }
            int newGrams = editDialog.getGrams();
            meal->editFood(foodData, grams, newGrams); // Adjust the meal with new grams
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

void GetFit::updateSumLabel(Meal* meal, QLabel* sumLabel)
{
    QString sumText = QString("Total: %1 Calories, %2g Protein, %3g Carbs, %4g Fat")
        .arg(meal->getCalories())
        .arg(meal->getProtein())
        .arg(meal->getCarbs())
        .arg(meal->getFat());

    sumLabel->setText(sumText);
}
