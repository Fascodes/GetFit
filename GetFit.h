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
#include "Day.h"

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
    void updateSumLabel(Meal* meal, QLabel* sumLabel);
    void updateDayLabel();

    Day day;
    QLabel* sumLabelBreakfast;
    QLabel* sumLabelLunch;
    QLabel* sumLabelDinner;
    QLabel* sumLabelSnack;
    QLabel* sumLabelSupper;
    QLabel* sumLabelDay;
};
