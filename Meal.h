#ifndef MEAL_H
#define MEAL_H

#include "Fooddata.h"
#include <vector>
#include <algorithm>
#include <tuple>
#include <ostream>
#include <cmath>

class Meal
{
private:
    std::vector<std::tuple<FoodData, int>> mealFoods;
    int calories;
    double protein;
    double carbs;
    double fat;

public:
    Meal() : calories(0), protein(0.0), carbs(0.0), fat(0.0) {};
    void addFood(const FoodData food, int grams);
    void sumFood();
    void editFood(const FoodData& food, const int grams, const int newGrams);
    void removeFood(const FoodData& other, const int otherGrams);

    int getCalories() const;
    double getProtein() const;
    double getCarbs() const;
    double getFat() const;
    size_t getSize() const;

    void clear();
    bool foodExists(const std::string& name) const;

};

#endif