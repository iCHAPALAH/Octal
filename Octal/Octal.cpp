#include "Octal.h"

Octal::Octal()
{
	size = 0;
	for (size_t i = 0; i < MAX; ++i)
		number[i] = 0;
}

Octal::Octal(size_t size)
{
	this->size = size;
	for (size_t i = 0; i < MAX; ++i)
		number[i] = 0;
}

Octal::Octal(const Octal& x)
{
	size = x.size;
	for (size_t i = 0; i < size; ++i)
		number[i] = x.number[i];
	for (size_t i = size; i < MAX; ++i)
		number[i] = 0;
}

size_t Octal::read(std::istream& stream)
{
	size = 0;
	std::string line;
	getline(stream, line);
	size_t i = 0;
	while (i < line.length() && line[i] == ' ')
		++i;
	while (i < line.length() && line[i] >= '0' && line[i] <= '7')
	{
		number[size] = line[i] - '0';
		++size;
		++i;
	}
	while (i < line.length())
	{
		if (line[i] != ' ')
			size = 0;
		++i;
	}
	for (i = 0; i < size / 2; ++i)
		std::swap(number[i], number[size - i - 1]);
	return size;
}

void Octal::display(std::ostream& stream) const
{
	for (size_t i = size; i != 0; --i)
		stream << +number[i - 1];
}

std::string Octal::to_string() const
{
	std::string result;
	for (size_t i = size; i != 0; --i)
		result.push_back('0' + number[i - 1]);
	return result;
}

bool Octal::operator==(const Octal& x) const
{
	return *this <= x && *this >= x;
}

bool Octal::operator!=(const Octal& x) const
{
	return !(*this == x);
}

bool Octal::operator<(const Octal& x) const
{
	bool result = false;
	if (this->size < x.size)
		result = true;
	else if (this->size == x.size)
	{
		bool trigger = true;
		for (size_t i = x.size; i != 0 && trigger; --i)
			if (this->number[i - 1] != x.number[i - 1])
			{
				trigger = false;
				result = this->number[i - 1] < x.number[i - 1];
			}
	}
	return result;
}

bool Octal::operator>(const Octal& x) const
{
	return x < *this;
}

bool Octal::operator<=(const Octal& x) const
{
	return !(*this > x);
}

bool Octal::operator>=(const Octal& x) const
{
	return !(*this < x);
}

Octal& Octal::operator=(const Octal& x)
{
	this->size = x.size;
	for (size_t i = 0; i < size; ++i)
		this->number[i] = x.number[i];
	return *this;
}

Octal& Octal::operator+=(const Octal& x)
{
	*this = *this + x;
	return *this;
}

Octal& Octal::operator-=(const Octal& x)
{
	*this = *this - x;
	return *this;
}

Octal& Octal::operator*=(const Octal& x)
{
	*this = *this * x;
	return *this;
}

Octal& Octal::operator/=(const Octal& x)
{
	*this = *this / x;
	return *this;
}

Octal& Octal::operator%=(const Octal& x)
{
	*this = *this - *this / x * x;
	return *this;
}

Octal Octal::operator+(const Octal& x) const
{
	Octal result;
	
	for (size_t i = 0; i < MAX; ++i)
	{
		result.number[i] = result.number[i] + this->number[i] + x.number[i];
		if (result.number[i] > 7)
		{
			result.number[i] %= 8;
			if (i != MAX - 1)
				++result.number[i + 1];
		}
	}
	result.size = 1;
	for (size_t i = MAX - 1; i != 0 && result.size == 1; --i)
		if (result.number[i] != 0)
			result.size = i + 1;
	return result;
}

Octal Octal::operator-(const Octal& x) const
{
	Octal result;
	Octal tmp = *this;
	for (size_t i = 0; i < MAX; ++i)
	{
		result.number[i] = tmp.number[i] - x.number[i];
		if (result.number[i] > 7)
		{
			result.number[i] = 8 - (256 - result.number[i]);
			if (i != MAX - 1)
				--tmp.number[i + 1];
		}
	}
	result.size = 1;
	for (size_t i = (MAX - 1); i != 0 && result.size == 1; --i)
		if (result.number[i] != 0)
			result.size = i + 1;
	return result;
}

Octal Octal::operator*(const Octal& x) const
{
	Octal result;
	for (size_t i = 0; i < x.size; ++i)
	{
		Octal tmp;
		tmp.size = i;
		for (size_t j = 0; j < size; ++j)
		{
			tmp.number[tmp.size++] += number[j] * x.number[i];
			if (tmp.size < MAX)
				tmp.number[tmp.size] += tmp.number[tmp.size - 1] / base;
			tmp.number[tmp.size - 1] %= base;
		}
		result += tmp;
	}
	return result;
}

Octal Octal::operator/(const Octal& x) const
{
	Octal result(1);
	if (x == result)
		throw "Деление на 0!\n";
	else
	{
		Octal partial(1), zero(1), eight(2);
		eight.number[1] = 1;
		size_t i = 1;
		while (i < size + 1)
		{
			int vol = 0;
			while (i <= size && partial < x)
			{
				partial = partial * eight;
				partial.number[0] = number[size - i];
				++i;
				++vol;
			}
			if (partial >= x)
			{
				Octal quotient(1);
				quotient.number[0] = 1;
				while (quotient * x <= partial)
					++quotient;
				--quotient;
				result = result * eight + quotient;
				partial = partial - quotient * x;
				if (partial == zero)
				{
					size_t j = i;
					while (j <= size && number[size - j] == 0)
						++j;
					if (j == size + 1)
						while (i <= size)
						{
							result *= eight;
							++i;
						}
				}
			}
			else
				while (vol > 0)
				{
					result *= eight;
					--vol;
				}
		}
		return result;
	}
}

Octal Octal::operator%(const Octal& x) const
{
	return *this - *this / x * x;
}

Octal& Octal::operator++()
{
	Octal tmp(1);
	tmp.number[0] = 1;
	*this += tmp;
	return *this;
}

Octal& Octal::operator--()
{
	Octal tmp(1);
	tmp.number[0] = 1;
	*this -= tmp;
	return *this;
}

Octal Octal::operator++(int)
{
	Octal result = *this, tmp(1);
	tmp.number[0] = 1;
	*this += tmp;
	return result;
}

Octal Octal::operator--(int)
{
	Octal result = *this, tmp(1);
	tmp.number[0] = 1;
	*this -= tmp;
	return result;
}

