#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GetFit.h"
#include <fstream>
#include <iostream>
#include <tuple>

struct FoodData {
    std::string name;
    int caloriesPer100g;
    double proteinPer100g;
    double carbsPer100g;
    double fatPer100g;
};

class Foods
{
private:
    std::vector<FoodData> food_vector;
public:
    void readFood(std::ifstream &inputFile);
    const std::vector<FoodData>& getFood() const;
    const FoodData& getFoodIndex(size_t index) const;
    //void writeFood();
};

class Meal
{
private:
    std::vector<std::tuple<FoodData, int>> meal;
    int calories;
    double protein;
    double carbs;
    double fat;
public:
    void addFood(const FoodData food, int grams);
    void sumFood();
    void editFood(size_t mealIndex, int newGrams);
    void removeFood(size_t mealIndex);
    void displayMeal() const;
    int getCalories();
    double getProtein();
    double getCarbs();
    double getFat();
    /*void editFood();
    void removeFood();*/
};

class Day
{
private:
    std::vector<Meal> day_food;
    int date;
public:

};

class GetFit : public QMainWindow
{
    Q_OBJECT

public:
    GetFit(QWidget* parent = nullptr);
    ~GetFit();

private slots:
    void addMeal();

private:
    Ui::GetFitClass ui;
    void populateComboBox(QComboBox* comboBox);

    void updateSumLabel(Meal meal);

    Meal breakfast;
    Meal II_breakfast;
    Meal dinner;
    Meal snack;
    Meal supper;
    QLabel* sumLabel;
};