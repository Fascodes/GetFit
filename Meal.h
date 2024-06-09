#pragma once

#include "Fooddata.h"
#include <vector>
#include <algorithm>

class Meal
{
private:
    std::vector<std::tuple<FoodData, int>> mealFoods;
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
    int getCalories() const;
    double getProtein() const;
    double getCarbs() const;
    double getFat() const;
    void clear();
    size_t getSize();
    bool foodExists(const std::string& name) const;
};


//class Day
//{
//private:
//    std::vector<Meal> day_food;
//    int date;
//    int calories;
//    double protein;
//    double carbs;
//    double fat;
//public:
//    Day() {};
//    int getCalories() const;
//    double getProtein() const;
//    double getCarbs() const;
//    double getFat() const;
//    void setCalories();
//    void setProtein();
//    void setCarbs();
//    void setFat();
//};