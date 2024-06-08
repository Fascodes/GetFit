#include "Meal.h"

void Meal::addFood(const FoodData food, int grams) {
    mealFoods.push_back(std::make_tuple(food, grams));

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
    for (const auto& item : mealFoods) {
        const FoodData& food = std::get<0>(item);
        int grams = std::get<1>(item);
        calories += (food.caloriesPer100g * grams) / 100;
        protein += (food.proteinPer100g * grams) / 100;
        carbs += (food.carbsPer100g * grams) / 100;
        fat += (food.fatPer100g * grams) / 100;
    }
}







//void Meal::removeFood(const FoodData& other, const int otherGrams) {
//    size_t foodIndex = 0;
//    while (foodIndex < mealFoods.size() && !(equal(mealFoods[foodIndex], other, otherGrams)))foodIndex++;
//    
//    mealFoods.erase(mealFoods.begin() + foodIndex);
//    sumFood();
//}

void Meal::editFood(const FoodData& food, const int grams, const int newGrams)
{
    for (auto& item : mealFoods) {
        if (std::get<0>(item) == food) {
            std::get<1>(item) = newGrams;
            sumFood();
            return;
        }
    }
}

void Meal::removeFood(const FoodData& other, const int otherGrams) {
    for (auto it = mealFoods.begin(); it != mealFoods.end(); ++it) {
        if (std::get<0>(*it) == other) {
            mealFoods.erase(it);
            sumFood();
            return;
        }
    }
}

void Meal::displayMeal() const {
    std::cout << "Meal composition:\n";
    for (const auto& item : mealFoods) {
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
    mealFoods.clear(); // Clear all food items from the vector
}

size_t Meal::getSize()
{
    return mealFoods.size();
};


int Meal::getCalories() const
{
    return this->calories;
};
double Meal::getProtein() const
{
    return this->protein;
};
double Meal::getCarbs() const
{
    return this->carbs;
};
double Meal::getFat() const
{
    return this->fat;
};