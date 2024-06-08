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