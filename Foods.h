#pragma once

#include <iostream>
#include <vector>
#include "Fooddata.h"

class Foods
{
private:
    std::vector<FoodData> food_vector;
public:
    void readFood(std::ifstream& inputFile);
    const std::vector<FoodData>& getFood() const;
    const FoodData& getFoodIndex(size_t index) const;
    //void writeFood();
};