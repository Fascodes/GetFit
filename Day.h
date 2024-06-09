#pragma once
#include <vector>
#include "Meal.h"
#include <fstream>

class Day
{
private:
    int calories;
    double protein;
    double carbs;
    double fat;
    Meal breakfast;
    Meal lunch;
    Meal dinner;
    Meal snack;
    Meal supper;


public:
    Day() : calories(0), protein(0.0), carbs(0.0), fat(0.0) {};
    enum MealType { Breakfast, Lunch, Dinner, Snack, Supper };
    Meal& getMeal(MealType mealtype);
    int getCalories() const;
    double getProtein() const;
    double getCarbs() const;
    double getFat() const;
    void sumMacros();
};
