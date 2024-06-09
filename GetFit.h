#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GetFit.h"
#include <fstream>
#include <iostream>
#include <tuple>
#include "Fooddata.h"
#include "Foods.h"
#include "Meal.h"
#include "EditMealDialog.h"

class GetFit : public QMainWindow
{
    Q_OBJECT

public:
    GetFit(QWidget* parent = nullptr);
    ~GetFit();

private slots:
    void addMeal(Meal* meal, QVBoxLayout* layout, QLabel* sumLabel, QComboBox* comboBox, QLineEdit* lineEdit);
    void removeMeal(Meal* meal, QVBoxLayout* layout, QLabel* sumLabel);

private:
    Ui::GetFitClass ui;
    void populateComboBox(QComboBox* comboBox);
    void sumMacros();
    void updateSumLabel(Meal* meal, QLabel* sumLabel);
    void updateDayLabel();

    Meal breakfast;
    Meal lunch;
    Meal dinner;
    Meal snack;
    Meal supper;
    int calories;
    double protein;
    double carbs;
    double fat;
    QLabel* sumLabelBreakfast;
    QLabel* sumLabelLunch;
    QLabel* sumLabelDinner;
    QLabel* sumLabelSnack;
    QLabel* sumLabelSupper;
    QLabel* sumLabelDay;
};
