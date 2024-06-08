#pragma once

#include "Fooddata.h"
#include <vector>

class Meal
{
private:
    std::vector<std::tuple<FoodData, int>> meal;
    int calories;
    double protein;
    double carbs;
    double fat;
public:
    void addFood(const FoodData food, int grams);
    void sumFood();
    void editFood(size_t mealIndex, int newGrams);
    void removeFood(size_t mealIndex);
    void displayMeal() const;
    int getCalories();
    double getProtein();
    double getCarbs();
    double getFat();
    /*void editFood();
    void removeFood();*/
};

class Day
{
private:
    std::vector<Meal> day_food;
    int date;
public:

};