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


void Foods::readFood(std::ifstream& inputFile)
{
    if (!inputFile) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    FoodData temp;
    while (inputFile >> temp.name >> temp.caloriesPer100g >> temp.proteinPer100g >> temp.carbsPer100g >> temp.fatPer100g)
    {
        this->food_vector.push_back(temp);
    };
    inputFile.close();
};

const std::vector<FoodData>& Foods::getFood() const {
    return food_vector;
}


const FoodData& Foods::getFoodIndex(size_t index) const {
    if (index < food_vector.size()) {
        return food_vector[index];
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}

void Meal::addFood(const FoodData food, int grams) {
    meal.push_back(std::make_tuple(food, grams));

    calories += (food.caloriesPer100g * grams) / 100;
    protein += (food.proteinPer100g * grams) / 100;
    carbs += (food.carbsPer100g * grams) / 100;
    fat += (food.fatPer100g * grams) / 100;
}

void Meal::sumFood() {
    calories = 0;
    protein = 0.0;
    carbs = 0.0;
    fat = 0.0;
    for (const auto& item : meal) {
        const FoodData& food = std::get<0>(item);
        int grams = std::get<1>(item);
        calories += (food.caloriesPer100g * grams) / 100;
        protein += (food.proteinPer100g * grams) / 100;
        carbs += (food.carbsPer100g * grams) / 100;
        fat += (food.fatPer100g * grams) / 100;
    }
}

void Meal::editFood(size_t mealIndex, int newGrams) {
    if (mealIndex < meal.size()) {
        std::get<1>(meal[mealIndex]) = newGrams;
        sumFood();
    }
    else {
        throw std::out_of_range("Meal index out of range");
    }
}

void Meal::removeFood(size_t mealIndex) {
    if (mealIndex < meal.size()) {
        meal.erase(meal.begin() + mealIndex);
        sumFood();
    }
    else {
        throw std::out_of_range("Meal index out of range");
    }
}

void Meal::displayMeal() const {
    std::cout << "Meal composition:\n";
    for (const auto& item : meal) {
        const FoodData& food = std::get<0>(item);
        int grams = std::get<1>(item);
        std::cout << food.name << ": " << grams << "g\n";
    }
    std::cout << "Total Calories: " << calories << " kcal\n";
    std::cout << "Total Protein: " << protein << " g\n";
    std::cout << "Total Carbs: " << carbs << " g\n";
    std::cout << "Total Fat: " << fat << " g\n";
}


int Meal::getCalories()
{
    return this->calories;
};
double Meal::getProtein()
{
    return this->protein;
};
double Meal::getCarbs()
{
    return this->carbs;
};
double Meal::getFat()
{
    return this->fat;
};

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