#include "Foods.h"
#include <fstream>

void Foods::readFood(std::ifstream& inputFile)
{
    if (!inputFile) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }
    FoodData temp;
    while (inputFile >> temp.name >> temp.caloriesPer100g >> temp.proteinPer100g >> temp.carbsPer100g >> temp.fatPer100g)
    {
        this->food_vector.push_back(temp);
    };
    inputFile.close();
};

const std::vector<FoodData>& Foods::getFood() const {
    return food_vector;
}


const FoodData& Foods::getFoodIndex(size_t index) const {
    if (index < food_vector.size()) {
        return food_vector[index];
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}