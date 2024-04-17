#pragma once
#include <string>
#include <iostream>
#include <sstream>

const size_t MAX = 10;

const size_t base = 8;

struct Octal
{
private:
	unsigned char number[MAX];
	size_t size;
public:
	//Конструкторы
	Octal();
	Octal(size_t size);
	Octal(const Octal& x);

	//Метод чтения
	size_t read(std::istream& stream = std::cin);
	//Метод печати
	void display(std::ostream& stream = std::cout) const;
	//Метод преобразования в строку
	std::string to_string() const;
	
	//Операторы сравнения
	bool operator==(const Octal& x) const;
	bool operator!=(const Octal& x) const;
	bool operator<(const Octal& x) const;
	bool operator>(const Octal& x) const;
	bool operator<=(const Octal& x) const;
	bool operator>=(const Octal& x) const;

	//Операторы присваивания
	Octal& operator=(const Octal& x);
	Octal& operator+=(const Octal& x);
	Octal& operator-=(const Octal& x);
	Octal& operator*=(const Octal& x);
	Octal& operator/=(const Octal& x);
	Octal& operator%=(const Octal& x);

	//Арифметические операторы
	Octal operator+(const Octal& x) const;
	Octal operator-(const Octal& x) const;
	Octal operator*(const Octal& x) const;
	Octal operator/(const Octal& x) const;
	Octal operator%(const Octal& x) const;
	
	//Операторы инкремента и декремента
	Octal& operator++();
	Octal& operator--();
	Octal operator++(int);
	Octal operator--(int);
};