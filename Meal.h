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
    Meal() {};
    void addFood(const FoodData food, int grams);
    void sumFood();
    void editFood(const FoodData& food, const int grams, const int newGrams);
    void removeFood(const FoodData& other, const int otherGrams);
    void displayMeal() const;
    int getCalories();
    double getProtein();
    double getCarbs();
    double getFat();
    void clear();
};

bool equal(std::tuple<FoodData, int> food, const FoodData& other, const int otherGrams);

class Day
{
private:
    std::vector<Meal> day_food;
    int date;
    int calories;
    double protein;
    double carbs;
    double fat;
public:
    Day() {};
    int getCalories();
    double getProtein();
    double getCarbs();
    double getFat();
};