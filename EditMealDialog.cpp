#include "EditMealDialog.h"

EditMealDialog::EditMealDialog(const QString& foodName, int grams, QWidget* parent)
    : QDialog(parent), grams(grams)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel(QString("Edit grams for %1").arg(foodName));
    layout->addWidget(label);

    lineEditGrams = new QLineEdit();
    layout->addWidget(lineEditGrams);

    QPushButton* buttonOk = new QPushButton("OK");
    layout->addWidget(buttonOk);

    connect(buttonOk, &QPushButton::clicked, this, &EditMealDialog::accept);
}

int EditMealDialog::getGrams() const
{
    return lineEditGrams->text().toInt();
}

void EditMealDialog::accept()
{
    grams = lineEditGrams->text().toInt();
    QDialog::accept();
}