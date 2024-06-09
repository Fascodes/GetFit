#pragma once


#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class NewFoodDialog : public QDialog
{
    Q_OBJECT

public:
    NewFoodDialog(QWidget* parent = nullptr);

    std::string getName() const;
    int getCalories() const;
    double getProtein() const;
    double getCarbs() const;
    double getFat() const;

private slots:
    void accept();

private:
    QLineEdit* lineEditName;
    QLineEdit* lineEditCalories;
    QLineEdit* lineEditProtein;
    QLineEdit* lineEditCarbs;
    QLineEdit* lineEditFat;
};