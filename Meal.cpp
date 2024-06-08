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


bool equal(std::tuple<FoodData, int> food, const FoodData& other, const int otherGrams)
{
    return other.caloriesPer100g == std::get<0>(food).caloriesPer100g && other.proteinPer100g == std::get<0>(food).proteinPer100g && other.carbsPer100g == std::get<0>(food).carbsPer100g && other.fatPer100g == std::get<0>(food).fatPer100g && std::get<1>(food) == otherGrams;
};

void Meal::editFood(const FoodData& food, const int grams, const int newGrams) 
{
    for (const auto& item : meal) {
        const FoodData& food = std::get<0>(item);
        int grams = std::get<1>(item);
    }
    sumFood();
}



void Meal::removeFood(const FoodData& other, const int otherGrams) {
    size_t foodIndex = 0;
    while (foodIndex < meal.size() && !(equal(meal[foodIndex], other, otherGrams)))foodIndex++;
    
    meal.erase(meal.begin() + foodIndex);
    sumFood();
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

void Meal::clear() {
    meal.clear(); // Clear all food items from the vector
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