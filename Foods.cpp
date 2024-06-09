#include "Foods.h"
#include <fstream>

void Foods::readFood(std::ifstream& inputFile)
{
    if (!inputFile) {
        std::cerr << "Error opening file." << std::endl;
        inputFile.close();
        return;
    }
    FoodData temp;
    while (inputFile >> temp.name >> temp.caloriesPer100g >> temp.proteinPer100g >> temp.carbsPer100g >> temp.fatPer100g)
    {
        this->food_vector.push_back(temp);
    };
    this->sortFoodByName();
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

void Foods::sortFoodByName() {
    std::sort(food_vector.begin(), food_vector.end(), [](const FoodData& a, const FoodData& b) {
        return a.name < b.name;
        });
}

std::ostream& operator<<(std::ostream& os, const FoodData& newFood) {
    os << newFood.name << " " << newFood.caloriesPer100g << " " << newFood.proteinPer100g << " " << newFood.carbsPer100g << " " << newFood.fatPer100g;
    return os;
}

void Foods::writeFood(FoodData newFood ,std::ofstream& outputFile)
{
    if (!outputFile) {
        std::cerr << "Error opening file." << std::endl;
        outputFile.close();
        return;
    }
    outputFile << newFood << std::endl;
}