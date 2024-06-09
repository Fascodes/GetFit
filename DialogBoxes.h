#ifndef DIALOGBOXES_H
#define DIALOGBOXES_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

class NewFoodDialog : public QDialog
{
    Q_OBJECT

public:
    NewFoodDialog(QWidget* parent = nullptr);

    QString getName() const;
    int getCalories() const;
    double getProtein() const;
    double getCarbs() const;
    double getFat() const;

private:
    QLineEdit* nameLineEdit;
    QLineEdit* caloriesLineEdit;
    QLineEdit* proteinLineEdit;
    QLineEdit* carbsLineEdit;
    QLineEdit* fatLineEdit;
    QPushButton* addButton;
    QPushButton* cancelButton;

private slots:
    void onAddButtonClicked();
};

class EditMealDialog : public QDialog
{
    Q_OBJECT

public:
    EditMealDialog(const QString& foodName, int grams, QWidget* parent = nullptr);

    int getGrams() const;

private slots:
    void accept();

private:
    QLineEdit* lineEditGrams;
    int grams;
};

#endif