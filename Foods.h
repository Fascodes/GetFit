#ifndef FOODS_H
#define FOODS_G

#include <iostream>
#include <vector>
#include <algorithm>
#include "Fooddata.h"

class Foods
{
private:
    std::vector<FoodData> food_vector;
public:
    Foods() {};
    void readFood(const std::string& fileName);
    const std::vector<FoodData>& getFood() const;
    const FoodData& getFoodIndex(size_t index) const;
    void sortFoodByName();
    void addFood(FoodData newFood);
    void writeFood(FoodData newFood, const std::string& fileName);
};

#endif