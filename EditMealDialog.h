#pragma once


#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

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