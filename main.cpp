#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
using namespace std;

int main(void) {
	string name;
	//Input name
	cout << "********** RETIREMENT CALCULATOR **********" << endl;
	cout << "Name: " << name << endl;

	//Define and Initialize all the int variables
	int age, retire_age, life;
	age = 0;
	retire_age = 0;
	life = 0;

	//Define and Initialize all the double variables
	double saving, retire_contri, annual_rate, inflation_rate, income, income_needed_year;
	saving = 0.0;
	retire_contri = 0.0;
	annual_rate = 0.0;
	inflation_rate = 0.0;
	income = 0.0;
	income_needed_year = 0.0;

	//User input and ensure the values input are valid 
	cout << "Enter your current age: ";
	cin >> age;
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	while (age < 18) {
		cout << "Invalid! Please enter a valid age!" << endl;
		cout << "Re-enter your current age: ";
		cin >> age;
		cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	}

	cout << "Enter your planned retirement age: ";
	cin >> retire_age;
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	while (retire_age <= age) {
		cout << "Invalid! Please enter a valid age!" << endl;
		cout << "Re-enter your planned retirement age: ";
		cin >> retire_age;
		cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	}

	cout << "Enter your life expectancy: ";
	cin >> life;
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	while (life < retire_age) {
		cout << "Invalid! Please enter a valid age!" << endl;
		cout << "Re-enter your life expectancy : ";
		cin >> life;
		cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	}

	cout << "Enter your current savings ($): ";
	cin >> saving;
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	while (saving <= 0) {
		cout << "Invalid! Please enter a valid amount!" << endl;
		cout << "Re-enter your current savings ($): ";
		cin >> saving;
		cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	}

	cout << "Enter your annual retirement contribution ($): ";
	cin >> retire_contri;
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	while (retire_contri <= 0) {
		cout << "Invalid! Please enter a valid amount!" << endl;
		cout << "Re-enter your annual retirement contribution ($): ";
		cin >> retire_contri;
		cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	}

	cout << "Enter your expected annual return rate (as %): ";
	cin >> annual_rate;
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	while (annual_rate < 0) {
		cout << "Invalid! Please enter a valid percentage!" << endl;
		cout << "Re-enter your expected annual return rate (as %): ";
		cin >> annual_rate;
		cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	}

	cout << "Enter the inflation rate (as %): ";
	cin >> inflation_rate;
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	while (inflation_rate < 0) {
		cout << "Invalid! Please enter a valid percentage!" << endl;
		cout << "Re-enter the inflation rate (as %): ";
		cin >> inflation_rate;
		cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	}

	cout << "Enter your current income ($): ";
	cin >> income;
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	while (income <= 0) {
		cout << "Invalid! Please enter a valid amount!" << endl;
		cout << "Re-enter your current income ($): ";
		cin >> income;
		cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	}

	cout << "Enter the income needed per year after retirement (in today's dollars) ($): ";
	cin >> income_needed_year;
	cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	while (income_needed_year <= 0) {
		cout << "Invalid! Please enter a valid amount!" << endl;
		cout << "Re-enter the income needed per year after retirement (in today's dollars) ($): ";
		cin >> income_needed_year;
		cin.ignore(numeric_limits <streamsize> ::max(), '\n');
	}

	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;

	//Calculation Part
	cout << "\n********** RETIREMENT SUMMARY **********" << endl;
	int year_to_retire;
	year_to_retire = retire_age - age;
	cout << "Years to retire: " << year_to_retire << " years" << endl;

	double ttl_saving;
	ttl_saving = 0;
	for (int i = 1; i <= year_to_retire; i += 1) {
		ttl_saving = saving + (saving * (annual_rate / 100)) + retire_contri;
		saving = ttl_saving;
	}
	cout << "Projected total savings at retirement: $" << fixed << showpoint << setprecision(2) << ttl_saving << endl;

	double purchasing_power;
	purchasing_power = ttl_saving / pow((1 + inflation_rate / 100), year_to_retire);
	cout << "Equivalent to current purchasing power: $" << fixed << showpoint << setprecision(2) << purchasing_power << endl;

	double amount_needed;
	amount_needed = (income_needed_year * pow((1 + inflation_rate / 100), year_to_retire)) * 25;
	cout << "Estimated amount John Tan needs at retirement age: $" << fixed << showpoint << setprecision(2) << amount_needed << endl;

	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;

	//Monthly Withdrawal Estimate
	cout << "\n********** MONTHLY WITHDRAWAL ESTIMATE **********" << endl;
	double month_rate, month_withdrawal;
	int ttlmonth_life;
	month_rate = (annual_rate / 100) / 12;
	ttlmonth_life = (life - retire_age) * 12;
	month_withdrawal = (ttl_saving * month_rate) / (1 - pow((1 + month_rate), -ttlmonth_life));
	cout << "After retirement (if saved $" << ttl_saving << "):" << endl;
	cout << "Actual amount income: $" << fixed << showpoint << setprecision(2) << month_withdrawal << " / month" << endl;

	double today_money;
	today_money = month_withdrawal / pow((1 + (inflation_rate / 100)), year_to_retire);
	cout << "Today's money: $" << fixed << showpoint << setprecision(2) << today_money << " / month" << endl;

	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;

	//Fixed Purchasing Power
	cout << "\n********** FIXED PURCHASING POWER WITHDRAWAL **********" << endl;
	double real_rate_month, fixed_purchase;
	real_rate_month = ((1 + annual_rate / 100) / (1 + inflation_rate / 100) - 1) / 12;
	fixed_purchase = (ttl_saving * real_rate_month) / (1 - pow((1 + real_rate_month), -ttlmonth_life));
	cout << "Monthly withdrawal at " << retire_age << ", increasing " << inflation_rate << "% annually: $" << fixed << showpoint << setprecision(2) << fixed_purchase << endl;

	double today_fixed_purchase;
	today_fixed_purchase = fixed_purchase / pow((1 + inflation_rate / 100), year_to_retire);
	cout << "Equivalent to current purchase power of $" << fixed << showpoint << setprecision(2) << today_fixed_purchase << endl;

	cout << "\n------------------------------------------------------------------------------------------------------------------------" << endl;

	//Conclusion
	if (fixed_purchase >= income_needed_year) {
		cout << ">>> " << name <<  " is on track for retirement!" << endl;
	}
	else {
		cout << ">>> Attention! " << name << " is not on track for retirement!" << endl;
	}

	//Enhancement
	cout << "\n\nThe amount you have: $" << fixed << showpoint << setprecision(2) << ttl_saving << endl;
	cout << "You plan to withdraw: $" << fixed << showpoint << setprecision(2) << fixed_purchase << " / month" << endl;
	cout << "Average investment return: " << fixed << showpoint << setprecision(2) << annual_rate << "%" << endl;

	cout << "\nResult:" << endl;
	double balance = ttl_saving;
	double monthly_rate = (annual_rate / 100) / 12;
	int total_month = 0;

	while (balance > fixed_purchase) {
		balance *= (1 + monthly_rate);
		balance -= fixed_purchase;
		total_month++;
	}
	int year = total_month / 12;
	float month = total_month % 12;
	cout << "If withdraw $" << fixed_purchase << " per month, $" << ttl_saving << " can last " << year << " years and " << fixed << showpoint << setprecision(1) << month << " months." << endl;


	system("pause");
	return 0;
}