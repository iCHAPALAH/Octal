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
	//������������
	Octal();
	Octal(size_t size);
	Octal(const Octal& x);

	//����� ������
	size_t read(std::istream& stream = std::cin);
	//����� ������
	void display(std::ostream& stream = std::cout) const;
	//����� �������������� � ������
	std::string to_string() const;
	
	//��������� ���������
	bool operator==(const Octal& x) const;
	bool operator!=(const Octal& x) const;
	bool operator<(const Octal& x) const;
	bool operator>(const Octal& x) const;
	bool operator<=(const Octal& x) const;
	bool operator>=(const Octal& x) const;

	//��������� ������������
	Octal& operator=(const Octal& x);
	Octal& operator+=(const Octal& x);
	Octal& operator-=(const Octal& x);
	Octal& operator*=(const Octal& x);
	Octal& operator/=(const Octal& x);
	Octal& operator%=(const Octal& x);

	//�������������� ���������
	Octal operator+(const Octal& x) const;
	Octal operator-(const Octal& x) const;
	Octal operator*(const Octal& x) const;
	Octal operator/(const Octal& x) const;
	Octal operator%(const Octal& x) const;
	
	//��������� ���������� � ����������
	Octal& operator++();
	Octal& operator--();
	Octal operator++(int);
	Octal operator--(int);
};