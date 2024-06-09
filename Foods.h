#ifndef FOODS_H
#define FOODS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "FoodData.h"
#include <fstream>
#include <stdexcept>
#include <sstream>

class Foods {
private:
    std::vector<FoodData> food_vector;

public:
    Foods() = default;

    void readFood(const std::string& fileName);
    const std::vector<FoodData>& getFood() const;
    const FoodData& getFoodIndex(size_t index) const;
    void sortFoodByName();
    void addFood(const FoodData& newFood);
    void writeFood(const FoodData& newFood, const std::string& fileName);
};

#endif 
