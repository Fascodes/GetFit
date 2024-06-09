#include "Foods.h"

void Foods::readFood(const std::string& fileName) {
    std::ifstream inputFile(fileName);
    if (!inputFile) {
        std::cerr << "Error opening file." << std::endl;
        inputFile.close();
        return;
    }
    FoodData temp;
    this->food_vector.clear();
    while (inputFile >> temp.name >> temp.caloriesPer100g >> temp.proteinPer100g >> temp.carbsPer100g >> temp.fatPer100g) {
        this->food_vector.push_back(temp);
    };
    this->sortFoodByName();
    inputFile.close();
};

const std::vector<FoodData>& Foods::getFood() const {
    return food_vector;
}

const FoodData& Foods::getFoodIndex(size_t index) const {
    if (index >= food_vector.size()) {
        throw std::out_of_range("Index out of range");
    }
    return food_vector[index];
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

void Foods::writeFood(const FoodData& newFood, const std::string& fileName) {
    std::ofstream outputFile(fileName, std::ios::app);
    if (!outputFile) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    outputFile << newFood << std::endl;
}

void Foods::addFood(const FoodData& newFood) {
    food_vector.push_back(newFood);
}
