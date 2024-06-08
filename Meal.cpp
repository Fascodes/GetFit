#include "Meal.h"

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