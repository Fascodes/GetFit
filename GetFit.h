#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GetFit.h"

// Struct to hold food data
struct FoodData {
    int caloriesPer100g;
    double proteinPer100g;
    double carbsPer100g;
    double fatPer100g;
};

Q_DECLARE_METATYPE(FoodData)

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
};