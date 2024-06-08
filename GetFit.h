#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GetFit.h"
#include <fstream>
#include <iostream>
#include <tuple>
#include "Fooddata.h"
#include "Foods.h"
#include "Meal.h"

class GetFit : public QMainWindow
{
    Q_OBJECT

public:
    GetFit(QWidget* parent = nullptr);
    ~GetFit();

private slots:
    void addMeal(Meal* meal, QVBoxLayout* layout, QLabel* sumLabel, QComboBox* comboBox, QLineEdit* lineEdit);

private:
    Ui::GetFitClass ui;
    void populateComboBox(QComboBox* comboBox);

    void updateSumLabel(Meal* meal, QLabel* sumLabel);

    Meal breakfast;
    Meal lunch;
    Meal dinner;
    Meal snack;
    Meal supper;
    QLabel* sumLabelBreakfast;
    QLabel* sumLabelLunch;
    QLabel* sumLabelDinner;
    QLabel* sumLabelSnack;
    QLabel* sumLabelSupper;
};
