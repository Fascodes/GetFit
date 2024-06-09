#include "Day.h"


Meal& Day::getMeal(MealType mealType) {
    switch (mealType)
    {
    case Breakfast:
        return breakfast;
    case Lunch:
        return lunch;
    case Dinner:
        return dinner;
    case Snack:
        return snack;
    case Supper:
        return supper;
    default:
        throw std::invalid_argument("Invalid meal type");
    }
}

int Day::getCalories() const {
	return this->calories;
};

double Day::getProtein() const {
	return this->protein;
};

double Day::getCarbs() const {
	return this->carbs;
};

double Day::getFat() const {
	return this->carbs;
};

void Day::sumMacros() {
	this->calories = this->breakfast.getCalories() + this->lunch.getCalories() + this->dinner.getCalories() + this->snack.getCalories() + this->supper.getCalories();
	this->protein = this->breakfast.getProtein() + this->lunch.getProtein() + this->dinner.getProtein() + this->snack.getProtein() + this->supper.getProtein();
	this->carbs = this->breakfast.getCarbs() + this->lunch.getCarbs() + this->dinner.getCarbs() + this->snack.getCarbs() + this->supper.getCarbs();
	this->fat = this->breakfast.getFat() + this->lunch.getFat() + this->dinner.getFat() + this->snack.getFat() + this->supper.getFat();
};