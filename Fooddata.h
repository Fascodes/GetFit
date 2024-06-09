#pragma once

#include <iostream>

struct FoodData{
    std::string name;
    int caloriesPer100g;
    double proteinPer100g;
    double carbsPer100g;
    double fatPer100g;

    bool operator==(const FoodData& other) const {
        return (
            caloriesPer100g == other.caloriesPer100g &&
            proteinPer100g == other.proteinPer100g &&
            carbsPer100g == other.carbsPer100g &&
            fatPer100g == other.fatPer100g);
    };
};