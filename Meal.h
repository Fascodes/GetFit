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
    int getCalories() const;
    double getProtein() const;
    double getCarbs() const;
    double getFat() const;
    void clear();
    size_t getSize();
    bool foodExists(const std::string& name) const;
    friend std::ostream& operator<<(std::ostream& os, const Meal& meal);
};

std::ostream& operator<<(std::ostream& os, const Meal& meal);
