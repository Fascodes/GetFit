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

void Meal::editFood(const FoodData& food, const int grams, const int newGrams) {
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

bool Meal::foodExists(const std::string& name) const {
    return std::any_of(mealFoods.begin(), mealFoods.end(), [&name](const std::tuple<FoodData, int>& item) {
        return std::get<0>(item).name == name;
        });
}

void Meal::clear() {
    mealFoods.clear();
    sumFood();
}

size_t Meal::getSize() const {
    return mealFoods.size();
};

int Meal::getCalories() const {
    return this->calories;
};
double Meal::getProtein() const {
    return this->protein;
};
double Meal::getCarbs() const {
    return this->carbs;
};
double Meal::getFat() const {
    return this->fat;
};